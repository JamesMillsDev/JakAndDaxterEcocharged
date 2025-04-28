// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/InputConfigDataAsset.h"

#include <EnhancedInputSubsystems.h>

UInputAction* UInputConfigDataAsset::Find(EEcoInputs ID)
{
	if(Mappings.Contains(ID))
	{
		return Mappings.FindChecked(ID);
	}

	return nullptr;
}

void UInputConfigDataAsset::BindContext(APlayerController* PC)
{
	if(UEnhancedInputLocalPlayerSubsystem* EnhancedInput = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
	{
		for(auto& Context : Contexts)
		{
			EnhancedInput->AddMappingContext(Context.Context, Context.Priority);
		}
	}
}
