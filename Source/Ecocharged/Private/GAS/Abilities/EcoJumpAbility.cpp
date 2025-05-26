// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/EcoJumpAbility.h"

#include "AbilitySystemComponent.h"

#include "Actors/Player/EcoCharacter.h"

#include "GAS/EcoAbilitySystemComponent.h"

UEcoJumpAbility::UEcoJumpAbility()
	: UEcoGameplayAbility{ EEcoInputs::Jump }, JumpTimeSpacing{ 1.f }
{
}

void UEcoJumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	ActorInfo->AbilitySystemComponent->RemoveLooseGameplayTag(CanJumpTag);

	if (AEcoCharacter* Char = Cast<AEcoCharacter>(ActorInfo->AvatarActor))
	{
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(
			this, &UEcoJumpAbility::ResetJumpTimer, ActorInfo->AbilitySystemComponent
		);

		Char->GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.f, false);
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

bool UEcoJumpAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	return ActorInfo->AbilitySystemComponent->HasMatchingGameplayTag(CanJumpTag);
}

void UEcoJumpAbility::AbilityGranted(const FGameplayAbilitySpecHandle Handle, UEcoAbilitySystemComponent* AbilitySystem)
{
	CanJumpTag = FGameplayTag::RequestGameplayTag("Jak.Jump.Allowed");
	AbilitySystem->AddLooseGameplayTag(CanJumpTag);
}

void UEcoJumpAbility::ResetJumpTimer(TWeakObjectPtr<UAbilitySystemComponent> AbilitySystem)
{
	AbilitySystem->AddLooseGameplayTag(CanJumpTag);
}
