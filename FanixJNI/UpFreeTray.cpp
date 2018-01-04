#include "stdafx.h"
#include <atlstr.h>
#include "cn_sgool_dll_UpFreeTray.h"

using namespace std;

typedef int(__stdcall* ConnectToAppServer)(HANDLE hLoginHand, char* pServerIP, int iServePort);
typedef int(__stdcall* UpFreeTray)(HANDLE hLoginHand, char* pServerIP, int iServePort, char* pPalletID, __int64 iRFID);


JNIEXPORT jint JNICALL Java_cn_sgool_dll_UpFreeTray_connectToAppServer(JNIEnv *env, jobject obj, jstring jServerIP, jstring jServerPort)
{
	char* serverIP;
	int serverPort;

	serverIP = (char*)env->GetStringUTFChars(jServerIP, 0);
	serverPort = atoi((char*)env->GetStringUTFChars(jServerPort, 0));

	//加载登录DLL，检查数据库连接
	printf("********************************************\n");
	printf("Native interface start!\n");
	printf("ServerIP: %s\n", serverIP);
	printf("ServerPort: %d\n", serverPort);
	HINSTANCE hInstance = LoadLibrary(_T("fxUpFreeTray.dll"));
	BOOL bFreeResult;
	if (hInstance != NULL)
	{
		ConnectToAppServer  FreeConnectToAppServer;

		HANDLE m_hWnd = GetCurrentProcess();
		printf("Handle is %u\n", (unsigned int)m_hWnd);

		FreeConnectToAppServer = (ConnectToAppServer)GetProcAddress(hInstance, "ConnectToAppServer");

		try
		{
			bFreeResult = FreeConnectToAppServer(m_hWnd, serverIP, serverPort);
			printf("FreeConnectToAppServer Completed!\n");

		}
		catch (...)
		{
			printf("Connection failed!");
		}
	}
	else
	{
		printf("Load failed!");
	}
	FreeLibrary(hInstance);
	printf("********************************************\n");
	return (jint)bFreeResult;
}


JNIEXPORT jint JNICALL Java_cn_sgool_dll_UpFreeTray_upFreeTray(JNIEnv *env, jobject obj, jstring jServerIP, jstring jServerPort, jstring jTrayId, jstring jTrayRfid)
{
	char* serverIP;
	int serverPort;
	char* trayId;
	__int64 trayRfid;

	serverIP = (char*)env->GetStringUTFChars(jServerIP, 0);
	serverPort = atoi((char*)env->GetStringUTFChars(jServerPort, 0));
	trayId = (char*)env->GetStringUTFChars(jTrayId, 0);
	trayRfid = _atoi64((char*)env->GetStringUTFChars(jTrayRfid, 0));


	//加载登录DLL，检查数据库连接
	printf("********************************************\n");
	printf("Native interface start!\n");
	printf("ServerIP: %s\n", serverIP);
	printf("ServerPort: %d\n", serverPort);
	HINSTANCE hInstance = LoadLibrary(_T("fxUpFreeTray.dll"));
	int iFreeResult;
	if (hInstance != NULL)
	{
		UpFreeTray FreeUpFreeTray;

		HANDLE m_hWnd = GetCurrentProcess();
		printf("Handle is %u\n", (unsigned int)m_hWnd);

		FreeUpFreeTray = (UpFreeTray)GetProcAddress(hInstance, "upFreeTray");

		try
		{
			iFreeResult = FreeUpFreeTray(m_hWnd, serverIP, serverPort, trayId, trayRfid);
			printf("FreeUpFreeTray Completed!\n");

		}

		catch (...)
		{
			printf("Connection failed!");
		}
	}
	else
	{
		printf("Load failed!");
	}

	FreeLibrary(hInstance);
	printf("********************************************\n");
	return (jint)iFreeResult;
}