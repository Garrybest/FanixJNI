#include "stdafx.h"
#include <atlstr.h>
#include "cn_sgool_dll_Login.h"

using namespace std;
using namespace System;

struct StringArray
{
	char battstrArr[16][50];
};

typedef int(__stdcall* ConnectToAppServer)(HANDLE hLoginHand, char* pServerIP, int iServePort);//__cdecl
typedef int(__stdcall* UpLoginData)(HANDLE hLoginHand, char* pServerIP, int iServePort, char* pPalletID, __int64 iRFID, DateTime dLoginTime, StringArray sBattstrArr, char* pIsNew);

JNIEXPORT jint JNICALL Java_cn_sgool_dll_Login_connectToAppServer(JNIEnv *env, jobject obj, jstring jServerIP, jstring jServerPort)
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
	HINSTANCE hInstance = LoadLibrary(_T("LoginDLL.dll"));
	BOOL bLoginResult;
	if (hInstance != NULL)
	{
		ConnectToAppServer  LoginConnectToAppServer;

		HANDLE m_hWnd = GetCurrentProcess();
		printf("Handle is %u\n", (unsigned int)m_hWnd);

		LoginConnectToAppServer = (ConnectToAppServer)GetProcAddress(hInstance, "ConnectToAppServer");

		try
		{
			bLoginResult = LoginConnectToAppServer(m_hWnd, serverIP, serverPort);
			printf("LoginConnectToAppServer Completed!\n");

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
	return (jint)bLoginResult;
}


JNIEXPORT jint JNICALL Java_cn_sgool_dll_Login_upLoginData(JNIEnv *env, jobject obj, jstring jServerIP, jstring jServerPort, jstring jTrayId, jstring jTrayRfid, jobjectArray jBattstrArr, jstring jIsNew)
{
	char* serverIP;
	int serverPort;
	char* trayId;
	__int64 trayRfid;
	DateTime loginTime = DateTime::Now;	
	StringArray stringArray;
	/*stringArray.battstrArr = new char*[16];*/
	
	//for (int i = 0; i < 16; i++)
	//{
	//	stringArray.battstrArr[i] = new char[50];  //分配第二维，每一行的空间。
	//}
	char* isNew;	

	serverIP = (char*)env->GetStringUTFChars(jServerIP, 0);
	serverPort = atoi((char*)env->GetStringUTFChars(jServerPort, 0));
	trayId = (char*)env->GetStringUTFChars(jTrayId, 0);
	trayRfid = _atoi64((char*)env->GetStringUTFChars(jTrayRfid, 0));
	isNew = (char*)env->GetStringUTFChars(jIsNew, 0);
			
	int length = env->GetArrayLength(jBattstrArr); 
	for (int i = 0; i < length; i++) {
		jstring str = (jstring)(env->GetObjectArrayElement(jBattstrArr, i));
		int battlen = env->GetStringUTFLength(str);
		char* battstr = (char*)env->GetStringUTFChars(str, 0);
		for (int j = 0; j < battlen; j++) {
			stringArray.battstrArr[i][j] = battstr[j];
		}
	}
	

	//加载登录DLL，检查数据库连接
	printf("********************************************\n");
	printf("Native interface start!\n");
	printf("ServerIP: %s\n", serverIP);
	printf("ServerPort: %d\n", serverPort);
	HINSTANCE hInstance = LoadLibrary(_T("LoginDLL.dll"));
	int bLoginResult;
	if (hInstance != NULL)
	{
		UpLoginData  upLoginData;

		HANDLE m_hWnd = GetCurrentProcess();
		printf("Handle is %u\n", (unsigned int)m_hWnd);

		upLoginData = (UpLoginData)GetProcAddress(hInstance, "upLoginData");

		try
		{
			bLoginResult = upLoginData(m_hWnd, serverIP, serverPort, trayId, trayRfid, loginTime, stringArray, isNew);
			printf("UpLoginData Completed!\n");

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

	//for (int i = 0; i < 16; i++)
	//{
	//	delete[] stringArray.battstrArr[i]; //先撤销指针元素所指向的数组
	//}
	//delete[] stringArray.battstrArr;
	FreeLibrary(hInstance);
	printf("********************************************\n");
	return (jint)bLoginResult;
}
