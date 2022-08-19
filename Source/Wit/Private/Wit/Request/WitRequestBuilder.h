/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "CoreMinimal.h"
#include "Wit/Request/WitRequestTypes.h"

struct FWitRequestConfiguration;

/**
 * Helper class for constructing valid request configurations
 */
class FWitRequestBuilder
{
public:

    /**
     * Setup a configuration with required information
     *
     * @param Configuration [in,out] the request configuration to fill in
     * @param Endpoint [in] the endpoint we want to use
     * @param ServerAuthToken [in] the server auth token for our application (this can be retrieved from the setup in Wit.ai)
     * @param Version [in] the version string we want to use. This can be left empty in which case it will use the latest version
     * @param CustomUrl [in] the custom base URL to use. Normally this should be left empty to use the default Wit.ai URL
     */
	static void SetRequestConfigurationWithDefaults(FWitRequestConfiguration& Configuration, const EWitRequestEndpoint Endpoint, const FString& ServerAuthToken, const FString& Version, const FString& CustomUrl);
	
	/**
	 * Add a text URL parameter. This is required when using the /message endpoint
	 *
	 * @param Configuration [in,out] the request configuration to fill in
	 * @param EncodedText [in] the URL encoded text to use as a parameter
	 */
	static void AddTextParameter(FWitRequestConfiguration& Configuration, const FString& EncodedText);

	/**
	 * Add a Mime format accept type. This is required for the /synthesize endpoint
	 *
	 * @param Configuration [in,out] the request configuration to fill in
	 * @param Format [in] the desired accept format
	 */
	static void AddFormatAccept(FWitRequestConfiguration& Configuration, const EWitRequestFormat Format);

	/**
	 * Add an audio format content type. This is required when using the /speech endpoint
	 *
	 * @param Configuration [in,out] the request configuration to fill in
	 * @param Format [in] the desired content format
	 */
	static void AddFormatContentType(FWitRequestConfiguration& Configuration, const EWitRequestFormat Format);

	/**
	 * Add an audio encoding type. This is required when using the /speech endpoint
	 *
	 * @param Configuration [in,out] the request configuration to fill in
	 * @param Encoding [in] the desired audio encoding
	 */
	static void AddEncodingContentType(FWitRequestConfiguration& Configuration, const EWitRequestEncoding Encoding);

	/**
	 * Add an audio sample size type. This is required when using the /speech endpoint
	 *
	 * @param Configuration [in,out] the request configuration to fill in
	 * @param SampleSize [in] the desired audio sample size
	 */
	static void AddSampleSizeContentType(FWitRequestConfiguration& Configuration, const EWitRequestSampleSize SampleSize);

	/**
	 * Add an audio rate type. This is required when using the /speech endpoint
	 *
	 * @param Configuration [in,out] the request configuration to fill in
	 * @param Rate [in] the desired audio sample rate. Not all rates are necessarily valid and only rates > 0 will be accepted
	 */
	static void AddRateContentType(FWitRequestConfiguration& Configuration, const int32 Rate);

	/**
	 * Add an audio endianness type. This is required when using the /speech endpoint
	 *
	 * @param Configuration [in,out] the request configuration to fill in
	 * @param Endian [in] the desired audio endianness
	 */
	static void AddEndianContentType(FWitRequestConfiguration& Configuration, const EWitRequestEndian Endian);

private:

    /**
     * Converts an endpoint into its final string representation
     *
     * @param Endpoint [in] the endpoint
     * @return the string representation of the endpoint
     */
	static const FString& GetEndpointString(const EWitRequestEndpoint Endpoint);

	/**
     * Converts an audio format into its final string representation
     *
     * @param Format [in] the audio format
     * @return the string representation of the audio format
     */
	static const FString& GetFormatString(const EWitRequestFormat Format);

	/**
     * Converts an audio encoding into its final string representation
     *
     * @param Encoding [in] the audio encoding
     * @return the string representation of the audio encoding
     */
	static const FString& GetEncodingString(const EWitRequestEncoding Encoding);

	/**
     * Converts an audio sample size into its final string representation
     *
     * @param SampleSize [in] the audio sample size
     * @return the string representation of the audio sample size
     */
	static const FString& GetSampleSizeString(const EWitRequestSampleSize SampleSize);

	/**
     * Converts an audio endianness into its final string representation
     *
     * @param Endian [in] the audio endianness
     * @return the string representation of the audio endianness
     */
	static const FString& GetEndianString(const EWitRequestEndian Endian);
	
	/** Default wit.ai URL */
	static const FString UrlDefault;

	/** Supported wit.ai endpoints */
	static const FString EndpointSpeech;
	static const FString EndpointMessage;
	static const FString EndpointSynthesize;
	static const FString EndpointVoices;

	/** Supported wit.ai parameters */
	static const FString ParameterTextKey;
	
	/** Supported wit.ai audio formats */
	static const FString FormatKey;
	static const FString FormatValueRaw;
	static const FString FormatValueWav;
	static const FString FormatValueJson;

	/** Supported wit.ai audio encodings */
	static const FString EncodingKey;
	static const FString EncodingValueFloatingPoint;
	static const FString EncodingValueSignedInteger;
	static const FString EncodingValueUnsignedInteger;

	/** Supported wit.ai audio sample sizes */
	static const FString SampleSizeKey;
	static const FString SampleSizeValueByte;
	static const FString SampleSizeValueWord;
	static const FString SampleSizeValueDword;

	/** Supported wit.ai audio sample rates */
	static const FString RateKey;

	/** Supported wit.ai audio endianness */
	static const FString EndianKey;
	static const FString EndianValueLittle;
	static const FString EndianValueBig;
};
