#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "resource.h"

#define WM_NewBlock WM_USER + 1

#define YES 1
#define NO 0
#define SUCCESS 1
#define FAIL 0
#define ON 1
#define OFF 0
#define ALIVE 1
#define DEAD 0

int Block[7][4][4][4] = { 0, 1, 0, 0,
						 0, 1, 0, 0,
						 0, 1, 0, 0,
						 0, 1, 0, 0,

						 0, 0, 0, 0,
						 1, 1, 1, 1,
						 0, 0, 0, 0,
						 0, 0, 0, 0,

						 0, 1, 0, 0,
						 0, 1, 0, 0,
						 0, 1, 0, 0,
						 0, 1, 0, 0,

						 0, 0, 0, 0,
						 1, 1, 1, 1,
						 0, 0, 0, 0,
						 0, 0, 0, 0,

						 0, 0, 1, 0,
						 0, 0, 1, 0,
						 0, 1, 1, 0,
						 0, 0, 0, 0,

						 1, 1, 1, 0,
						 0, 0, 1, 0,
						 0, 0, 0, 0,
						 0, 0, 0, 0,

						 1, 1, 0, 0,
						 1, 0, 0, 0,
						 1, 0, 0, 0,
						 0, 0, 0, 0,

						 0, 0, 0, 0,
						 1, 0, 0, 0,
						 1, 1, 1, 0,
						 0, 0, 0, 0,

						 1, 0, 0, 0,
						 1, 0, 0, 0,
						 1, 1, 0, 0,
						 0, 0, 0, 0,

						 0, 0, 0, 0,
						 0, 0, 1, 0,
						 1, 1, 1, 0,
						 0, 0, 0, 0,

						 0, 1, 1, 0,
						 0, 0, 1, 0,
						 0, 0, 1, 0,
						 0, 0, 0, 0,

						 1, 1, 1, 0,
						 1, 0, 0, 0,
						 0, 0, 0, 0,
						 0, 0, 0, 0,

						 0, 0, 0, 0,
						 0, 1, 0, 0,
						 1, 1, 1, 0,
						 0, 0, 0, 0,

						 0, 0, 1, 0,
						 0, 1, 1, 0,
						 0, 0, 1, 0,
						 0, 0, 0, 0,

						 1, 1, 1, 0,
						 0, 1, 0, 0,
						 0, 0, 0, 0,
						 0, 0, 0, 0,

						 1, 0, 0, 0,
						 1, 1, 0, 0,
						 1, 0, 0, 0,
						 0, 0, 0, 0,

						 0, 1, 0, 0,
						 0, 1, 1, 0,
						 0, 0, 1, 0,
						 0, 0, 0, 0,

						 0, 1, 1, 0,
						 1, 1, 0, 0,
						 0, 0, 0, 0,
						 0, 0, 0, 0,

						 0, 1, 0, 0,
						 0, 1, 1, 0,
						 0, 0, 1, 0,
						 0, 0, 0, 0,

						 0, 1, 1, 0,
						 1, 1, 0, 0,
						 0, 0, 0, 0,
						 0, 0, 0, 0,

						 0, 1, 0, 0,
						 1, 1, 0, 0,
						 1, 0, 0, 0,
						 0, 0, 0, 0,

						 1, 1, 0, 0,
						 0, 1, 1, 0,
						 0, 0, 0, 0,
						 0, 0, 0, 0,

						 0, 1, 0, 0,
						 1, 1, 0, 0,
						 1, 0, 0, 0,
						 0, 0, 0, 0,

						 1, 1, 0, 0,
						 0, 1, 1, 0,
						 0, 0, 0, 0,
						 0, 0, 0, 0,

						 1, 1, 0, 0,
						 1, 1, 0, 0,
						 0, 0, 0, 0,
						 0, 0, 0, 0,

						 1, 1, 0, 0,
						 1, 1, 0, 0,
						 0, 0, 0, 0,
						 0, 0, 0, 0,

						 1, 1, 0, 0,
						 1, 1, 0, 0,
						 0, 0, 0, 0,
						 0, 0, 0, 0,

						 1, 1, 0, 0,
						 1, 1, 0, 0,
						 0, 0, 0, 0,
						 0, 0, 0, 0 
};

int BackGround[21][12];
// �� ���� �߰�
int BlankBlock[10];

BOOL bTime = OFF;
int BlockNum;
int NextBlockNum;
int HoldBlockNum;
BOOL HoldOn = OFF;
int RotateNum;
int NowX, NowY;
int FullLineNum;
int PlayerState;

