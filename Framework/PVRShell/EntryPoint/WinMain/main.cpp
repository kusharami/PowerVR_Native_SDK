/*!
\brief Application entry point for Microsoft Windows systems.
\file PVRShell/EntryPoint/WinMain/main.cpp
\author PowerVR by Imagination, Developer Technology Team
\copyright Copyright (c) Imagination Technologies Limited.
*/
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "PVRShell/OS/ShellOS.h"
#include "PVRShell/StateMachine.h"
#include "PVRShell/CommandLine.h"
#include "PVRCore/Interfaces/IPlatformContext.h"
#include "PVRShell/OS/Windows/WindowsOSData.h"
#include <windows.h>
#include <io.h>

#if !defined(UNDER_CE)
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE , LPWSTR lpCmdLine, int nCmdShow)
#endif
{
	int retval;
	{
#if defined(_WIN32) && !defined(UNDER_CE) && defined(_DEBUG)
		// Enable memory-leak reports
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_EVERY_16_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));
#endif
		pvr::platform::WindowsOSData data;
		data.cmdShow = nCmdShow;

		pvr::platform::CommandLineParser commandLine;
		commandLine.set(lpCmdLine);

		pvr::platform::StateMachine stateMachine(hInstance, commandLine, &data);

		stateMachine.init();

		// Enter our loop
		retval = (stateMachine.execute() == pvr::Result::Success) ? 0 : 1;
	}
	//_CrtDumpMemoryLeaks();
	return retval;
}