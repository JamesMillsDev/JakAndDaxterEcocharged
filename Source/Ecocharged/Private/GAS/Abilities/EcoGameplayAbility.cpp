// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/EcoGameplayAbility.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"

#include "Framework/InputConfigDataAsset.h"

#include "GAS/EcoAbilitySystemComponent.h"

void UEcoGameplayAbility::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UEcoGameplayAbility::GrantAbility(const TSubclassOf<UEcoGameplayAbility>& AbilityClass, UEcoAbilitySystemComponent* AbilitySystem, int32 Level, UObject* SourceObject)
{
	FGameplayAbilitySpecHandle Handle = AbilitySystem->GiveAbility(
		FGameplayAbilitySpec(
			AbilityClass,
			Level,
			static_cast<int32>(AbilityID),
			SourceObject
		)
	);

	if (Handle.IsValid())
	{
		if (FGameplayAbilitySpec* Spec = AbilitySystem->FindAbilitySpecFromHandle(Handle))
		{
			if (UEcoGameplayAbility* Ability = Cast<UEcoGameplayAbility>(Spec->Ability))
			{
				Ability->AbilityGranted(Handle, AbilitySystem);
			}
		}
	}
}

void UEcoGameplayAbility::Bind(UInputConfigDataAsset* InputConfig, UEnhancedInputComponent* EnhancedInput,
	AEcoPlayerController* Controller, void(AEcoPlayerController::* StartedFunc)(const int32),
	void(AEcoPlayerController::* EndedFunc)(const int32)) const
{
	if (const UInputAction* Action = InputConfig->Find(AbilityID))
	{
		EnhancedInput->BindAction(Action, ETriggerEvent::Started, Controller, StartedFunc, (int32)AbilityID);
		EnhancedInput->BindAction(Action, ETriggerEvent::Canceled, Controller, EndedFunc, (int32)AbilityID);
		EnhancedInput->BindAction(Action, ETriggerEvent::Completed, Controller, EndedFunc, (int32)AbilityID);
	}
}

UEcoGameplayAbility::UEcoGameplayAbility()
	: AbilityID{ EEcoInputs::None }
{
}

UEcoGameplayAbility::UEcoGameplayAbility(EEcoInputs ID)
	: AbilityID{ ID }
{
}

void UEcoGameplayAbility::AbilityGranted(const FGameplayAbilitySpecHandle Handle, UEcoAbilitySystemComponent* AbilitySystem)
{
}