HWND g_hWnd;

void InitBackGround(void);
void DrawBackGround(void);
void DrawBlock(void);
void EraseBlock(void);
void DrawNextBlock(void);
BOOL BlockCanMove(int x, int y);
void LeftMove(void);
void RightMove(void);
// �� ȸ��
void Rotate(void);
BOOL DownMove(void);
// �̸����� ��
void GhostBlock(void);
// �̸����� �� ����
void EraseGhostBlock(void);
// �̸����� �� �ٴ�üũ
int CheckGhostGround(void);
// 30�ʸ��� ��� �ö��
void UpBackGround(void);
// 30�ʸ��� �ö�ö� �عٴ� ���� ����
void EraseLine(void);
// 30�ʸ��� �ö���� ��(1ĭ�� ��ä�� �ö��)
void UpBlockSet(void);
// �迭 ����� �� �ö�
void UpBlock(void);
// Ȧ�� ���ڿ� �� �׸�
void DrawHoldBlock(void);
// Ȧ�� Ű
void Hold(void);
// Ȧ����� �����ö� �翷�� ������ �� �ִ��� �Ǵ�
void BlockCanMoveHold(int x, int y);
void UpdateBackGround(void);
void CheckFullLine(void);
void EraseFullLine(int);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG mSg;
	WCHAR szTitle[] = TEXT("��Ʈ����");
	WCHAR szClass[] = TEXT("Class");

	HICON hIcon1;
	HICON hIcon2;

	hIcon1 = LoadIcon(NULL, IDI_QUESTION);
	hIcon2 = LoadIcon(hInstance, MAKEINTRESOURCE(102));

	WNDCLASSEX WndEx;

	WndEx.cbSize = sizeof(WndEx);
	WndEx.style = NULL;
	WndEx.lpfnWndProc = WndProc;
	WndEx.cbClsExtra = 0;
	WndEx.cbWndExtra = 0;
	WndEx.hInstance = hInstance;
	WndEx.hIcon = LoadIcon(NULL, TEXT("IDI_ICON"));
	WndEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndEx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndEx.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	WndEx.lpszClassName = szClass;
	WndEx.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));

	RegisterClassEx(&WndEx);

	g_hWnd = CreateWindowEx(NULL, szClass, szTitle, WS_OVERLAPPEDWINDOW, 0, 0, 640, 480, NULL, NULL, hInstance, NULL);

	ShowWindow(g_hWnd, nShowCmd);
	UpdateWindow(g_hWnd);

	while(TRUE)
	{
		if (PeekMessage(&mSg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&mSg, NULL, 0, 0))
				break;
			TranslateMessage(&mSg);
			DispatchMessage(&mSg);
		}
	}
	return mSg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	srand(time(NULL));
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case FILE_START:
			if (PlayerState == DEAD)
			{
				InitBackGround();
				DrawBackGround();
				PlayerState = ALIVE;
				NextBlockNum = rand() % 7;
				FullLineNum = 0;

				SendMessage(hWnd, WM_NewBlock, 0, 0);
			}
			if (bTime == ON)
			{
				KillTimer(hWnd, 3);
				KillTimer(hWnd, 4);
				bTime = OFF;
			}
			else
			{
				SetTimer(hWnd, 3, 1000, NULL);
				SetTimer(hWnd, 4, 30000, NULL);
				bTime = ON;
			}
			break;
		case FILE_EXIT:
			DestroyWindow(hWnd);
			break;
		}
		return FALSE;

	case WM_NewBlock:

		NowX = 4;
		NowY = 0;
		RotateNum = 0;
		BlockNum = NextBlockNum;
		NextBlockNum = rand() % 7;
		// �̸����� �� �׸���
		GhostBlock();
		DrawBlock();
		DrawNextBlock();
		// ó�� ���۽� Ȧ��� �׵θ� �׸�
		if (HoldOn == OFF)
			DrawHoldBlock();

		if (!BlockCanMove(NowX, NowY))
		{		
			PlayerState = DEAD;
		}
		return FALSE;

	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_LEFT:
			LeftMove();
			break;
		case VK_RIGHT:
			RightMove();
			break;
		case VK_DOWN:
			DownMove();
			break;
		case VK_UP:
			Rotate();
			break;
		case VK_SPACE:
			while (DownMove());
			break;
		case VK_RETURN:
			Hold();
			break;
		}
		return FALSE;

	case WM_TIMER:
		if (PlayerState == ALIVE)
		{
			if (wParam == 3)
			{
				DownMove();
			}
			if (wParam == 4)
			{
				UpBlock();
			}
		}
		else
		{
			if (bTime == ON)
			{
				bTime = OFF;
				KillTimer(hWnd, 3);
				KillTimer(hWnd, 4);
			}
		}
		return FALSE;

	case WM_DESTROY:
		if (bTime == ON)
		{
			KillTimer(hWnd, 3);
			KillTimer(hWnd, 4);
		}
		PostQuitMessage(0);
		return FALSE;		
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void InitBackGround(void)
{
	InvalidateRect(g_hWnd, NULL, TRUE);
	UpdateWindow(g_hWnd);

	for (int row = 0; row < 21; row++)
	{
		for (int col = 0; col < 12; col++)
		{
			BackGround[row][col] = 0;
		}
	}

	for (int row = 0; row < 21; row++)
	{
		for (int col = 0; col < 12; col++)
		{
			if (row == 20)
			{
				BackGround[row][col] = 1;
			}
			else if (col == 0)
			{
				BackGround[row][col] = 1;
			}
			else if (col == 11)
			{
				BackGround[row][col] = 1;
			}
			else
			{
				BackGround[row][col] = 0;
			}
		}
	}
}

