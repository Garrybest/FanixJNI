#include "stdafx.h"
#include <atlstr.h>
#include "cn_sgool_dll_Classify.h"

using namespace std;

typedef int(__stdcall* ConnectToAppServer)(HANDLE hLoginHand, char* pServerIP, int iServePort);
typedef int(__stdcall* UpOCVFXResult16)(HANDLE hLoginHand, char* pServerIP, int iServePort, int iDataType, char* pPalletID, __int64 iRFID, char* pFilePath);
typedef int(__stdcall* UpOCVFXResultMany)(HANDLE hLoginHand, char* pServerIP, int iServePort, char* pPalletID, __int64 iRFID, char* pFilePath, int iDataType, int iOCVNum);


JNIEXPORT jint JNICALL Java_cn_sgool_dll_Classify_connectToAppServer(JNIEnv *env, jobject obj, jstring jServerIP, jstring jServerPort)
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
	HINSTANCE hInstance = LoadLibrary(_T("fxClassifyDLL.dll"));
	BOOL bClassifyResult;
	if (hInstance != NULL)
	{
		ConnectToAppServer  ClassifyConnectToAppServer;

		HANDLE m_hWnd = GetCurrentProcess();
		printf("Handle is %u\n", (unsigned int)m_hWnd);

		ClassifyConnectToAppServer = (ConnectToAppServer)GetProcAddress(hInstance, "ConnectToAppServer");

		try
		{
			bClassifyResult = ClassifyConnectToAppServer(m_hWnd, serverIP, serverPort);
			printf("ClassifyConnectToAppServer Completed!\n");

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
	return (jint)bClassifyResult;
}


JNIEXPORT jint JNICALL Java_cn_sgool_dll_Classify_upOcvFxResult16(JNIEnv *env, jobject obj, jstring jServerIP, jstring jServerPort, jstring jDataType, jstring jTrayId, jstring jTrayRfid, jstring jFileName)
{
	char* serverIP;
	int serverPort;
	int dataType;
	char* trayId;
	__int64 trayRfid;
	char* fileName;

	serverIP = (char*)env->GetStringUTFChars(jServerIP, 0);
	serverPort = atoi((char*)env->GetStringUTFChars(jServerPort, 0));
	dataType = atoi((char*)env->GetStringUTFChars(jDataType, 0));
	trayId = (char*)env->GetStringUTFChars(jTrayId, 0);
	trayRfid = _atoi64((char*)env->GetStringUTFChars(jTrayRfid, 0));
	fileName = (char*)env->GetStringUTFChars(jFileName, 0);


	//加载登录DLL，检查数据库连接
	printf("********************************************\n");
	printf("Native interface start!\n");
	printf("ServerIP: %s\n", serverIP);
	printf("ServerPort: %d\n", serverPort);
	HINSTANCE hInstance = LoadLibrary(_T("fxClassifyDLL.dll"));
	int iClassifyResult;
	if (hInstance != NULL)
	{
		UpOCVFXResult16 ClassifyUpOCVFXResult16;

		HANDLE m_hWnd = GetCurrentProcess();
		printf("Handle is %u\n", (unsigned int)m_hWnd);

		ClassifyUpOCVFXResult16 = (UpOCVFXResult16)GetProcAddress(hInstance, "upOCVFXResult16");

		try
		{
			iClassifyResult = ClassifyUpOCVFXResult16(m_hWnd, serverIP, serverPort, dataType, trayId, trayRfid, fileName);
			printf("ClassifyUpOCVFXResult16 Completed!\n");

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
	return (jint)iClassifyResult;
}


JNIEXPORT jint JNICALL Java_cn_sgool_dll_Classify_upOcvFxResultMany(JNIEnv *env, jobject obj, jstring jServerIP, jstring jServerPort, jstring jTrayId, jstring jTrayRfid, jstring jFileName, jstring jDataType, jstring jOcvNum)
{
	char* serverIP;
	int serverPort;	
	char* trayId;
	__int64 trayRfid;
	char* fileName;
	int dataType;
	int ocvNum;

	serverIP = (char*)env->GetStringUTFChars(jServerIP, 0);
	serverPort = atoi((char*)env->GetStringUTFChars(jServerPort, 0));	
	trayId = (char*)env->GetStringUTFChars(jTrayId, 0);
	trayRfid = _atoi64((char*)env->GetStringUTFChars(jTrayRfid, 0));
	fileName = (char*)env->GetStringUTFChars(jFileName, 0);
	dataType = atoi((char*)env->GetStringUTFChars(jDataType, 0));
	ocvNum = atoi((char*)env->GetStringUTFChars(jOcvNum, 0));


	//加载登录DLL，检查数据库连接
	printf("********************************************\n");
	printf("Native interface start!\n");
	printf("ServerIP: %s\n", serverIP);
	printf("ServerPort: %d\n", serverPort);
	HINSTANCE hInstance = LoadLibrary(_T("fxClassifyDLL.dll"));
	int iClassifyResult;
	if (hInstance != NULL)
	{
		UpOCVFXResultMany ClassifyUpOCVFXResultMany;

		HANDLE m_hWnd = GetCurrentProcess();
		printf("Handle is %u\n", (unsigned int)m_hWnd);

		ClassifyUpOCVFXResultMany = (UpOCVFXResultMany)GetProcAddress(hInstance, "upOCVFXResultMany");

		try
		{
			iClassifyResult = ClassifyUpOCVFXResultMany(m_hWnd, serverIP, serverPort, trayId, trayRfid, fileName, dataType, ocvNum);
			printf("ClassifyUpOCVFXResultMany Completed!\n");

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
	return (jint)iClassifyResult;
}