#include<windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
DWORD WINAPI ThreadOne(LPVOID);
DWORD WINAPI ThreadTwo(LPVOID);
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Multi Threading");

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

	hwnd = CreateWindow(szAppName,
		TEXT("Multi Threading"),
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
	HANDLE hThreadOne = NULL;
	HANDLE hThreadTwo = NULL;

	switch(iMsg)
	{
		case WM_CREATE:
			hThreadOne = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadOne,(LPVOID)hWnd,0,NULL);
			hThreadTwo = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadTwo,(LPVOID)hWnd,0,NULL);
			break;

		case WM_LBUTTONDOWN:
			MessageBox(hWnd,TEXT("Mouse left button pressed"),TEXT("Multiple Threads"),MB_OK);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return(DefWindowProc(hWnd,iMsg,wParam,lParam));
}
DWORD WINAPI ThreadOne(LPVOID Param)
{
	HDC hdc;
	unsigned long int iCounter;
	TCHAR strMsg[255];

	hdc = GetDC((HWND)Param);
	SetBkColor(hdc,RGB(0,0,0));
	SetTextColor(hdc,RGB(0,255,0));

	for(iCounter = 0; iCounter < 4294967295; iCounter++)
	{
		wsprintf(strMsg,TEXT("Thread One -> Increasing Order : %lu"),iCounter);

		TextOut(hdc,5,5,strMsg,wcslen(strMsg));
	}
	ReleaseDC((HWND)Param,hdc);
	return 0;
}


DWORD WINAPI ThreadTwo(LPVOID lParam)
{
	HDC hdc;
	unsigned long int iCounter;
	TCHAR strMsg[255];

	hdc = GetDC((HWND)lParam);
	SetBkColor(hdc,RGB(0,0,0));
	SetTextColor(hdc,RGB(0,255,0));

	for(iCounter = 4294967295; iCounter > 0 ; iCounter--)
	{
		wsprintf(strMsg,TEXT("Thread Two -> Decreasing Order : %lu"),iCounter);

		TextOut(hdc,5,25,strMsg,wcslen(strMsg));
	}
	ReleaseDC((HWND)lParam,hdc);
	return 0;
}