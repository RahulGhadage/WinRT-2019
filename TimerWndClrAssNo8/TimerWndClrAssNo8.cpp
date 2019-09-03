#include<windows.h>
#define ID_TIMER 100

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("TimerWndClr");

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
		TEXT("TimerWndClr"),
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
	static int iPaintFalg = 0;
	switch(iMsg)
	{
		case WM_CREATE:
			SetTimer(hWnd,ID_TIMER,500,NULL);
			break;
		case WM_TIMER:
			KillTimer(hWnd,ID_TIMER);
			iPaintFalg++;
			if(iPaintFalg > 11)
			{
				iPaintFalg = 0;
			}
			InvalidateRect(hWnd,NULL,FALSE);			//Keep third param as FALSE if you want to see previos temp rect clr
			SetTimer(hWnd,ID_TIMER,500,NULL);			//Start timer
			break;
		case WM_PAINT:
			RECT rcTemp,rc;
			HDC hdc;
			PAINTSTRUCT ps;
			HBRUSH hBrush;
			long lWidth;

			GetClientRect(hWnd,&rc);					//Original Wnd Rect
			
			lWidth = (rc.right)/12;						//Orignal rect width
			rcTemp.left = lWidth* iPaintFalg;
			rcTemp.top = rc.top;
			rcTemp.right = rcTemp.left + lWidth;		//Updating left of Temp RECT
			rcTemp.bottom = rc.bottom;
			
			hdc = BeginPaint(hWnd,&ps);

			switch(iPaintFalg)
			{
				case 1:
					hBrush = CreateSolidBrush(RGB(255,0,0));		
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rcTemp,hBrush);
					break;
				case 2:
					hBrush = CreateSolidBrush(RGB(0,255,0));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rcTemp,hBrush);
					break;
				case 3:
					hBrush = CreateSolidBrush(RGB(0,0,255));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rcTemp,hBrush);
					break;
				case 4:
					hBrush = CreateSolidBrush(RGB(0,255,255));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rcTemp,hBrush);
					break;
				case 5:
					hBrush = CreateSolidBrush(RGB(255,0,255));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rcTemp,hBrush);
					break;		
				case 6:
					hBrush = CreateSolidBrush(RGB(255,255,0));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rcTemp,hBrush);
					break;
				case 7:
					hBrush = CreateSolidBrush(RGB(255,255,255));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rcTemp,hBrush);
					break;
				case 8:
					hBrush = CreateSolidBrush(RGB(255,128,0));				//Orange
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rcTemp,hBrush);
					break;
				case 9:
					hBrush = CreateSolidBrush(RGB(64,64,64));				//DarkGrey
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rcTemp,hBrush);
					break;
				case 10:
					hBrush = CreateSolidBrush(RGB(128,128,128));			//MediumGrey
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rcTemp,hBrush);
					break;
				case 11:
					hBrush = CreateSolidBrush(RGB(192,192,192));			//LightGrey
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rcTemp,hBrush);
					break;
				case 0:
				default:
					hBrush = CreateSolidBrush(RGB(0,0,0));
					SelectObject(hdc,hBrush);
					FillRect(hdc,&rc,hBrush);								//Fill original rc to fill whole wnd with black clr
					break;
			}
				EndPaint(hWnd,&ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

	}
	return(DefWindowProc(hWnd,iMsg,wParam,lParam));
}