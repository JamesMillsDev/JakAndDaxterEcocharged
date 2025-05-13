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
	FORCEINLINE TSubclassOf<class UGameplayEffect> GetDefaultAttributes() const { return DefaultAttributes; }
	FORCEINLINE TArray<TSubclassOf<class UEcoGameplayAbility>> GetDefaultAbilities() const { return DefaultAbilities; }
	FORCEINLINE class UEcoAbilitySystemComponent* GetAbilitySystem() const { return AbilitySystem; }
	FORCEINLINE class UEcoAttributeSet* GetAttributes() const { return Attributes; }

public:
	AEcoPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void AcknowledgePossession(APawn* P) override;
	virtual void OnRep_PlayerState() override;

	virtual void InitializeAttributes();
	virtual void GiveAbilities();

private:
	UPROPERTY(EditDefaultsOnly, Category = Input, meta = (AllowPrivateAccess = true))
	class UInputConfigDataAsset* InputConfig;

	UPROPERTY(EditDefaultsOnly, Category = "GAS", meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<class UEcoGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "GAS", meta = (AllowPrivateAccess = true))
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = true))
	class UEcoAbilitySystemComponent* AbilitySystem;

	UPROPERTY(EditDefaultsOnly, Category = Components, meta = (AllowPrivateAccess = true))
	class UEcoAttributeSet* Attributes;

	UPROPERTY()
	class AEcoCharacter* CurrentCharacter;

private:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void ActivateAbility(int32 AbilityID);
	void EndAbility(int32 AbilityID);

};
