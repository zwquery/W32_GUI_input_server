// Activate.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "windows.h"
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include "Resource.h"
#include "winNT.h"
#include <shellapi.h>
#include <Tchar.h>
#include <Commdlg.h>
#include <time.h>
#include <fstream>
#include <Wininet.h>
#include <strsafe.h>
#include <wchar.h>





#define MAX_LOADSTRING 100
#pragma comment(lib, "Wininet")

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
TCHAR helloWorld[] = _T("TITLE TEXT");
TCHAR helloWorld2[] = _T("Please, type your EMAIL :");


TCHAR helloWorld3[] = _T("TEXT2");
LPCTSTR key = L"Software\\SOFT\\KEY";
TCHAR date[] = L"VALUE";
LPCWSTR buffo = L"REF";


HWND hWndInput;
TCHAR buff[64] = { '\0' };
LPCWSTR ok = L"false";

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;


	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_ACTIVATE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ACTIVATE));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ACTIVATE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ACTIVATE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      500, 300, 500, 300, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void sorry(){
	 ok = L"false";
}

void writeKey(){

	HKEY hkey;
	    DWORD dwDisposition;
	    if(RegCreateKeyEx(HKEY_CURRENT_USER,
	      //TEXT("Software\\SOFT\\KEY"),
	      key,
		  0, NULL, 0,
	      KEY_WRITE, NULL,
	      &hkey, &dwDisposition) == ERROR_SUCCESS)
	    {

	    	if (RegSetValueEx(hkey, TEXT("KEY"), 0, REG_SZ, (LPBYTE)date, strlen("VALUE")*sizeof(char)) != ERROR_SUCCESS)
			{
	    		//cout <<"Unable to set registry value value_name";
				MessageBox(NULL,L"error",0, MB_OK);
	    	}
	    	else
	    	{
	//    		cout << "Key written  ;)" << endl;
	    	}

	    	RegCloseKey(hkey);
	    	}
	    	else
	        MessageBox(NULL,L"error",0, MB_OK);
			}



   void getMail()
   {
	   
	   typedef std::basic_string<TCHAR> tstring;

				// Send request
   LPCTSTR lpszAgent = L"WinInetGet/0.1";
HINTERNET hInternet = InternetOpen(lpszAgent,
		INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

LPCTSTR lpszServerName = L"URL_DOMAIN";
INTERNET_PORT nServerPort = INTERNET_DEFAULT_HTTP_PORT;
LPCTSTR lpszUserName = NULL;
LPCTSTR lpszPassword = NULL;
DWORD dwConnectFlags = 0;
DWORD dwConnectContext = 0;
HINTERNET hConnect = InternetConnect(hInternet,
				lpszServerName, nServerPort,
				lpszUserName, lpszPassword,
				INTERNET_SERVICE_HTTP,
				dwConnectFlags, dwConnectContext);

LPCTSTR lpszVerb = L"GET";

			//buff est l'adresse EMAIL !!
			//buffo est la référence du manuel !!
TCHAR pszDest[260] = _T("WEBPAGE.php?email=");
StringCchCat(pszDest, 260, buff); 
StringCchCat(pszDest, 260, _T("&mnref="));
StringCchCat(pszDest, 260, buffo);

	

LPCTSTR lpszObjectName = pszDest;
LPCTSTR lpszVersion = NULL;			// Use default.
LPCTSTR lpszReferrer = NULL;		// No referrer.
LPCTSTR *lplpszAcceptTypes = NULL;	// Whatever the server wants to give us.
DWORD dwOpenRequestFlags = INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP |
		INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTPS |
		INTERNET_FLAG_KEEP_CONNECTION |
		INTERNET_FLAG_NO_AUTH |
		INTERNET_FLAG_NO_AUTO_REDIRECT |
		INTERNET_FLAG_NO_COOKIES |
		INTERNET_FLAG_NO_UI |
		INTERNET_FLAG_RELOAD;
DWORD dwOpenRequestContext = 0;
HINTERNET hRequest = HttpOpenRequest(hConnect, lpszVerb, lpszObjectName, lpszVersion,
		lpszReferrer, lplpszAcceptTypes,
		dwOpenRequestFlags, dwOpenRequestContext);


BOOL bResult = HttpSendRequest(hRequest, NULL, 0, NULL, 0);

DWORD dwInfoLevel = HTTP_QUERY_RAW_HEADERS_CRLF;
DWORD dwInfoBufferLength = 10;
BYTE *pInfoBuffer = (BYTE *)malloc(dwInfoBufferLength+1);
while (!HttpQueryInfo(hRequest, dwInfoLevel, pInfoBuffer, &dwInfoBufferLength, NULL))
{
	DWORD dwError = GetLastError();
	if (dwError == ERROR_INSUFFICIENT_BUFFER)
	{
		free(pInfoBuffer);
		pInfoBuffer = (BYTE *)malloc(dwInfoBufferLength+1);
	}
	else
	{
		fprintf(stderr, "HttpQueryInfo failed, error = %d (0x%x)\n",
			GetLastError(), GetLastError());
		break;
	}
}

pInfoBuffer[dwInfoBufferLength] = '\0';
printf("%s", pInfoBuffer);
free(pInfoBuffer);

DWORD dwBytesAvailable;
while (InternetQueryDataAvailable(hRequest, &dwBytesAvailable, 0, 0))
{
	BYTE *pMessageBody = (BYTE *)malloc(dwBytesAvailable+1);

	DWORD dwBytesRead;
	BOOL bResult = InternetReadFile(hRequest, pMessageBody,
				dwBytesAvailable, &dwBytesRead);
	if (!bResult)
	{
		fprintf(stderr, "InternetReadFile failed, error = %d (0x%x)\n",
			GetLastError(), GetLastError());
		break;
	}

	if (dwBytesRead == 0)
		break;	// End of File.


	pMessageBody[dwBytesRead] = '\0';

	BYTE* response = new BYTE[300];
	response = pMessageBody;
	LPCWSTR lol = LPCWSTR(response);

	
									//OutputDebugStringW ((LPCWSTR)wcslen(lol));
	
	if (wcslen(lol)<30)
	{
		ok = L"true";
	}
	else
	{
	MessageBox(NULL, L"Unknown address email\r\nPlease contact us at \"informations@DOMAIN\"", NULL, MB_OK | MB_ICONSTOP);
	sorry();
	}

	printf("%s", pMessageBody);
	free(pMessageBody);
}



  
			int Description=0;
            bool isConnected = InternetGetConnectedState(NULL, 0);

         if (isConnected == false)
         {
			ok = L"true";
		}


		 
	if (wcscmp(ok, L"true") == 0){
	   MessageBox(NULL, (tstring(helloWorld3) + L" is accepted for " + tstring(buff)).c_str(), L"Well done !!", MB_OK | MB_ICONINFORMATION);
	   writeKey();

	}



   }

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc, MemDCExercising;
	static HBITMAP hBmp = NULL;

	switch (message)
	{

	case WM_CREATE:
		{
		HWND hWndButton=CreateWindowEx(NULL, 
		L"BUTTON",
		L"Activate !",
		WS_TABSTOP|WS_VISIBLE|WS_CHILD|BS_DEFPUSHBUTTON,
		10,
		150,
		70,
		24,
		hWnd,
		(HMENU)IDC_MAIN_BUTTON,
		GetModuleHandle(NULL),
		NULL);


		hWndInput = CreateWindowEx (NULL,L"EDIT", TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 10, 100, 430, 20, hWnd, (HMENU) IDC_MAIN_INPUT, NULL, NULL);

		}
		break;



	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDC_MAIN_BUTTON:{
			// Obtains input from the textbox and puts it into the char array
			int len = SendMessage(hWndInput, WM_GETTEXTLENGTH, 0, 0);
			SendMessage(hWndInput, WM_GETTEXT, len+1, (LPARAM)buff);
			GetWindowText(hWndInput, buff, len+1);

			if (buff != NULL && buff[0] == '\0' ) {
			 MessageBox(NULL, L"Your EMAIL address is mandatory !!", NULL, MB_OK | MB_ICONSTOP);
			return FALSE;
			}

			getMail();
			break;
							 }
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		TextOut(hdc, 10, 10, helloWorld, _tcslen(helloWorld));
		TextOut(hdc, 200, 10, helloWorld3, _tcslen(helloWorld3));
		TextOut(hdc, 10, 80, helloWorld2, _tcslen(helloWorld2));
		hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_EXERCISING));
		// Create a memory device compatible with the above DC variable
	    MemDCExercising = CreateCompatibleDC(hdc);
        // Select the new bitmap
        SelectObject(MemDCExercising, hBmp);
		// Copy the bits from the memory DC into the current dc
	    BitBlt(hdc, 415, 180, 450, 400, MemDCExercising, 0, 0, SRCCOPY);
	    // Restore the old bitmap
	    DeleteDC(MemDCExercising);
	    DeleteObject(hBmp);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_GETTEXT:

		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
