// Fill out your copyright notice in the Description page of Project Settings.


#include "ValheimPlayer.h"
#include "AC_BuildComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "AC_InventoryComponent.h"
#include "AC_CraftingComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"



// Sets default values
AValheimPlayer::AValheimPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshTemp(
		TEXT("/Script/Engine.SkeletalMesh'/Game/UP/VIking/Brute.Brute'"));

	if (MeshTemp.Succeeded()) {
		GetMesh()->SetSkeletalMesh(MeshTemp.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetRelativeLocation(FVector(0.0f, 60.0f, 80.0f));
	springArmComp->TargetArmLength = 300.0f;
	springArmComp->bUsePawnControlRotation = true;

	// Camera 컴포넌트 붙이기
	tpsCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("TpsCamComp"));
	tpsCamComp->SetupAttachment(springArmComp);
	tpsCamComp->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// BuildingSystem
	BuildComp = CreateDefaultSubobject<UAC_BuildComponent>(TEXT("BuildComp"));


	// InventorySystem
	InventoryComp = CreateDefaultSubobject<UAC_InventoryComponent>(TEXT("InventoryComp"));
	
	// CraftingSystem
	CraftingComp = CreateDefaultSubobject<UAC_CraftingComponent>(TEXT("CraftingComp"));

}

// Called when the game starts or when spawned
void AValheimPlayer::BeginPlay()
{
	Super::BeginPlay();
	


	pc = Cast<APlayerController>(Controller);

	if (pc)
	{
		auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());

		if (subsystem)
		{
			subsystem->AddMappingContext(IMC_TPS, 0);
		}
	}

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	BuildComp->SetCameraBS(tpsCamComp);
	InventoryComp->ConnectedActor = this;
	BuildComp->CraftComp = CraftingComp;
	BuildComp->InventoryComp = InventoryComp;
	// 애님몽타주 구현용 애님인스턴스 KMS
	AnimInstance = GetMesh()->GetAnimInstance();

	anim = Cast<UValheimPlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AValheimPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Direction = FTransform(GetControlRotation()).TransformVector(Direction);

	AddMovementInput(Direction);
	Direction = FVector::ZeroVector;

}

void AValheimPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	auto PlayerInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (PlayerInput)
	{
		PlayerInput->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &AValheimPlayer::Turn);
		PlayerInput->BindAction(IA_LookUp, ETriggerEvent::Triggered, this, &AValheimPlayer::LookUp);
		PlayerInput->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AValheimPlayer::Move);
		PlayerInput->BindAction(IA_Jump, ETriggerEvent::Started, this, &AValheimPlayer::InputJump);
		PlayerInput->BindAction(IA_BuildMode, ETriggerEvent::Started, this, &AValheimPlayer::BuildModeOn);
		PlayerInput->BindAction(IA_WheelUp, ETriggerEvent::Started, this, &AValheimPlayer::WheelUp);
		PlayerInput->BindAction(IA_WheelDown, ETriggerEvent::Started, this, &AValheimPlayer::WheelDown);
		PlayerInput->BindAction(IA_LeftMouseButton, ETriggerEvent::Started, this, &AValheimPlayer::LeftMouseButton);
		PlayerInput->BindAction(IA_RightMouseButton, ETriggerEvent::Started, this, &AValheimPlayer::RightMouseButton);
		PlayerInput->BindAction(IA_RotateRightR, ETriggerEvent::Triggered, this, &AValheimPlayer::RotateRightR);
		PlayerInput->BindAction(IA_RotateLeftQ, ETriggerEvent::Triggered, this, &AValheimPlayer::RotateLeftQ);

		PlayerInput->BindAction(IA_CraftMode, ETriggerEvent::Started, this, &AValheimPlayer::CraftModeOn);
		PlayerInput->BindAction(IA_InventoryMode, ETriggerEvent::Started, this, &AValheimPlayer::InventoryModeOn);
		PlayerInput->BindAction(IA_PickUp, ETriggerEvent::Started, this, &AValheimPlayer::PickUp);

		PlayerInput->BindAction(IA_Sprint, ETriggerEvent::Started, this, &AValheimPlayer::SprintStart);
		PlayerInput->BindAction(IA_Sprint, ETriggerEvent::Completed, this, &AValheimPlayer::SprintStart);

		PlayerInput->BindAction(IA_Roll, ETriggerEvent::Started, this, &AValheimPlayer::Roll);
		PlayerInput->BindAction(IA_Attack, ETriggerEvent::Started, this, &AValheimPlayer::Attack);
		

	}
}

void AValheimPlayer::Turn(const FInputActionValue& inputValue)
{
	float value = inputValue.Get<float>();
	AddControllerYawInput(value);
}

void AValheimPlayer::LookUp(const FInputActionValue& inputValue)
{
	float value = inputValue.Get<float>();
	AddControllerPitchInput(value);
}

void AValheimPlayer::InputJump(const FInputActionValue& inputValue)
{
	Jump();
}

