//Headers
#include<windows.h>

//global varible eclaration

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int iCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("KeyClrWindow");
	//code
	//initialization of WNDCLASSEX

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

	//register above class
	RegisterClassEx(&wndclass);

	//createwindow
	hwnd = CreateWindow(szAppName,
		TEXT("KeyClrWindow"),
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

	//message loop
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMsg,WPARAM wParam,LPARAM lParam)
{
	static int iPaintFalg = 0;			//Variable used among msgs should be static otherwise it will not update value

	//msg handlinng code
	switch(iMsg)
	{
		case WM_CHAR:
			//Entered character case
			switch(LOWORD(wParam))
			{
				case 'R':
				case 'r':
					iPaintFalg = 1;
					InvalidateRect(hWnd, NULL, TRUE);		//Call to WMPAINT
					break;
				
				case 'G':
				case 'g':
					iPaintFalg = 2;
					InvalidateRect(hWnd, NULL, TRUE);
					break;
				
				case 'B':
				case 'b':
					iPaintFalg = 3;
					InvalidateRect(hWnd, NULL, TRUE);
					break;

				case 'C':
				case 'c':
					iPaintFalg = 4;
					InvalidateRect(hWnd, NULL, TRUE);
					break;
				
				case 'M':
				case 'm':
					iPaintFalg = 5;
					InvalidateRect(hWnd, NULL, TRUE);
					break;
				
				case 'Y':
				case 'y':
					iPaintFalg = 6;
					InvalidateRect(hWnd, NULL, TRUE);
					break;
					
				case 'W':
				case 'w':
					iPaintFalg =7;
					InvalidateRect(hWnd, NULL, TRUE);
					break;

				case 'K':
				case 'k':
				default:
					iPaintFalg = 0;
					InvalidateRect(hWnd, NULL, TRUE);
					break;
			}
			break;

		case WM_PAINT:
			RECT rc;
			GetClientRect(hWnd,&rc);			//Get Window Rect

			HDC hdc;
			PAINTSTRUCT ps;
			HBRUSH hBrush;
			
			hdc = BeginPaint(hWnd,&ps);			//Begin Paint

			switch(iPaintFalg)
			{
				case 1:
					hBrush = CreateSolidBrush(RGB(255,0,0));		//Create Red Brush
						SelectObject(hdc,hBrush);					//select HDC to paint 
						FillRect(hdc,&rc,hBrush);					//Fill rect with selected brush
					break;
				case 2:
					hBrush = CreateSolidBrush(RGB(0,255,0));		//Create Green Brush
						SelectObject(hdc,hBrush);
						FillRect(hdc,&rc,hBrush);
					break;
				case 3:
					hBrush = CreateSolidBrush(RGB(0,0,255));		//Create Blue Brush
						SelectObject(hdc,hBrush);
						FillRect(hdc,&rc,hBrush);
					break;
				case 4:
					hBrush = CreateSolidBrush(RGB(0,255,255));		//Create Cyan Brush
						SelectObject(hdc,hBrush);
						FillRect(hdc,&rc,hBrush);
					break;
				case 5:
					hBrush = CreateSolidBrush(RGB(255,0,255));		//Create Magenta Brush
						SelectObject(hdc,hBrush);
						FillRect(hdc,&rc,hBrush);
					break;		
				case 6:
					hBrush = CreateSolidBrush(RGB(255,255,0));		//Create Yellow Brush
						SelectObject(hdc,hBrush);
						FillRect(hdc,&rc,hBrush);
					break;
				case 7:
					hBrush = CreateSolidBrush(RGB(255,255,255));	//Create White Brush
						SelectObject(hdc,hBrush);
						FillRect(hdc,&rc,hBrush);
					break;
				case 0:
				default:
					hBrush = CreateSolidBrush(RGB(0,0,0));			//Create Black Brush
						SelectObject(hdc,hBrush);
						FillRect(hdc,&rc,hBrush);
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