void DrawBackGround(void) 
{
	HDC hDC = GetDC(g_hWnd);
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	int x, y;

	hPen = CreatePen(PS_SOLID, 1, RGB(150, 150, 150));
	hBrush = CreateSolidBrush(RGB(102, 102, 102));

	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	for (int row = 0; row < 21; row++)
	{
		for (int col = 0; col < 12; col++)
		{
			if (BackGround[row][col] == 1)
			{
				x = 10 + col * 15;
				y = row * 15;
				Rectangle(hDC, x, y, x + 15, y + 15);
			}
		}
	}

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	DeleteDC(hDC);

}

void DrawBlock(void)
{
	HDC hDC = GetDC(g_hWnd);
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	int x, y;

	hPen = CreatePen(PS_SOLID, 1, RGB(255, 102, 102));
	hBrush = CreateSolidBrush(RGB(255, 255, 255));


	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (Block[BlockNum][RotateNum][row][col] == 1)
			{
				x = 25 + NowX * 15 + col * 15;
				y = NowY * 15 + row * 15;
				Rectangle(hDC, x, y, x + 15, y + 15);
			}
		}
	}

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(g_hWnd, hDC);
}

void EraseBlock(void)
{
	HDC hDC = GetDC(g_hWnd);
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	int x, y;

	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hBrush = CreateSolidBrush(RGB(0, 0, 0));

	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (Block[BlockNum][RotateNum][row][col])
			{
				x = 25 + NowX * 15 + col * 15;
				y = NowY * 15 + row * 15;
				Rectangle(hDC, x, y, x + 15, y + 15);
			}
		}
	}

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(g_hWnd, hDC);
}

void DrawNextBlock(void)											
{
	HDC hDC;
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	int x, y;

	hPen = CreatePen(PS_SOLID, 1, RGB(255, 102, 102));
	hBrush = CreateSolidBrush(RGB(0, 0, 0));

	hDC = GetDC(g_hWnd);

	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Rectangle(hDC, 200, 20, 280, 100);

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(g_hWnd, hDC);

	hPen = CreatePen(PS_SOLID, 1, RGB(255, 102, 102));
	hBrush = CreateSolidBrush(RGB(255, 255, 255));

	hDC = GetDC(g_hWnd);

	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (Block[NextBlockNum][RotateNum][row][col])
			{
				x = 210 + col * 15;
				y = 30 + row * 15;
				Rectangle(hDC, x, y, x + 15, y + 15);
			}
		}
	}
	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(g_hWnd, hDC);
}				

BOOL BlockCanMove(int x, int y)
{
	int check = 0;

	int row, col;
	for (row = 0; row < 4; row++)
	{
		for (col = 0; col < 4; col++)
		{
			if (Block[BlockNum][RotateNum][row][col])
			{
				check += BackGround[y + row][x + col + 1];
			}
		}
	}
	if (check == 0)
	{
		return YES;
	}
	else 
	{
		return NO;
	}
}

void LeftMove(void)
{
	if (PlayerState == DEAD)
	{
		return;
	}
	if (BlockCanMove(NowX - 1, NowY))
	{
		EraseGhostBlock();
		EraseBlock();
		NowX--;
		GhostBlock();
		DrawBlock();
	}
}

