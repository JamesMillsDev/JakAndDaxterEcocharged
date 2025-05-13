// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/EcoAttributeSet.h"

#include "Net/UnrealNetwork.h"

UEcoAttributeSet::UEcoAttributeSet()
{
}

void UEcoAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UEcoAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEcoAttributeSet, JumpPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEcoAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEcoAttributeSet, GreenEco, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEcoAttributeSet, EcoCharge, COND_None, REPNOTIFY_Always);
}

void UEcoAttributeSet::OnRep_MoveSpeed(FGameplayAttributeData& OldMoveSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEcoAttributeSet, MoveSpeed, OldMoveSpeed);
}

void UEcoAttributeSet::OnRep_JumpPower(FGameplayAttributeData& OldJumpPower)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEcoAttributeSet, JumpPower, OldJumpPower);
}

void UEcoAttributeSet::OnRep_Health(FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEcoAttributeSet, Health, OldHealth);
}

void UEcoAttributeSet::OnRep_GreenEco(FGameplayAttributeData& OldGreenEco)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEcoAttributeSet, GreenEco, OldGreenEco);
}

void UEcoAttributeSet::OnRep_EcoCharge(FGameplayAttributeData& OldEcoCharge)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEcoAttributeSet, EcoCharge, OldEcoCharge);
}