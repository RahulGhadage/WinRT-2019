#include<Windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hPrevInstance,HINSTANCE hInstance,LPSTR,int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("HelloWorld");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,TEXT("MessageBox"),
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
	return ((int)msg.wParam);
}
LRESULT CALLBACK WndProc(HWND hwnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{	
	TCHAR strMsg[255];
	switch(iMsg)
	{	
		case WM_CREATE:
			wsprintf(strMsg,TEXT("Application Started!..\nWM_CREATE Arrived!.."));
			MessageBox(hwnd,strMsg,TEXT("Message"),MB_OK);
		break;

		case WM_LBUTTONDOWN:
			wsprintf(strMsg,TEXT("Mouse left button pressed!.."));
			MessageBox(hwnd,strMsg,TEXT("Message"),MB_OK);
		break;
		
		case WM_RBUTTONDOWN:
			wsprintf(strMsg,TEXT("Mouse right button pressed!.."));
			MessageBox(hwnd,strMsg,TEXT("Message"),MB_OK);
		break;

		case WM_MBUTTONDOWN:
			wsprintf(strMsg,TEXT("Mouse middle button pressed!.."));
			MessageBox(hwnd,strMsg,TEXT("Message"),MB_OK);
		break;
		case WM_DESTROY:
			PostQuitMessage(0);
		break;

	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}