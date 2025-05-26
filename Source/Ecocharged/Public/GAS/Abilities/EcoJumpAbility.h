// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/EcoGameplayAbility.h"
#include "EcoJumpAbility.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ECOCHARGED_API UEcoJumpAbility : public UEcoGameplayAbility
{
	GENERATED_BODY()

public:
	UEcoJumpAbility();

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = true))
	float JumpTimeSpacing;

private:
	FTimerHandle TimerHandle;

	UPROPERTY()
	FGameplayTag CanJumpTag;

private:
	virtual void AbilityGranted(const FGameplayAbilitySpecHandle Handle, UEcoAbilitySystemComponent* AbilitySystem) override;
	void ResetJumpTimer(TWeakObjectPtr<UAbilitySystemComponent> AbilitySystem);

};
