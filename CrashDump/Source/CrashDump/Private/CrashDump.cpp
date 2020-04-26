// (c) 2017 Damian Nowakowski

#include "CrashDump.h"

#if PLATFORM_ANDROID
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)

#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include <android_native_app_glue.h>

#include "client/linux/handler/exception_handler.h"
#include "client/linux/handler/minidump_descriptor.h"

#endif
#endif

#define LOCTEXT_NAMESPACE "FCrashDumpModule"

#if PLATFORM_ANDROID
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)

static google_breakpad::ExceptionHandler* exceptionHandler;
bool DumpCallback(const google_breakpad::MinidumpDescriptor& descriptor, void* context, bool succeeded)
{
	FPlatformMisc::LowLevelOutputDebugStringf(TEXT("Dumping Callstack (%i): %s"), succeeded, descriptor.path());
	return succeeded;
}

extern "C" void Java_com_epicgames_ue4_GameActivity_setUpBreakpad(JNIEnv* env, jobject obj, jstring filepath)
{
	const char *path = env->GetStringUTFChars(filepath, 0);
	FPlatformMisc::LowLevelOutputDebugStringf(TEXT("Running Java_com_epicgames_ue4_GameActivity_setUpBreakpad: %s"), path);
	google_breakpad::MinidumpDescriptor descriptor(path);
	exceptionHandler = new google_breakpad::ExceptionHandler(descriptor, NULL, DumpCallback, NULL, true, -1);
}

#endif
#endif

void FCrashDumpModule::StartupModule()
{
}

void FCrashDumpModule::ShutdownModule()
{
}
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCrashDumpModule, CrashDump)