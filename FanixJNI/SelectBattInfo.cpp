#include "stdafx.h"
#include <atlstr.h>
#include "cn_sgool_dll_SelectBattInfo.h"

using namespace std;
using namespace System;

typedef int(__stdcall* ConnectToAppServer)(HANDLE hLoginHand, char* pServerIP, int iServePort);
typedef int(__stdcall* GetTrayBattInfoDC)(HANDLE hLoginHand, char* pServerIP, int iServePort, char* pPalletID, __int64 iRFID);
typedef int(__stdcall* GetTrayBattInfoDC2)(HANDLE hLoginHand, char* pServerIP, int iServePort, char* pPalletID, __int64 iRFID);


JNIEXPORT jint JNICALL Java_cn_sgool_dll_SelectBattInfo_connectToAppServer(JNIEnv *env, jobject obj, jstring jServerIP, jstring jServerPort)
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
	HINSTANCE hInstance = LoadLibrary(_T("fxSelectBattInfo.dll"));
	BOOL bQueryResult;
	if (hInstance != NULL)
	{
		ConnectToAppServer  QueryConnectToAppServer;

		HANDLE m_hWnd = GetCurrentProcess();
		printf("Handle is %u\n", (unsigned int)m_hWnd);

		QueryConnectToAppServer = (ConnectToAppServer)GetProcAddress(hInstance, "ConnectToAppServer");
		
		try
		{			
			bQueryResult = QueryConnectToAppServer(m_hWnd, serverIP, serverPort);
			printf("QueryConnectToAppServer Completed!\n");

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
	return (jint)bQueryResult;
}


JNIEXPORT jint JNICALL Java_cn_sgool_dll_SelectBattInfo_getTrayBattInfoDC(JNIEnv *env, jobject obj, jstring jServerIP, jstring jServerPort, jstring jTrayId, jstring jTrayRfid)
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
	HINSTANCE hInstance = LoadLibrary(_T("fxSelectBattInfo.dll"));
	int iQueryResult;
	if (hInstance != NULL)
	{
		GetTrayBattInfoDC  QueryGetDC1Data;

		HANDLE m_hWnd = GetCurrentProcess();
		printf("Handle is %u\n", (unsigned int)m_hWnd);

		QueryGetDC1Data = (GetTrayBattInfoDC)GetProcAddress(hInstance, "GetTrayBattInfoDC");

		try
		{
			iQueryResult = QueryGetDC1Data(m_hWnd, serverIP, serverPort, trayId, trayRfid);
			printf("QueryGetTrayBattInfoDC1 Completed!\n");

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
	return (jint)iQueryResult;
}

JNIEXPORT jint JNICALL Java_cn_sgool_dll_SelectBattInfo_getTrayBattInfoDC2(JNIEnv *env, jobject obj, jstring jServerIP, jstring jServerPort, jstring jTrayId, jstring jTrayRfid)
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
	HINSTANCE hInstance = LoadLibrary(_T("fxSelectBattInfo.dll"));
	int iQueryResult;
	if (hInstance != NULL)
	{
		GetTrayBattInfoDC  QueryGetDC2Data;

		HANDLE m_hWnd = GetCurrentProcess();
		printf("Handle is %u\n", (unsigned int)m_hWnd);

		QueryGetDC2Data = (GetTrayBattInfoDC2)GetProcAddress(hInstance, "GetTrayBattInfoDC");

		try
		{
			iQueryResult = QueryGetDC2Data(m_hWnd, serverIP, serverPort, trayId, trayRfid);
			printf("QueryGetTrayBattInfoDC2 Completed!\n");

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
	return (jint)iQueryResult;
}