// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "Actors/Player/EcoPlayerController.h"

#include "Framework/EcoInputs.h"

#include "EcoGameplayAbility.generated.h"

/**
 * 
 */
UCLASS(Abstract, NotBlueprintable)
class ECOCHARGED_API UEcoGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	FORCEINLINE EEcoInputs ID() const { return AbilityID; }

public:
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	void GrantAbility(const TSubclassOf<UEcoGameplayAbility>& AbilityClass, UEcoAbilitySystemComponent* AbilitySystem, int32 Level, UObject* SourceObject);

	void Bind(class UInputConfigDataAsset* InputConfig, class UEnhancedInputComponent* EnhancedInput, AEcoPlayerController* Controller,
		void(AEcoPlayerController::* StartedFunc)(const int32), void(AEcoPlayerController::* EndedFunc)(const int32)) const;

protected:
	EEcoInputs AbilityID;

protected:
	UEcoGameplayAbility();
	UEcoGameplayAbility(EEcoInputs ID);

protected:
	virtual void AbilityGranted(const FGameplayAbilitySpecHandle Handle, UEcoAbilitySystemComponent* AbilitySystem);

};
