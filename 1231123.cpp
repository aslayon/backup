#include <windows.h>
#include "resource.h"
#include <iostream>
#include<stdio.h>
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, 
			WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("New Title Hong Gil Dong");

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, //WINAPI : ������ ���α׷��̶�� �ǹ�
		   LPSTR lpszCmdLine, int nCmdShow)						 //hInstance : �ü���� Ŀ���� ���� ���α׷��� �ο��� ID
{																 //szCmdLine : Ŀ��Ʈ���� �󿡼� ���α׷� ���� �� ���޵� ���ڿ�
	HWND	hwnd;												 //iCmdShow : �����찡 ȭ�鿡 ��µ� ����
	MSG		msg;
	WNDCLASS WndClass;											 //WndClass ��� ����ü ����									 
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;			 //��½�Ÿ�� : ����/������ ��ȭ�� �ٽ� �׸�
	WndClass.lpfnWndProc	= WndProc;							 //���ν��� �Լ���
	WndClass.cbClsExtra		= 0;								 //O/S ��� ���� �޸� (Class)
	WndClass.cbWndExtra		= 0;								 //O/s ��� ���� �޸� (Window)
	WndClass.hInstance		= hInstance;						 //���� ���α׷� ID
	WndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);	 //������ ����
	WndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);		 //Ŀ�� ����
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);//����   
	WndClass.lpszMenuName	= NULL;								 //�޴� �̸�
	WndClass.lpszClassName	= lpszClass;						 //Ŭ���� �̸�
	RegisterClass(&WndClass);									 //�ռ� ������ ������ Ŭ������ �ּ�

	hwnd = CreateWindow(lpszClass,								 //�����찡 �����Ǹ� �ڵ�(hwnd)�� ��ȯ
		lpszClass,												 //������ Ŭ����, Ÿ��Ʋ �̸�
		WS_OVERLAPPEDWINDOW,									 //������ ��Ÿ��
		100,											 //������ ��ġ, x��ǥ
		50,											 //������ ��ġ, y��ǥ
		600,											 //������ ��   
		400,											 //������ ����   
		NULL,													 //�θ� ������ �ڵ�	 
		LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU1)),													 //�޴� �ڵ�
		hInstance,    											 //���� ���α׷� ID
		NULL     												 //������ ������ ����
	);
	ShowWindow(hwnd, nCmdShow);									 //�������� ȭ�� ���
	UpdateWindow(hwnd);											 //O/S �� WM_PAINT �޽��� ����

	while(GetMessage(&msg, NULL, 0, 0))							 //WinProc()���� PostQuitMessage() ȣ�� ������ ó��
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);									 //WinMain -> WinProc  
	}
	return (int)msg.wParam;
}

HDC hdc;
static int x, y;
int tx = -3;
int ty = -3;
int score = 0;
bool timee = FALSE;
void CALLBACK TimerProc1(HWND hwnd, UINT iMsg, UINT ievent, DWORD dwTime)
{
		//if(ievent  == 1)
		//x += 10;
		//else
		//	y += 10;
		tx = rand()%600;
		ty = rand()%400;
		InvalidateRect(hwnd, NULL, TRUE);
}

void CALLBACK TimerProc2(HWND hwnd, UINT iMsg, UINT ievent, DWORD dwTime)
{
		//if(ievent  == 1)
		//	x += 10;
		//else
		y += 10;
		InvalidateRect(hwnd, NULL, TRUE);
}

int BallPath[2] = {10, 10};
int BallVector[2] = {20, 20};

int TailPath[9][2];

