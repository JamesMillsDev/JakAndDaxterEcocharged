// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Framework/EcoInputs.h"
#include "InputConfigDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FMappingData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	class UInputMappingContext* Context;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	int32 Priority;
	
};

/**
 *
 */
UCLASS()
class ECOCHARGED_API UInputConfigDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	class UInputAction* Find(EEcoInputs ID);
	void BindContext(class APlayerController* PC);

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TMap<EEcoInputs, class UInputAction*> Mappings;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TArray<FMappingData> Contexts;

};
