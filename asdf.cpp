#include <windows.h>
#include <iostream>
#include "resource1.h"
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
			WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("New Title Hong Gil Dong");



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, //WINAPI : 윈도우 프로그램이라는 의미
		   LPSTR lpszCmdLine, int nCmdShow)						 //hInstance : 운영체제의 커널이 응용 프로그램에 부여한 ID
{																 //szCmdLine : 커멘트라인 상에서 프로그램 구동 시 전달된 문자열
	HWND	hwnd;												 //iCmdShow : 윈도우가 화면에 출력될 형태
	MSG		msg;
	WNDCLASS WndClass;											 //WndClass 라는 구조체 정의									
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;			 //출력스타일 : 수직/수평의 변화시 다시 그림
	WndClass.lpfnWndProc	= WndProc;							 //프로시저 함수명
	WndClass.cbClsExtra		= 0;								 //O/S 사용 여분 메모리 (Class)
	WndClass.cbWndExtra		= 0;								 //O/s 사용 여분 메모리 (Window)
	WndClass.hInstance		= hInstance;						 //응용 프로그램 ID
	WndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);	 //아이콘 유형
	WndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);		 //커서 유형
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);//배경색  
	WndClass.lpszMenuName	= NULL;								 //메뉴 이름
	WndClass.lpszClassName	= lpszClass;						 //클래스 이름
	RegisterClass(&WndClass);									 //앞서 정의한 윈도우 클래스의 주소

	hwnd = CreateWindow(lpszClass,								 //윈도우가 생성되면 핸들(hwnd)이 반환
		lpszClass,												 //윈도우 클래스, 타이틀 이름
		WS_OVERLAPPEDWINDOW,									 //윈도우 스타일
		100,											 //윈도우 위치, x좌표
		50,											 //윈도우 위치, y좌표
		600,											 //윈도우 폭  
		400,											 //윈도우 높이  
		NULL,													 //부모 윈도우 핸들	
		LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)),													 //메뉴 핸들
		hInstance,    											 //응용 프로그램 ID
		NULL     												 //생성된 윈도우 정보
	);
	ShowWindow(hwnd, nCmdShow);									 //윈도우의 화면 출력
	UpdateWindow(hwnd);											 //O/S 에 WM_PAINT 메시지 전송

	while(GetMessage(&msg, NULL, 0, 0))							 //WinProc()에서 PostQuitMessage() 호출 때까지 처리
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);									 //WinMain -> WinProc  
	}
	return (int)msg.wParam;
}

HDC hdc;
COLORREF tc;
int x = 0;
int y = 0;
int a = 10;
int b = 10;
void CALLBACK TimerProc1(HWND hwnd, UINT iMsg, UINT ievent, DWORD dwTime)
{
		RECT r4;
	    GetClientRect(hwnd,&r4);
		int width = r4.right - r4.left;
	
		if(x > width-15) {
			a = -10;	
			
		}
		if(x<0) a= 10;

		x += a;
		
		
		
		InvalidateRect(hwnd, NULL, TRUE);
}


void CALLBACK TimerProc2(HWND hwnd, UINT iMsg, UINT ievent, DWORD dwTime)
{
		
		RECT r4;
	    GetClientRect(hwnd,&r4);
		int height = r4.bottom - r4.top;
		
		if(y > height - 15){
			b = -10;
		}
		if(y<0) b = 10;
		y += b;
		
		InvalidateRect(hwnd, NULL, TRUE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)    
{

	PAINTSTRUCT ps;
	hdc = GetDC(hwnd);
	static char linebfr[256] = {0, };
	
	
	switch (iMsg)
	{
	case WM_CREATE:
		//m_count = 0;
		SetTimer(hwnd, 1, 20, TimerProc1);
		SetTimer(hwnd, 2, 30, TimerProc2);
		break;
	case WM_COMMAND:{
		switch(LOWORD(wParam)){

		case ID_COLOR_BLUE:{
			tc = 0x00FF0000;
			InvalidateRect(hwnd, NULL, TRUE);
				   }
						   break;
		}

		case ID_COLOR_RED:{
			tc = 0x000000FF;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
				   }
		case ID_COLOR_BLACK:{
			tc = 0x00000000;
			InvalidateRect(hwnd, NULL, TRUE);
							}
							break;
		}
	
					
					
	case WM_CHAR:
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_MOUSEMOVE:
		//x = LOWORD(lParam);
		//y = HIWORD(lParam);
		//left_button = FALSE;
		//m_count++;
		//itoa(m_count, linebfr, 10);

		//nvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		//left_button = TRUE;
		//m_count++;
		//itoa(m_count, linebfr, 10);

		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP:{
		//left_button = FALSE;
					  }
	case WM_RBUTTONDOWN:
		//x = LOWORD(lParam);
		//y = HIWORD(lParam);
		//left_button = FALSE;
		//m_count--;
		//itoa(m_count, linebfr, 10);

		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//TextOut(hdc, 100, 50, "        ",8 );
		//TextOut(hdc, 100, 50, linebfr,strlen(linebfr) );
		SetTextColor(hdc,tc);
		TextOut(hdc,x,y,"H",1);

		//if(left_button == TRUE)
			//SetPixel(hdc, x, y, RGB(255, 0, 0));
		
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);			 //CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달
}

/*
		switch(wParam)
		{
		case 'i' : // UP
			y -= 3;
			break;
		case 'j' : // LEFT
			x -= 5;
			break;
		case 'k' : // RIGHT
			x += 5;
			break;
		case 'm' : // DOWN
			y += 3;
			break;
		}
		*/