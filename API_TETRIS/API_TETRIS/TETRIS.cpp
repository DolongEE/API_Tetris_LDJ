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
// 빈 공간 추가
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
// 블럭 회전
void Rotate(void);
BOOL DownMove(void);
// 미리보는 블럭
void GhostBlock(void);
// 미리보는 블럭 삭제
void EraseGhostBlock(void);
// 미리보는 블럭 바닥체크
int CheckGhostGround(void);
// 30초마다 배경 올라옴
void UpBackGround(void);
// 30초마다 올라올때 밑바닥 라인 삭제
void EraseLine(void);
// 30초마다 올라오는 블럭(1칸만 빈채로 올라옴)
void UpBlockSet(void);
// 배열 저장된 블럭 올라감
void UpBlock(void);
// 홀드 상자에 블럭 그림
void DrawHoldBlock(void);
// 홀드 키
void Hold(void);
// 홀드블럭을 가져올때 양옆에 움직일 수 있는지 판단
void BlockCanMoveHold(int x, int y);
void UpdateBackGround(void);
void CheckFullLine(void);
void EraseFullLine(int);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	MSG mSg;
	WCHAR szTitle[] = TEXT("테트리스");
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
		// 미리보기 블럭 그리기
		GhostBlock();
		DrawBlock();
		DrawNextBlock();
		// 처음 시작시 홀드블럭 테두리 그림
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

