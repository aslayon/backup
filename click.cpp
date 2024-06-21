#include "click.h"

// Wave_M.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.



#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,
   WPARAM wParam, LPARAM lParam);

LPCTSTR lpszClass = TEXT("New Title Hong Gil Dong");

HDC hdc;
const int TIMER_ID = 1;

int radius = 10; // ������
int m_count = 20; // M ������ ����
const double PI = 3.14159265358979323846; // PI ��
static int a = 5; // ������ �׸� M�� ���� �׸� M���� �Ÿ�

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, //WINAPI : ������ ���α׷��̶�� �ǹ�
   LPSTR lpszCmdLine, int nCmdShow)                   //hInstance : �ü���� Ŀ���� ���� ���α׷��� �ο��� ID
{                                                 //szCmdLine : Ŀ��Ʈ���� �󿡼� ���α׷� ���� �� ���޵� ���ڿ�
   HWND   hwnd;                                     //iCmdShow : �����찡 ȭ�鿡 ��µ� ����
   MSG      msg;
   WNDCLASS WndClass;                                  //WndClass ��� ����ü ����                            
   WndClass.style = CS_HREDRAW | CS_VREDRAW;          //��½�Ÿ�� : ����/������ ��ȭ�� �ٽ� �׸�
   WndClass.lpfnWndProc = WndProc;                      //���ν��� �Լ���
   WndClass.cbClsExtra = 0;                         //O/S ��� ���� �޸� (Class)
   WndClass.cbWndExtra = 0;                         //O/s ��� ���� �޸� (Window)
   WndClass.hInstance = hInstance;                   //���� ���α׷� ID
   WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);    //������ ����
   WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);       //Ŀ�� ����
   WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//����   
   WndClass.lpszMenuName = NULL;                         //�޴� �̸�
   WndClass.lpszClassName = lpszClass;                   //Ŭ���� �̸�
   RegisterClass(&WndClass);                            //�ռ� ������ ������ Ŭ������ �ּ�

   hwnd = CreateWindow(lpszClass,                         //�����찡 �����Ǹ� �ڵ�(hwnd)�� ��ȯ
      lpszClass,                                     //������ Ŭ����, Ÿ��Ʋ �̸�
      WS_OVERLAPPEDWINDOW,                            //������ ��Ÿ��
      100,                                  //������ ��ġ, x��ǥ
      50,                                  //������ ��ġ, y��ǥ
      600,                                  //������ ��   
      400,                                  //������ ����   
      NULL,                                        //�θ� ������ �ڵ�    
      NULL,                                        //�޴� �ڵ�
      hInstance,                                      //���� ���α׷� ID
      NULL                                          //������ ������ ����
   );
   ShowWindow(hwnd, nCmdShow);                            //�������� ȭ�� ���
   UpdateWindow(hwnd);                                  //O/S �� WM_PAINT �޽��� ����

   while (GetMessage(&msg, NULL, 0, 0))                      //WinProc()���� PostQuitMessage() ȣ�� ������ ó��
   {
      TranslateMessage(&msg);
      DispatchMessage(&msg);                            //WinMain -> WinProc  
   }
   return (int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

   PAINTSTRUCT ps;

   static int m_count, x, y, round_x,round_y; 
   static int left_button = true;


   switch (iMsg)
   {

   case WM_CHAR:
      InvalidateRect(hwnd, NULL, FALSE);
      break;

   case WM_LBUTTONDOWN:
      x = LOWORD(lParam);
      y = HIWORD(lParam);
      m_count = 30;
      a = 5;
      InvalidateRect(hwnd, NULL, false);
      SetTimer(hwnd, TIMER_ID, 100, NULL); // 100ms���� Ÿ�̸� Ʈ����
      break;

   case WM_RBUTTONDOWN:
      KillTimer(hwnd, TIMER_ID); // Ÿ�̸� ����
      break;
   case WM_PAINT:
      hdc = BeginPaint(hwnd, &ps);
      for (int i = 0; i < m_count; ++i) {
         // ���� ���
         double angle = 2 * PI * i / m_count; // i�� 0���� �����ϸ鼭 ������ ���� ��Ŵ
         // �߽ɿ������� ������ ��ŭ ������ ��ġ ���
         round_x = x + static_cast<int>((radius + a) * cos(angle)); // ���� angle�̸鼭, 
         round_y = y + static_cast<int>((radius + a) * sin(angle));
         // M ���� �׸���
         TextOut(hdc, round_x, round_y, "M", 1);
      }
      EndPaint(hwnd, &ps);
      break;

   case WM_TIMER:
      a = a + 20;
      // ȭ�� ���� ��û
      InvalidateRect(hwnd, NULL, false);
      break;

   case WM_DESTROY:
      PostQuitMessage(0);
      break;
   }
   return DefWindowProc(hwnd, iMsg, wParam, lParam);          //CASE���� ���ǵ��� ���� �޽����� Ŀ���� ó���ϵ��� �޽��� ����
} \