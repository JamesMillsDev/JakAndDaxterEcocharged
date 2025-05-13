// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/Player/EcoPlayerController.h"

#include <EnhancedInputComponent.h>

#include "Actors/Player/EcoCharacter.h"
#include "Actors/Player/EcoPlayerCameraManager.h"

#include "Framework/InputConfigDataAsset.h"

#include "GAS/EcoAbilitySystemComponent.h"
#include "GAS/EcoAttributeSet.h"
#include "GAS/Abilities/EcoGameplayAbility.h"

AEcoPlayerController::AEcoPlayerController()
{
	PlayerCameraManagerClass = AEcoPlayerCameraManager::StaticClass();

	AbilitySystem = CreateDefaultSubobject<UEcoAbilitySystemComponent>(TEXT("Ability System"));
	AbilitySystem->SetIsReplicated(true);
	AbilitySystem->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	Attributes = CreateDefaultSubobject<UEcoAttributeSet>(TEXT("Attributes"));
}

void AEcoPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AEcoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(!IsValid(InputConfig))
	{
		return;
	}

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		const FTopLevelAssetPath AssetPath = FTopLevelAssetPath(
			FName("/Script/Ecocharged"),
			FName("EEcoInputs")
		);

		AbilitySystem->BindAbilityActivationToInputComponent(InputComponent,
			FGameplayAbilityInputBinds(
				FString("ConfirmTarget"),
				FString("CancelTarget"),
				AssetPath,
				static_cast<int32>(EEcoInputs::Confirm),
				static_cast<int32>(EEcoInputs::Cancel)
			)
		);

		if(const UInputAction* Action = InputConfig->Find(EEcoInputs::Move))
		{
			EnhancedInput->BindAction(Action, ETriggerEvent::Triggered, this, &AEcoPlayerController::Move);
		}

		if (const UInputAction* Action = InputConfig->Find(EEcoInputs::Look))
		{
			EnhancedInput->BindAction(Action, ETriggerEvent::Triggered, this, &AEcoPlayerController::Look);
		}

		for (TSubclassOf<UEcoGameplayAbility> AbilityClass : DefaultAbilities)
		{
			if (!AbilityClass)
			{
				continue;
			}

			if (const UEcoGameplayAbility* Ability = AbilityClass.GetDefaultObject())
			{
				Ability->Bind(InputConfig,
					EnhancedInput,
					this,
					&AEcoPlayerController::ActivateAbility,
					&AEcoPlayerController::EndAbility);
			}
		}
	}
}

void AEcoPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	CurrentCharacter = Cast<AEcoCharacter>(P);

	if (IsValid(CurrentCharacter))
	{
		InitializeAttributes();
		GiveAbilities();
	}

	if (IsValid(InputConfig))
	{
		InputConfig->BindContext(this);
	}
}

void AEcoPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitializeAttributes();
}

void AEcoPlayerController::InitializeAttributes()
{
	if (DefaultAttributes)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		const FGameplayEffectSpecHandle SpecHandle = AbilitySystem->MakeOutgoingSpec(
			DefaultAttributes, 1, EffectContext
		);

		if (SpecHandle.IsValid())
		{
			AbilitySystem->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void AEcoPlayerController::GiveAbilities()
{
	if (DefaultAbilities.Num() > 0 && HasAuthority())
	{
		for (TSubclassOf<UEcoGameplayAbility> DefaultAbility : DefaultAbilities)
		{
			if (DefaultAbility)
			{
				AbilitySystem->GiveAbility(
					FGameplayAbilitySpec(
						DefaultAbility.Get(), 
						1,
						static_cast<int32>(DefaultAbility.GetDefaultObject()->ID()), 
						this
					)
				);
			}
		}
	}
}

void AEcoPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (IsValid(CurrentCharacter))
	{
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation = { 0.f, Rotation.Yaw, 0.f };

		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		CurrentCharacter->AddMovementInput(Forward, MovementVector.Y);
		CurrentCharacter->AddMovementInput(Right, MovementVector.X);
	}
}

void AEcoPlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();

	if (IsValid(CurrentCharacter))
	{
		CurrentCharacter->AddControllerYawInput(LookVector.X);
		CurrentCharacter->ApplyZoom(LookVector.Y);
	}
}

void AEcoPlayerController::ActivateAbility(int32 AbilityID)
{
	AbilitySystem->AbilityLocalInputPressed(AbilityID);
}

void AEcoPlayerController::EndAbility(int32 AbilityID)
{
	AbilitySystem->AbilityLocalInputReleased(AbilityID);
}