VOID CALLBACK TimerProc3(HWND hwnd, UINT message, UINT_PTR idTimer,
                         DWORD dwTime) {
  RECT windowRect;

  GetClientRect(hwnd, &windowRect);

  BallPath[0] += BallVector[0];
  BallPath[1] += BallVector[1];

  if (windowRect.right - abs(BallVector[0]) < BallPath[0] ||
      abs(BallVector[0]) > BallPath[0]) {
    BallVector[0] = -BallVector[0];
  }

  if (windowRect.bottom - abs(BallVector[1]) < BallPath[1] ||
      abs(BallVector[1]) > BallPath[1]) {
    BallVector[1] = -BallVector[1];
  }

  for (int i = 8; i > 0; --i) {
    TailPath[i][0] = TailPath[i - 1][0];
    TailPath[i][1] = TailPath[i - 1][1];
  }

  TailPath[0][0] = BallPath[0];
  TailPath[0][1] = BallPath[1];

  InvalidateRect(hwnd, NULL, true);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)     
{

	PAINTSTRUCT ps;

	static char linebfr[256] = {0, };
	static int oldX, oldY, left_button, color;	
	 
	switch (iMsg) 
	{
	case WM_CREATE:
		//SetTimer(hwnd, 3, 100, TimerProc3);
		//SetTimer(hwnd, 2, 5000, TimerProc2);
		x = 0;
		y = 0;
		color = 1;
		break;

	case WM_COMMAND:
		switch (wParam) 
		{
		case ID_TIMER_START:
			//SetTimer(hwnd, 1, 1000, TimerProc1);
			SetTimer(hwnd, 3, 100, TimerProc3);
			timee = TRUE;
			break;
		case ID_TIMER_STOP:
			KillTimer(hwnd, 3);
			timee = FALSE;
			break;
		case ID_COLOR_RED:
			color = 1;
			break;
		case ID_COLOR_GREEN:
			color = 2;
			break;
		case ID_COLOR_BLUE:
			color = 3;
			break;
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;

	case WM_TIMER:
		//if(wParam  == 1)
			x += 10;
		//else
			y += 10;
		InvalidateRect(hwnd, NULL, FALSE);
		break;

	case WM_CHAR:
		InvalidateRect(hwnd, NULL, FALSE);
		break;

	case WM_MOUSEMOVE:
		x = LOWORD(lParam);
		y = HIWORD(lParam);

		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		if( LOWORD(lParam) -10<tx+8 &&  LOWORD(lParam) + 20 >tx+8){
			if(HIWORD(lParam) -10<ty+8 &&  HIWORD(lParam) + 20 >ty+8){
				score++;
				KillTimer(hwnd, 1);
				SetTimer(hwnd, 1, 1000, TimerProc1);
				tx = rand()%600;
				ty = rand()%400;
			}
		}
		

		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_LBUTTONUP:
		left_button = FALSE;

		InvalidateRect(hwnd, NULL, FALSE);
		break;

	case WM_RBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		left_button = FALSE;
		//m_count--;
		//itoa(m_count, linebfr, 10);

		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		//Rectangle(hdc, x-10, y-10, x+10, y+10);
		oldX = x;
		oldY = y;

		if(color == 1)
			SetTextColor(hdc, RGB(255, 0, 0));
		else if(color == 2)
			SetTextColor(hdc, RGB(0, 255, 0));
		else 
			SetTextColor(hdc, RGB(0, 0, 255));

		TextOut(hdc, BallPath[0], BallPath[1], L"W", 1);

		for (int i = 0; i < 9; ++i) {
		if (TailPath[i][0] != 0 && TailPath[i][1] != 0) {
		TextOut(hdc, TailPath[i][0], TailPath[i][1], L"W", 1);
		}
		}

  
			
		
		
		//TextOut(hdc, tx, ty, "H", 1 );
		
		
		
		char buffer[10];
		sprintf_s(buffer,"%d",score);
		//TextOut(hdc, 0, 0, buffer, strlen(buffer) );
		
		EndPaint(hwnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	} 
	return DefWindowProc(hwnd, iMsg, wParam, lParam);			 //CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ����
}
/* 
COLORREF color = RGB(0, 0, 0);
Rectangle(hdc, x1, y1, x2, y2);
Ellipse(hdc, x1, y1, x2, y2);
*/


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
	/*
	case WM_MOUSEMOVE:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		
		//m_count++;
		//itoa(m_count, linebfr, 10);

		InvalidateRect(hwnd, NULL, FALSE);
		break;
	*/

		//MoveToEx(hdc, 10, 50, NULL);

		//LineTo(hdc, 300, 50);