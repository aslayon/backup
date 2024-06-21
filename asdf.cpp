#include <windows.h>
#include <iostream>
#include "resource1.h"
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
		LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1)),													 //�޴� �ڵ�
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
	return DefWindowProc(hwnd, iMsg, wParam, lParam);			 //CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ����
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