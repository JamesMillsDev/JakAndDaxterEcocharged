// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/EcoJumpAbility.h"

#include "Actors/Player/EcoCharacter.h"

UEcoJumpAbility::UEcoJumpAbility()
	: UEcoGameplayAbility{ EEcoInputs::Jump }
{
}

void UEcoJumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (AEcoCharacter* Char = Cast<AEcoCharacter>(ActorInfo->AvatarActor))
	{
		Char->Jump();
	}
}

void UEcoJumpAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if(AEcoCharacter* Char = Cast<AEcoCharacter>(ActorInfo->AvatarActor))
	{
		Char->StopJumping();
	}
}
