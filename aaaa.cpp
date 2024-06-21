

#include <windows.h>
int a=100;
int b = 100;
char tmp[2];
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
		NULL,													 //�޴� �ڵ�
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


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)     
{

	PAINTSTRUCT ps;
	RECT r4;
	GetClientRect(hwnd,&r4);
	int width = r4.right - r4.left;
	int height = r4.bottom - r4.top;
	static char linebfr[10][256] = {0, };
	static int i, row, col;
	 
	switch (iMsg) 
	{
	case WM_CREATE:
		row = 0; 
		col = 0;
		CreateCaret(hwnd,NULL,1,17);
		//SetCaretPos(a,b);
		//ShowCaret(hwnd);
		tmp[0] = ' ';
		tmp[1] = '\0';
		break;

	case WM_CHAR:
		
		if(wParam  == VK_RETURN) {
			row ++;
			col = 0;
			b = 100;
			a+= 15;
			break;
		}
		
		else {
			linebfr[row][col++] = wParam;
			linebfr[row][col] = '\0';
			tmp[0] = wParam;
			tmp[1] = '\0';
			b+=8;
			if(b>width) b = 0;
		}
		//SetCaretPos(a,b);
		//ShowCaret(hwnd);
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:{
		HideCaret(hwnd);
		if(wParam == VK_LEFT){
			if(col != 0){
				col--;
				b -= 8;
				if(b<0) b = width;
			}
			
		}
		else if(wParam == VK_RIGHT){
			if(linebfr[row][col+1] != '0'){
				col++;
				b+= 8;
				if(b>width) b = 0;
			}
			
		}
		else if(wParam == VK_UP){
			if(row != 0){
				row--;
				a -= 15;
				if(a<0) b = height;
			}
		
		}
		else if(wParam == VK_DOWN){
			if(linebfr[row+1][col] != '0'){
				row++;
				a += 15;
				if(a>height) a = 0;
			}
			//SetCaretPos(a,b);
		//ShowCaret(hwnd);
		}
		break;
		}
	case WM_PAINT:
		HideCaret(hwnd);
		hdc = BeginPaint(hwnd, &ps);

		//for(i=0; i<10; i++)
			//TextOut(hdc,100,100+20*i,linebfr[i],strlen(linebfr[i]) );
		TextOut(hdc, b,a,tmp,1 );
		EndPaint(hwnd, &ps);
		//SetCaretPos(a,b);
		//ShowCaret(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	} 
	return DefWindowProc(hwnd, iMsg, wParam, lParam);			 //CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ����
}