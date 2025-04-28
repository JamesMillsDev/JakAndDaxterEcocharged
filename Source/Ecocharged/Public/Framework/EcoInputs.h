#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EEcoInputs : uint8
{
	None,
	Confirm,
	Cancel,
	Move,
	Look,
	Jump,
	Crouch,
	Sprint,
	Punch,
	Spin,
	Zoom,
	ShowHUD,
	Pause
};