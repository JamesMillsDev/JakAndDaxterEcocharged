// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "EcoAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class ECOCHARGED_API UEcoAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(UEcoAttributeSet, MoveSpeed);

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	FGameplayAttributeData JumpPower;
	ATTRIBUTE_ACCESSORS(UEcoAttributeSet, JumpPower);

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UEcoAttributeSet, Health);

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	FGameplayAttributeData GreenEco;
	ATTRIBUTE_ACCESSORS(UEcoAttributeSet, GreenEco);

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	FGameplayAttributeData EcoCharge;
	ATTRIBUTE_ACCESSORS(UEcoAttributeSet, EcoCharge);

public:
	UEcoAttributeSet();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_MoveSpeed(FGameplayAttributeData& OldMoveSpeed);
	UFUNCTION()
	virtual void OnRep_JumpPower(FGameplayAttributeData& OldJumpPower);
	UFUNCTION()
	virtual void OnRep_Health(FGameplayAttributeData& OldHealth);
	UFUNCTION()
	virtual void OnRep_GreenEco(FGameplayAttributeData& OldGreenEco);
	UFUNCTION()
	virtual void OnRep_EcoCharge(FGameplayAttributeData& OldEcoCharge);
	
};
