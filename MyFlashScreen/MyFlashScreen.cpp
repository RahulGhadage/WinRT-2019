#include<Windows.h>
#include "MyFlashScreen.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Flash Window");
	
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance,MAKEINTRESOURCE(MYICON));

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,
		TEXT("Flash Window"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	return((int)msg.wParam);
}
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	static HBITMAP hBitmap;
	HINSTANCE hInstance;
	HDC hDc,hMemDC ;
	PAINTSTRUCT ps;
	RECT rc;
	BITMAP MyBitmap;
	hInstance = GetModuleHandle(0);

	switch(iMsg)
	{
		case WM_CREATE:
			hBitmap = LoadBitmap(hInstance,MAKEINTRESOURCE(MYBITMAP));
			break;
		case WM_PAINT:
			hDc = BeginPaint(hWnd,&ps);
			GetClientRect(hWnd,&rc);
			hMemDC = CreateCompatibleDC(NULL);
			SelectObject(hMemDC,hBitmap);
			GetObject(hBitmap,sizeof(BITMAP),(LPSTR)&MyBitmap);
			StretchBlt(hDc,0,0,(rc.right- rc.left),(rc.bottom- rc.top),hMemDC,0,0,MyBitmap.bmWidth,MyBitmap.bmHeight,SRCCOPY);
			//StretchBlt(hDc,150,100,128,128,hMemDC,0,0,32,32,SRCCOPY);
			DeleteDC(hMemDC);
			EndPaint(hWnd,&ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

	}
	return(DefWindowProc(hWnd,iMsg,wParam,lParam));
}