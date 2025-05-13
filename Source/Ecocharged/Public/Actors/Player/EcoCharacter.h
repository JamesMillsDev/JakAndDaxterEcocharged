// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EcoCharacter.generated.h"

UCLASS()
class ECOCHARGED_API AEcoCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

public:
	// Sets default values for this character's properties
	AEcoCharacter();

public:
	void ApplyZoom(float Amount);

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual void ApplyMovementAttributes(class UEcoAttributeSet* MovementAttributes);

private:
	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = true))
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = true))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = true))
	float CameraZoomMin;

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = true))
	float CameraZoomMax;

};
