// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Player/EcoPlayerController.h"

#include "Actors/Player/EcoCharacter.h"
#include "Actors/Player/EcoPlayerCameraManager.h"

#include <EnhancedInputComponent.h>
#include <Framework/InputConfigDataAsset.h>
#include <GameFramework/Character.h>

AEcoPlayerController::AEcoPlayerController()
{
	PlayerCameraManagerClass = AEcoPlayerCameraManager::StaticClass();
}

void AEcoPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AEcoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(!IsValid(InputConfig))
	{
		return;
	}

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if(const UInputAction* Action = InputConfig->Find(EEcoInputs::Move))
		{
			EnhancedInput->BindAction(Action, ETriggerEvent::Triggered, this, &AEcoPlayerController::Move);
		}

		if (const UInputAction* Action = InputConfig->Find(EEcoInputs::Look))
		{
			EnhancedInput->BindAction(Action, ETriggerEvent::Triggered, this, &AEcoPlayerController::Look);
		}

		if (const UInputAction* Action = InputConfig->Find(EEcoInputs::Jump))
		{
			EnhancedInput->BindAction(Action, ETriggerEvent::Started, CurrentCharacter, &ACharacter::Jump);
			EnhancedInput->BindAction(Action, ETriggerEvent::Completed, CurrentCharacter, &ACharacter::StopJumping);
			EnhancedInput->BindAction(Action, ETriggerEvent::Canceled, CurrentCharacter, &ACharacter::StopJumping);
		}
	}
}

void AEcoPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	CurrentCharacter = Cast<AEcoCharacter>(P);

	if (IsValid(InputConfig))
	{
		InputConfig->BindContext(this);
	}
}

void AEcoPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (IsValid(CurrentCharacter))
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation = { 0.f, Rotation.Yaw, 0.f };

		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		CurrentCharacter->AddMovementInput(Forward, MovementVector.Y);
		CurrentCharacter->AddMovementInput(Right, MovementVector.X);
	}
}

void AEcoPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();

	if (IsValid(CurrentCharacter))
	{
		CurrentCharacter->AddControllerYawInput(LookVector.X);
	}
}