void AValheimPlayer::Move(const FInputActionValue& inputValue)
{
	FVector2D value = inputValue.Get<FVector2D>();

	Direction.X = value.X;
	Direction.Y = value.Y;

	//GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AValheimPlayer::SprintStart(const FInputActionValue& inputValue)
{
	auto Movement = GetCharacterMovement();
	if (!Movement) return;
	
	if (Movement->MaxWalkSpeed > WalkSpeed) 
	{
		Movement->MaxWalkSpeed = WalkSpeed;
	}
	else 
	{
		Movement->MaxWalkSpeed = SprintSpeed;
	}
}

void AValheimPlayer::Roll(const FInputActionValue& inputValue)
{
	if (anim) {
		IsRolling = true;
		//GetCharacterMovement()->MaxWalkSpeed = 0.0f;
		anim->PlayRollAnim();
		
	}
}

void AValheimPlayer::Attack(const FInputActionValue& inputValue)
{
	if (AM_PlayerAttack)
	{
		AnimInstance;
		if (AnimInstance && AM_PlayerAttack)
		{
			GetCharacterMovement()->MaxWalkSpeed = 0.0f; 
			// 공격 중 이동 금지
			//AnimInstance->Montage_Play(AM_PlayerAttack);
			
		}
	}
}

void AValheimPlayer::OnAttackEnd()
{
	
}

void AValheimPlayer::BuildModeOn()
{
	if (GEngine)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("BuildModeOn"));
	}
	//BuildComp->LaunchBuildMode();
}

void AValheimPlayer::DestroyComponent(UActorComponent* BC)
{
	BC->DestroyComponent();
}

void AValheimPlayer::WheelUp(const FInputActionValue& inputValue)
{
	if (BuildComp->IsBuildMode) {
		int32 BuildDataSize = BuildComp->BuildableDataArray.Num() - 1;
		int32 BuildIndex = BuildComp->BuildID;

		if (BuildIndex < BuildDataSize) {
			BuildIndex += 1;
			BuildComp->BuildID = BuildIndex;
		}

		BuildComp->ChangeMesh();

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("WheelUp!"));
	}
}

void AValheimPlayer::WheelDown(const FInputActionValue& inputValue)
{
	if (BuildComp->IsBuildMode) {
		int32 BuildDataSize = BuildComp->BuildableDataArray.Num() - 1;
		int32 BuildIndex = BuildComp->BuildID;
		if (BuildIndex > 0) {
			BuildIndex -= 1;
			BuildComp->BuildID = BuildIndex;
		}

		BuildComp->ChangeMesh();

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("WheelDown!"));
	}
}

void AValheimPlayer::LeftMouseButton(const FInputActionValue& inputValue)
{
	if (BuildComp->IsBuildMode && BuildComp->CanBuild) {

		if (CraftingSlotUI) {
			FName SlotName = FName(CraftingSlotUI->CraftSlotName->GetText().ToString());

			if (SlotName != PreviousSlotName) {
				PreviousSlotName = SlotName;
			}

			if (BuildComp->IsIngredientsEnough(PreviousSlotName)) {

				BuildComp->SpawnBuild(PreviousSlotName);
			}

		}
		
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("SpawnBuild"));
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("LeftMouse!"));
}



void AValheimPlayer::RightMouseButton(const FInputActionValue& inputValue)
{
	if (BuildComp->IsBuildMode) {
		BuildComp->DestroyBuild();
	}
}

void AValheimPlayer::RotateRightR(const FInputActionValue& inputValue)
{
	if (BuildComp->IsBuildMode) {
		BuildComp->RotateRight();
	}
}

void AValheimPlayer::RotateLeftQ(const FInputActionValue& inputValue)
{
	if (BuildComp->IsBuildMode) {
		BuildComp->RotateLeft();
	}
}

void AValheimPlayer::CraftModeOn()
{
	if (IsCraftModeOn) {
		if (CraftUI) {
			CraftUI->RemoveFromParent();
		}
		IsCraftModeOn = false;
		FInputModeGameOnly GameInputMode;
		pc->SetInputMode(GameInputMode);
		pc->bShowMouseCursor = false;
	}
	else {
		if (CraftWidget)
		{
			CraftUI = CreateWidget<UCraftingUI>(GetWorld(), CraftWidget);
		}
		if (CraftUI)
		{
			CraftUI->AddToViewport();
			CraftUI->LoadCraftInventory(CraftingComp);
		}
		IsCraftModeOn = true;
		BuildComp->StopBuildMode();

		FInputModeGameAndUI UIInputMode;
		pc->SetInputMode(UIInputMode);
		pc->bShowMouseCursor = true;
	}
}

void AValheimPlayer::PickUp()
{
	//InventoryComp->DetectPlayer();
	InventoryComp->PickUpItem();
}

void AValheimPlayer::InventoryModeOn()
{
	if (IsInventoryModeOn) {
		if (InventoryUI) {
			InventoryUI->RemoveFromParent();
		}
		IsInventoryModeOn = false;
		FInputModeGameOnly GameInputMode;
		pc->SetInputMode(GameInputMode);
		pc->bShowMouseCursor = false;
	}
	else {
		if (InventoryWidget)
		{
			InventoryUI = CreateWidget<UInventoryUI>(GetWorld(), InventoryWidget);
		}
		if (InventoryUI)
		{
			InventoryUI->AddToViewport();
			InventoryUI->LoadInventory(InventoryComp);
		}
		IsInventoryModeOn = true;

		FInputModeGameAndUI UIInputMode;
		pc->SetInputMode(UIInputMode);
		pc->bShowMouseCursor = true;
	}

}


