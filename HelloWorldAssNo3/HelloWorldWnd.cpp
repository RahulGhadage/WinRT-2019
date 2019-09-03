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

	hwnd = CreateWindow(szAppName,TEXT("HelloWorld"),
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
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR str[255] = TEXT("Hello World!..");
	RECT rc;

	switch(iMsg)
	{	
		case WM_PAINT:
			
			//Get continueosly changing wnd rect.
			GetClientRect(hwnd,&rc);
		
			//Create hdc
			hdc = BeginPaint(hwnd,&ps);
		
			//Set text color
			SetTextColor(hdc,RGB(0,255,0));

			//Set text backgrond
			//SetBkColor(hdc,RGB(255,255,255));
			SetBkColor(hdc,RGB(0,0,0));

			//Set text(Draw text)
			DrawText(hdc,str,-1,&rc,DT_SINGLELINE|DT_CENTER|DT_VCENTER);

			//Send back HDC
			EndPaint(hwnd,&ps);
			
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}