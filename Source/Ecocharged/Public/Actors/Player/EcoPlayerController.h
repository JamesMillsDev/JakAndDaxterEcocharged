// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "EcoPlayerController.generated.h"

/**
 *
 */
UCLASS()
class ECOCHARGED_API AEcoPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AEcoPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void AcknowledgePossession(APawn* P) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Input, meta = (AllowPrivateAccess = true))
	class UInputConfigDataAsset* InputConfig;

	UPROPERTY()
	class AEcoCharacter* CurrentCharacter;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

};
