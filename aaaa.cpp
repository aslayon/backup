

#include <windows.h>
int a=100;
int b = 100;
char tmp[2];
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
		NULL,													 //메뉴 핸들
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
	return DefWindowProc(hwnd, iMsg, wParam, lParam);			 //CASE에서 정의되지 않은 메시지는 커널이 처리하도록 메시지 전달
}