// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Player/EcoCharacter.h"

#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>

#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>

#include "Actors/Player/EcoPlayerController.h"

#include "GAS/EcoAbilitySystemComponent.h"
#include "GAS/EcoAttributeSet.h"

// Sets default values
AEcoCharacter::AEcoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	JumpMaxCount = 2;

	constexpr float CapsuleHeight = 85.f;

	if(UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->InitCapsuleSize(35.f, CapsuleHeight);

		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Boom Arm"));
		CameraBoom->SetupAttachment(Capsule);
		CameraBoom->TargetArmLength = 400.f;
		CameraBoom->bUsePawnControlRotation = true;
		CameraBoom->SetRelativeLocation({ 0.f, 0.f, 90.f });

		Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		Camera->SetupAttachment(CameraBoom);
		Camera->SetRelativeRotation({ -15.f, 0.f, 0.f });
	}

	if(UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->RotationRate = { 0, 0, 500.f };
		Movement->bOrientRotationToMovement = true;
		Movement->SetCrouchedHalfHeight(CapsuleHeight);
		Movement->bUseFlatBaseForFloorChecks = true;

		FNavAgentProperties& NavProperties = Movement->GetNavAgentPropertiesRef();
		NavProperties.bCanCrouch = true;
		NavProperties.bCanSwim = true;
	}

	CrouchedEyeHeight = BaseEyeHeight;
}

void AEcoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AEcoPlayerController* PC = Cast<AEcoPlayerController>(Controller))
	{
		ApplyMovementAttributes(PC->GetAttributes());
	}
}

void AEcoCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AEcoPlayerController* PC = Cast<AEcoPlayerController>(NewController))
	{
		PC->GetAbilitySystem()->InitAbilityActorInfo(PC, this);
	}

	SetOwner(NewController);
}

void AEcoCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (AEcoPlayerController* PC = Cast<AEcoPlayerController>(Controller))
	{
		PC->GetAbilitySystem()->InitAbilityActorInfo(PC, this);
	}
}

void AEcoCharacter::ApplyMovementAttributes(UEcoAttributeSet* MovementAttributes)
{
	if (UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->JumpZVelocity = MovementAttributes->GetJumpPower();
		Movement->MaxWalkSpeed = MovementAttributes->GetMoveSpeed();
		Movement->MaxWalkSpeedCrouched = Movement->MaxWalkSpeed * .5f;
	}
}
