/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "WitModule.h"
#include "Curl/CurlHttpManager.h"
#include "Misc/EngineVersionComparison.h"
#include "Wit/Utilities/WitLog.h"

#define LOCTEXT_NAMESPACE "FWitModule"

IMPLEMENT_MODULE(FWitModule, Wit)

FWitModule* FWitModule::Singleton = nullptr;

/**
 * Perform module initialization. We initialize our custom HTTP manager that
 * is used to handle streaming Wit.ai requests
 */
void FWitModule::StartupModule()
{
	Singleton = this;
	
	if (HttpManager == nullptr)
	{
		FCurlHttpManager::InitCurl();

		HttpManager = new FCurlHttpManager();
		HttpManager->Initialize();
	}
}

/**
 * Perform module cleanup
 */
void FWitModule::ShutdownModule()
{
	if (HttpManager != nullptr)
	{
#if UE_VERSION_OLDER_THAN(5,0,0)
		HttpManager->Flush(true);
#else
		HttpManager->Flush(EHttpFlushReason::Shutdown);
#endif
		delete HttpManager;
	}
	
	HttpManager = nullptr;
	Singleton = nullptr;
}

/**
 * Retrieve singleton access to the module
 */
FWitModule& FWitModule::Get()
{
	if (Singleton == nullptr)
	{
		check(IsInGameThread());
		FModuleManager::LoadModuleChecked<FWitModule>("Wit");
	}
	
	check(Singleton != nullptr);
	return *Singleton;
}

#undef LOCTEXT_NAMESPACE