// 블럭 회전
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
		// 고스트 블럭 지움
		// 지우지 않으면 잔상 남음
		EraseGhostBlock();
		EraseBlock();
		RotateNum++;
		RotateNum %= 4;
		// 고스트 블럭 생성
		GhostBlock();
		DrawBlock();
	}
	else if (BlockCanMove(NowX - 2, NowY))		// 우측 벽에서 회전가능 
	{
		RotateNum = temp;
		// 고스트 블럭 지움
		// 지우지 않으면 잔상 남음
		EraseGhostBlock();
		EraseBlock();
		RotateNum++;
		RotateNum %= 4;
		// BlockNum = 0은 1자 블럭 그러므로 한번더 -1 해줌
		if (BlockNum == 0)
		{
			NowX--;
		}
		NowX--;
		// 고스트 블럭 생성
		GhostBlock();
		DrawBlock();
	}
	else if (BlockCanMove(NowX + 1, NowY))		// 좌측 벽에서 회전가능
	{
		RotateNum = temp;
		// 고스트 블럭 지움
		// 지우지 않으면 잔상 남음
		EraseGhostBlock();
		EraseBlock();
		RotateNum++;
		RotateNum %= 4;
		NowX++;
		// 고스트 블럭 생성
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

// 고스트 블럭 생성
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

	// 가운데가 검은색인 고스트 블럭
	hPen = CreatePen(PS_SOLID, 1, RGB(255, 102, 102));
	hBrush = CreateSolidBrush(RGB(0, 0, 0));

	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	// 고스트 블럭 그리는 반복문
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (Block[BlockNum][RotateNum][row][col])
			{
				x = 25 + NowX * 15 + col * 15;
				// 고스트 블럭이 바닥에 있는지 체크하는 함수
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

// 고스트 블럭을 지우는 함수
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

// 고스트 블럭이 바닥에 있는지 체크하는 함수
int CheckGhostGround(void) 
{
	int downY = NowY;
	
	// 바닥까지 내림
	while (BlockCanMove(NowX, downY + 1))
	{
		downY++;
	}
	return downY;
}

#pragma region timer
// 30초 마다 기존 블럭 한줄 올림(백그라운드)
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

	// 내려오는 블럭을 지우지 않으면 그 위치에서 고정되버리기 때문에 지워야한다
	// 내려오는 블럭지웠다가
	EraseBlock();
	
	BitBlt(hMemDC, 0, 0, Xlen, Ylen, hDC, 25, 15, SRCCOPY);
	BitBlt(hDC, 25, 0, Xlen, Ylen, hMemDC, 0, 0, SRCCOPY);

	// 다시 블럭 생성
	DrawBlock();

	DeleteDC(hMemDC);
	ReleaseDC(g_hWnd, hDC);
	DeleteObject(hBmp);
}

// 30초 마다 바닥 라인 삭제(백그라운드)
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

	// 맨 아랫줄 지움
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

// 30초 마다 블럭 한줄을 올리는데 무조건 1칸만 비게 올림
void UpBlockSet(void)
{
	HDC hDC;
	HPEN hPen, hOldPen;
	HBRUSH hBrush, hOldBrush;
	int x, y;
	int col;
	// 랜덤 숫자 저장 변수
	int rnum;
	// 랜덤값을 저장할 배열 생성
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
		// 0~9사이 랜덤 값 생성
		rnum = rand() % 10;
		rArray[col] = rnum;
		// 처음 값은 무조건 배열에 저장
		if (!col)
		{
			rArray[col] = rnum;
		}
		// 1부터 9까지 조건 만족
		else
		{
			// rArray에 저장된 랜덤값은 중복이 안되도록설정
			for (checkBlank = 0; checkBlank < col; checkBlank++) 
			{
				// rArray[0]부터 col까지 저장된 값이 현재 랜덤값과 비교
				// 만약 한개라도 같으면 다시 값 설정
				if (rArray[checkBlank] == rArray[col])
				{
					col--;
				}
			}
		}
	}
	// 마지막 줄에서 빈칸을 판별할 배열 초기화
	for (col = 0; col < 10; col++) 
	{
		BlankBlock[col] = 1;
	}

	for (col = 0; col < 10; col++)
	{
		// BlankBlock이 0이 나오기 전까지 실행
		if (!isZero)
		{
			// BlankBlock에 50퍼센트 확률로 0을 주면
			// 처음 부분에 빈칸이 몰려 생긴다
			// 그것을 방지하기위해 rArray를 완전한 랜덤성 부여
			BlankBlock[rArray[col]] = rand() % 2;
			for (checkBlank = 0; checkBlank < 10; checkBlank++)
			{
				// 칸이 0이면 탈출
				if (!BlankBlock[checkBlank])
				{
					isZero = true;
				}
			}
		}
		// BlankBlock이 0이 나올경우 나머지 1로 채움
		else
		{
			BlankBlock[rArray[col]] = 1;
		}
	}

	// 백그라운드에 올라온 줄 그림
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

// 30초마다 블럭 한줄 올림(배열)
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

// 홀드 상자 그림
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

// 엔터를 눌럿을때 홀드
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

	// 홀드시킬때 해당하는 고스트 블럭 삭제
	EraseGhostBlock();
	// 홀드 시킬 블럭 삭제
	EraseBlock();
	// 홀드되있는 블럭이 없을때 한번 실행
	if (HoldOn == OFF)
	{
		// 홀드블럭 배열 숫자 저장
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
		// 블럭을 홀드시키고 다음 블럭 현재 블럭에 저장
		BlockNum = NextBlockNum;
		// 다시 현재블럭을 그림
		DrawBlock();
		// 한번 실행되었음
		HoldOn = ON;
	}
	// 홀드와 현재 블럭 바꾸는 조건
	else
	{
		// 교환
		int HoldTemp = BlockNum;
		BlockNum = HoldBlockNum;
		HoldBlockNum = HoldTemp;
		// 홀드 상자에 블럭 그림
		DrawHoldBlock();

		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				if (Block[HoldBlockNum][0][row][col])
				{
					// 블럭 바꿀때 블럭이 벽을 뚫지 않는가 확인
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

// 현재 블럭과 교환시에 홀드블럭이 벽을 뚫는가 확인
void BlockCanMoveHold(int x, int y)
{
	int check = 0;

	int row, col;
	for (row = 0; row < 4; row++)
	{
		for (col = 0; col < 4; col++)
		{
			// 우측 확인
			if (x >= 8 && (BackGround[row + y][11] && Block[HoldBlockNum][0][row][col]))
			{
				if (HoldBlockNum == 0)
				{
					NowX--;
				}
				NowX--;
				return;
			}
			// 좌측 확인
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