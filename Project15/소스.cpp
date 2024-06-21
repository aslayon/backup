#include <stdio.h>
#include <stdlib.h>

#include <tchar.h>
#include <windows.h>

#include <string.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;

WNDCLASS WndClass;

int numbers = 0;

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpszCmdParam,
    int nCmdShow)
{
    HWND hWnd;
    MSG Message;
    g_hInst = hInstance;

    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hInstance = hInstance;
    WndClass.lpfnWndProc = (WNDPROC)WndProc;
    WndClass.lpszClassName = "ApiBase";
    WndClass.lpszMenuName = NULL;
    WndClass.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&WndClass);

    hWnd = CreateWindow("ApiBase",
        "Test",
        WS_OVERLAPPEDWINDOW,
        10,// X
        100,// Y
        400,// Width
        400,// Height
        NULL,
        (HMENU)NULL,
        hInstance,
        NULL);


    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&Message, 0, 0, 0))
    {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }

    return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static char strChar[MAX_PATH];
    int nlen = 0;
    static int pos = 0;
    SIZE size;

    switch (iMessage)
    {
    case WM_CREATE:
        strcpy(strChar, "");
        break;
    case WM_CHAR:
        //���� ũ�� ����/���� �߰�.
        nlen = strlen(strChar);
        strChar[nlen] = (char)wParam;
        strChar[nlen + 1] = 0;

        //���� ���.
        pos++;
        hdc = GetDC(hWnd);
        GetTextExtentPoint(hdc, strChar, pos, &size);
        ReleaseDC(hWnd, hdc);

        //ĳ�� ��ġ ����.
        SetCaretPos(size.cx + 100, 100);

        //�ٽ� �׸��� ����.
        InvalidateRect(hWnd, NULL, FALSE);
        break;
    case WM_SETFOCUS:
        hdc = GetDC(hWnd);
        CreateCaret(hWnd, NULL, 2, 14); // ĳ�� ����
        ShowCaret(hWnd); // ĳ�� ���̱�
        SetCaretPos(100, 100); // ĳ���� ��ġ ����
        break;
    case WM_KILLFOCUS:
        HideCaret(hWnd); // ĳ�� �����
        DestroyCaret(); // ĳ�� �ı�
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        TextOut(hdc, 100, 100, strChar, strlen(strChar));
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}