void RightMove(void)
{
	if (PlayerState == DEAD)
	{
		return;
	}
	if (BlockCanMove(NowX + 1, NowY))
	{
		EraseGhostBlock();
		EraseBlock();
		NowX++;
		GhostBlock();
		DrawBlock();
	}
}

// �� ȸ��
void Rotate(void)								
{
	if (PlayerState == DEAD)
	{
		return;
	}
	int temp = RotateNum;
	RotateNum++;
	RotateNum %= 4;
	if (BlockCanMove(NowX, NowY))
	{
		RotateNum = temp;
		// ��Ʈ �� ����
		// ������ ������ �ܻ� ����
		EraseGhostBlock();
		EraseBlock();
		RotateNum++;
		RotateNum %= 4;
		// ��Ʈ �� ����
		GhostBlock();
		DrawBlock();
	}
	else if (BlockCanMove(NowX - 2, NowY))		// ���� ������ ȸ������ 
	{
		RotateNum = temp;
		// ��Ʈ �� ����
		// ������ ������ �ܻ� ����
		EraseGhostBlock();
		EraseBlock();
		RotateNum++;
		RotateNum %= 4;
		// BlockNum = 0�� 1�� �� �׷��Ƿ� �ѹ��� -1 ����
		if (BlockNum == 0)
		{
			NowX--;
		}
		NowX--;
		// ��Ʈ �� ����
		GhostBlock();
		DrawBlock();
	}
	else if (BlockCanMove(NowX + 1, NowY))		// ���� ������ ȸ������
	{
		RotateNum = temp;
		// ��Ʈ �� ����
		// ������ ������ �ܻ� ����
		EraseGhostBlock();
		EraseBlock();
		RotateNum++;
		RotateNum %= 4;
		NowX++;
		// ��Ʈ �� ����
		GhostBlock();
		DrawBlock();
	}
	else
	{
		RotateNum = temp;
	}
}

BOOL DownMove(void) 
{
	if (PlayerState == DEAD)
	{
		return FALSE;
	}
	if (BlockCanMove(NowX, NowY + 1))
	{
		EraseBlock();
		NowY++;
		DrawBlock();
		return SUCCESS;
	}
	else
	{
		UpdateBackGround();
		CheckFullLine();
		SendMessage(g_hWnd, WM_NewBlock, 0, 0);
		return FAIL;
	}
}

// ��Ʈ �� ����
void GhostBlock(void)
{
	if (PlayerState == DEAD)
	{
		return;
	}
	HDC hDC = GetDC(g_hWnd);
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	int x, y;

	// ����� �������� ��Ʈ ��
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 102, 102));
	hBrush = CreateSolidBrush(RGB(0, 0, 0));

	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	// ��Ʈ �� �׸��� �ݺ���
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (Block[BlockNum][RotateNum][row][col])
			{
				x = 25 + NowX * 15 + col * 15;
				// ��Ʈ ���� �ٴڿ� �ִ��� üũ�ϴ� �Լ�
				y = CheckGhostGround() * 15 + row * 15;
				Rectangle(hDC, x, y, x + 15, y + 15);
			}
		}
	}

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(g_hWnd, hDC);
}

// ��Ʈ ���� ����� �Լ�
void EraseGhostBlock(void)
{
	HDC hDC = GetDC(g_hWnd);
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	int x, y;

	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hBrush = CreateSolidBrush(RGB(0, 0, 0));

	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (Block[BlockNum][RotateNum][row][col])
			{
				x = 25 + NowX * 15 + col * 15;
				y = CheckGhostGround() * 15 + row * 15;
				Rectangle(hDC, x, y, x + 15, y + 15);
			}
		}
	}

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(g_hWnd, hDC);
}

// ��Ʈ ���� �ٴڿ� �ִ��� üũ�ϴ� �Լ�
int CheckGhostGround(void) 
{
	int downY = NowY;
	
	// �ٴڱ��� ����
	while (BlockCanMove(NowX, downY + 1))
	{
		downY++;
	}
	return downY;
}

