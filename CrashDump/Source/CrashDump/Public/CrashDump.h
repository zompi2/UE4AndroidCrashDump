// (c) 2017 Damian Nowakowski

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