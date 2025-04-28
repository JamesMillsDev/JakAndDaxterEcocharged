// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Player/EcoCharacter.h"

#include <Camera/CameraComponent.h>
#include <Components/CapsuleComponent.h>

#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>

// Sets default values
AEcoCharacter::AEcoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	JumpMaxCount = 2;

	if(UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->InitCapsuleSize(35.f, 90.f);

		CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Boom Arm"));
		CameraBoom->SetupAttachment(Capsule);
		CameraBoom->TargetArmLength = 400.f;
		CameraBoom->bUsePawnControlRotation = true;

		Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		Camera->SetupAttachment(CameraBoom);
	}

	if(UCharacterMovementComponent* Movement = GetCharacterMovement())
	{
		Movement->RotationRate = { 0, 0, 500.f };
		Movement->bOrientRotationToMovement = true;

		FNavAgentProperties& NavProperties = Movement->GetNavAgentPropertiesRef();
		NavProperties.bCanCrouch = true;
		NavProperties.bCanSwim = true;
	}
}