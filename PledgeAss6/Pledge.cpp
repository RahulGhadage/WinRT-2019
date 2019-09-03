#include<Windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hPrevInstance,HINSTANCE hInstance,LPSTR,int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Pledge");

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

	hwnd = CreateWindow(szAppName,TEXT("Pledge"),
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
	TCHAR str[500] = TEXT("India is my country. All Indians are my Brothers and Sisters.\
		I love my country and I am proud of its rich and varied heritage.\
		I shall always strive to");
		
	TCHAR str1[500] = TEXT("be worthy of it.\
		I shall give my parents, teachers and all elders respect and treat everyone with courtesy.\
		To my country and my people, I pledge my devotion.");

	TCHAR str2[500] = TEXT("In their well being and prosperity alone, lies my happiness.");
	
	RECT rc;

	switch(iMsg)
	{	
		case WM_PAINT:
			
			//Get continueosly changing wnd rect.
			GetClientRect(hwnd,&rc);
		
			//Create hdc
			hdc = BeginPaint(hwnd,&ps);
		
			//Set text color
			SetTextColor(hdc,RGB(255,125,0));
			
			//Set text backgrond
			SetBkColor(hdc,RGB(0,0,0));
		
			//Set text(Multiple line text)
			TextOut(hdc,0,0,str,wcslen(str));
			TextOut(hdc,0,20,str1,wcslen(str1));
			TextOut(hdc,0,40,str2,wcslen(str2));
			
			SetTextColor(hdc,RGB(255,255,255));
			TextOut(hdc,0,100,str,wcslen(str));
			TextOut(hdc,0,120,str1,wcslen(str1));
			TextOut(hdc,0,140,str2,wcslen(str2));
			
			SetTextColor(hdc,RGB(0,255,0));
			TextOut(hdc,0,200,str,wcslen(str));
			TextOut(hdc,0,220,str1,wcslen(str1));
			TextOut(hdc,0,240,str2,wcslen(str2));
			
			//Send back HDC
			EndPaint(hwnd,&ps);
			
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}