#pragma region timer
// 30�� ���� ���� �� ���� �ø�(��׶���)
void UpBackGround(void)
{
	HDC hDC, hMemDC;
	HBITMAP hBmp;

	int Xlen = 150;
	int Ylen = 19 * 15;

	hDC = GetDC(g_hWnd);
	hMemDC = CreateCompatibleDC(hDC);
	hBmp = CreateCompatibleBitmap(hDC, 1000, 1000);

	SelectObject(hMemDC, hBmp);

	// �������� ���� ������ ������ �� ��ġ���� �����ǹ����� ������ �������Ѵ�
	// �������� �������ٰ�
	EraseBlock();
	
	BitBlt(hMemDC, 0, 0, Xlen, Ylen, hDC, 25, 15, SRCCOPY);
	BitBlt(hDC, 25, 0, Xlen, Ylen, hMemDC, 0, 0, SRCCOPY);

	// �ٽ� �� ����
	DrawBlock();

	DeleteDC(hMemDC);
	ReleaseDC(g_hWnd, hDC);
	DeleteObject(hBmp);
}

// 30�� ���� �ٴ� ���� ����(��׶���)
void EraseLine(void) 
{
	HDC hDC = GetDC(g_hWnd);
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	int x, y;

	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hBrush = CreateSolidBrush(RGB(0, 0, 0));

	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	// �� �Ʒ��� ����
	for (int col = 1; col <= 10; col++)
	{
		x = 25 + (col - 1) * 15;
		y = 19 * 15;
		Rectangle(hDC, x, y, x + 15, y + 15);
	}

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(g_hWnd, hDC);
}

// 30�� ���� �� ������ �ø��µ� ������ 1ĭ�� ��� �ø�
void UpBlockSet(void)
{
	HDC hDC;
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	int x, y;
	int col;
	// ���� ���� ���� ����
	int rnum;
	// �������� ������ �迭 ����
	int rArray[10];
	int checkBlank;
	bool isZero = false;

	hDC = GetDC(g_hWnd);

	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	hBrush = CreateSolidBrush(RGB(150, 150, 150));

	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	for (col = 0; col < 10; col++) 
	{
		// 0~9���� ���� �� ����
		rnum = rand() % 10;
		rArray[col] = rnum;
		// ó�� ���� ������ �迭�� ����
		if (!col)
		{
			rArray[col] = rnum;
		}
		// 1���� 9���� ���� ����
		else
		{
			// rArray�� ����� �������� �ߺ��� �ȵǵ��ϼ���
			for (checkBlank = 0; checkBlank < col; checkBlank++) 
			{
				// rArray[0]���� col���� ����� ���� ���� �������� ��
				// ���� �Ѱ��� ������ �ٽ� �� ����
				if (rArray[checkBlank] == rArray[col])
				{
					col--;
				}
			}
		}
	}
	// ������ �ٿ��� ��ĭ�� �Ǻ��� �迭 �ʱ�ȭ
	for (col = 0; col < 10; col++) 
	{
		BlankBlock[col] = 1;
	}

	for (col = 0; col < 10; col++)
	{
		// BlankBlock�� 0�� ������ ������ ����
		if (!isZero)
		{
			// BlankBlock�� 50�ۼ�Ʈ Ȯ���� 0�� �ָ�
			// ó�� �κп� ��ĭ�� ���� �����
			// �װ��� �����ϱ����� rArray�� ������ ������ �ο�
			BlankBlock[rArray[col]] = rand() % 2;
			for (checkBlank = 0; checkBlank < 10; checkBlank++)
			{
				// ĭ�� 0�̸� Ż��
				if (!BlankBlock[checkBlank])
				{
					isZero = true;
				}
			}
		}
		// BlankBlock�� 0�� ���ð�� ������ 1�� ä��
		else
		{
			BlankBlock[rArray[col]] = 1;
		}
	}

	// ��׶��忡 �ö�� �� �׸�
	for (col = 1; col <= 10; col++)
	{
		BackGround[19][col] = BlankBlock[col - 1];
		if (BackGround[19][col] >= 1)
		{
			x = 25 + (col - 1) * 15;
			y = 19 * 15;
			Rectangle(hDC, x, y, x + 15, y + 15);
		}
	}

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(g_hWnd, hDC);
}

// 30�ʸ��� �� ���� �ø�(�迭)
void UpBlock(void)
{	
	int row, col;

	UpBackGround();
	for (row = 1; row <= 19; row++)
	{
		for (col = 1; col <= 10; col++)
		{
			BackGround[row - 1][col] = BackGround[row][col];
		}
	}
	EraseLine();
	UpBlockSet();
}
#pragma endregion

// Ȧ�� ���� �׸�
void DrawHoldBlock(void)
{
	HDC hDC;
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;

	hPen = CreatePen(PS_SOLID, 1, RGB(255, 102, 102));
	hBrush = CreateSolidBrush(RGB(0, 0, 0));

	hDC = GetDC(g_hWnd);

	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	Rectangle(hDC, 200, 140, 280, 220);

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(g_hWnd, hDC);
}

