#include <windows.h>
#include <stdio.h>
#include <afx.h>
SERVICE_STATUS ServiceStatus;
SERVICE_STATUS_HANDLE hStatus;

void ServiceMain(int argc, char** argv);
void ControlHandler(DWORD request);
int InitService();
char serviceName[] = "TestApp";
bool installService();
bool uninstallService();

int main()
{
	SERVICE_TABLE_ENTRY ServiceTable[2];
	ServiceTable[0].lpServiceName = (LPWSTR)(CString(serviceName).AllocSysString());
	ServiceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceMain;

	ServiceTable[1].lpServiceName = NULL;
	ServiceTable[1].lpServiceName = NULL;

	StartServiceCtrlDispatcher(ServiceTable);
	return 0;
}

int InitService()
{
	OutputDebugString("Monitoring started.");
	return 0;
}

void ControlHandler(DWORD request)
{
	switch (request)
	{
	case SERVICE_CONTROL_STOP:
		OutputDebugString("TestApp stopped.");
		ServiceStatus.dwWin32ExitCode = 0;
		ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		SetServiceStatus(hStatus, &ServiceStatus);
		return;
	case SERVICE_CONTROL_SHUTDOWN:
		OutputDebugString("Test App Sropped");
		ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		SetServiceStatus(hStatus, &ServiceStatus);
		return;
	default:
		break;
	}

	SetServiceStatus(hStatus, &ServiceStatus);
	return;
}

void ServiceMain(int argc, char** argv)
{
	ServiceStatus.dwServiceType = SERVICE_WIN32;
	ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_STOP;
	ServiceStatus.dwWin32ExitCode = 0;
	ServiceStatus.dwServiceSpecificExitCode = 0;
	ServiceStatus.dwCheckPoint = 0;
	ServiceStatus.dwWaitHint = 0;
	
	/* 注册服务控制函数 */
	hStatus = RegisterServiceCtrlHandler(serviceName, (LPHANDLER_FUNCTION)ControlHandler);

	/* 如果注册失败，服务直接退出 */
	if (hStatus == (SERVICE_STATUS_HANDLE)0)
	{
		OutputDebugString("Register Service Control Handler");
		return;
	}

	//向SCM报告运行状态
	ServiceStatus.dwCurrentState = SERVICE_RUNNING;
	SetServiceStatus(hStatus, &ServiceStatus);

	while (ServiceStatus.dwCurrentState == SERVICE_RUNNING)
	{
		//TODO
	}


}

bool installService()
{
	SC_HANDLE hSCM, AppService;
	bool success = false;

	hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ENUMERATE_SERVICE | SC_MANAGER_CREATE_SERVICE);
	if (!hSCM)
	{
		OutputDebugString("Open SCManager failed.");
		return false;
	}

	//AppService = CreateService(hSCM, serviceName, serviceName, SERVICE_ALL_ACCESS | SERVICE_STOP, SERVICE_WIN32_OWN_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_NORMAL, )
}