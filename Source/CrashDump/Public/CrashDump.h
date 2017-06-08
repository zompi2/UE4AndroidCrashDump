// zompi 2014-2017 all rights reserverd

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"

class FCrashDumpModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};