// ���͸� �������� Ȧ��
void Hold(void)
{
	if (PlayerState == DEAD)
	{
		return;
	}
	HDC hDC;
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	int x, y;

	hPen = CreatePen(PS_SOLID, 1, RGB(255, 102, 102));
	hBrush = CreateSolidBrush(RGB(255, 255, 255));

	hDC = GetDC(g_hWnd);

	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);		

	// Ȧ���ų�� �ش��ϴ� ��Ʈ �� ����
	EraseGhostBlock();
	// Ȧ�� ��ų �� ����
	EraseBlock();
	// Ȧ����ִ� ���� ������ �ѹ� ����
	if (HoldOn == OFF)
	{
		// Ȧ��� �迭 ���� ����
		HoldBlockNum = BlockNum;
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				if (Block[BlockNum][0][row][col])
				{
					BlockCanMoveHold(NowX, NowY);
					x = 210 + col * 15;
					y = 150 + row * 15;
					Rectangle(hDC, x, y, x + 15, y + 15);
				}
			}
		}
		// ���� Ȧ���Ű�� ���� �� ���� ���� ����
		BlockNum = NextBlockNum;
		// �ٽ� ������� �׸�
		DrawBlock();
		// �ѹ� ����Ǿ���
		HoldOn = ON;
	}
	// Ȧ��� ���� �� �ٲٴ� ����
	else
	{
		// ��ȯ
		int HoldTemp = BlockNum;
		BlockNum = HoldBlockNum;
		HoldBlockNum = HoldTemp;
		// Ȧ�� ���ڿ� �� �׸�
		DrawHoldBlock();

		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				if (Block[HoldBlockNum][0][row][col])
				{
					// �� �ٲܶ� ���� ���� ���� �ʴ°� Ȯ��
					BlockCanMoveHold(NowX, NowY);
					x = 210 + col * 15;
					y = 150 + row * 15;
					Rectangle(hDC, x, y, x + 15, y + 15);
				}
			}
		}
	}
	GhostBlock();
	DrawBlock();

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);

	DeleteObject(hPen);
	DeleteObject(hBrush);

	ReleaseDC(g_hWnd, hDC);
}

// ���� ���� ��ȯ�ÿ� Ȧ����� ���� �մ°� Ȯ��
void BlockCanMoveHold(int x, int y)
{
	int check = 0;

	int row, col;
	for (row = 0; row < 4; row++)
	{
		for (col = 0; col < 4; col++)
		{
			// ���� Ȯ��
			if (x >= 8 && (BackGround[row + y][11] && Block[HoldBlockNum][0][row][col]))
			{
				if (HoldBlockNum == 0)
				{
					NowX--;
				}
				NowX--;
				return;
			}
			// ���� Ȯ��
			else if (x < 0 && (BackGround[row + y][0] && Block[HoldBlockNum][0][row][col]) )
			{
				NowX++;
				return;
			}
		}
	}
}

void UpdateBackGround(void)
{
	int element;
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			element = Block[BlockNum][RotateNum][row][col];
			if (element)
				BackGround[NowY + row][NowX + col + 1] = element;
		}
	}	
}

void CheckFullLine(void)
{
	int row, col, line;
	int elementNum;
	for (row = 19; row >= 0; row--)
	{
		elementNum = 0;
		for (col = 1; col <= 10; col++)
		{
			elementNum += BackGround[row][col];
		}

		if (elementNum == 10)
		{
			for (line = row; line > 0; line--)
			{
				for (col = 1; col <= 10; col++)
				{
					BackGround[line][col] = BackGround[line - 1][col];
				}
			}
			EraseFullLine(row);
			FullLineNum++;
			row++;
		}
	}
}

void EraseFullLine(int row)
{
	HDC hDC, hMemDC;
	HBITMAP hBmp;

	int Xlen = 150;
	int Ylen = row * 15;

	hDC = GetDC(g_hWnd);
	hMemDC = CreateCompatibleDC(hDC);
	hBmp = CreateCompatibleBitmap(hDC, 1000, 1000);

	SelectObject(hMemDC, hBmp);

	BitBlt(hMemDC, 0, 0, Xlen, Ylen, hDC, 25, 0, SRCCOPY);
	BitBlt(hDC, 25, 15, Xlen, Ylen, hMemDC, 0, 0, SRCCOPY);

	DeleteDC(hMemDC);
	ReleaseDC(g_hWnd, hDC);
	DeleteObject(hBmp);
}