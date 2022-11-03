﻿/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Wit/Request/WitResponse.h"
#include "TTS/Configuration/TtsConfiguration.h"
#include "TtsEvents.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSynthesizeResponseDelegate, const bool, bIsSuccessful, USoundWave*, SoundWave);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSynthesizeErrorDelegate, const FString&, ErrorMessage, const FString&, HumanReadableMessage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSynthesizeRawResponseDelegate, const FString&, ClipId, const TArray<uint8>&, BinaryData, const FTtsConfiguration&, ClipSettings);

/**
 * Container for all TTS events
 */
UCLASS(ClassGroup=(Meta))
class WIT_API UTtsEvents final : public UActorComponent
{
	GENERATED_BODY()

public:

	/**
	 * The response we receive from Wit requests parsed into UObject structures
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Transient, Category = "TTS")
	FWitVoicesResponse VoicesResponse{};

	/**
	 * Callback to call when a synthesize request has been fully processed. The callback receives the raw response data
	 */
	UPROPERTY(BlueprintAssignable)
	FOnSynthesizeRawResponseDelegate OnSynthesizeRawResponse{};
	
	/**
	 * Callback to call when a synthesize request has been fully processed. The callback receives a USoundWave containing the received wav
	 */
	UPROPERTY(BlueprintAssignable)
	FOnSynthesizeResponseDelegate OnSynthesizeResponse{};

	/**
	 * Callback to call when a synthesize error occurs
	 */
	UPROPERTY(BlueprintAssignable)
	FOnSynthesizeErrorDelegate OnSynthesizeError{};
	
};
