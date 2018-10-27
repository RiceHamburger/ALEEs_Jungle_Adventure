//プロジェクトにDirect3Dライブラリインクルード
#include <Windows.h>
#include <d3dx9.h>
#include <math.h>
#include "debugPrintf.h"
#include "common.h"
#include "direct3d_setup.h"
#include "sprite.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//window設定
#define CLASS_NAME ("GameWindow")
#define CLASS_NAMEEX ("GameLouise")
#define WINDOW_CAPTION ("ALEE's Jungle Adventure")
#define WINDOW_STYLE (WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME))

//ウィンドウズプロシージャ（コールバック関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//ゲームの初期化関数
static bool Init(HINSTANCE hInstance,HWND hWnd);
//ゲームの更新関数
static void Update(void);
//ゲームの描画関数
static void Draw(void);
//ゲームの終了関数
static void Final(void);

/*-----------------------------
	グローバル変数宣言
-----------------------------*/
HWND  hWnd = NULL;


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdline);

	WNDCLASS wc = {}; //何も入れない　*ZeroMemory()
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	RegisterClass(&wc);

	DWORD window_style = WINDOW_STYLE;

	RECT WindowRect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&WindowRect, window_style, FALSE);

	//computer Screen width and height
	int WSCREEN = GetSystemMetrics(SM_CXSCREEN);
	int HSCREEN = GetSystemMetrics(SM_CYSCREEN);

	//return max number
	int windows_x = max((WSCREEN - (WindowRect.right - WindowRect.left)) / 2, 0);
	int windows_y = max((HSCREEN - (WindowRect.bottom - WindowRect.top)) / 2, 0);

	int windows_width = WindowRect.right - WindowRect.left;
	int windows_height = WindowRect.bottom - WindowRect.top;
	
	//HWND hWnd = CreateWindow(
	hWnd = CreateWindow(
		CLASS_NAME,
		WINDOW_CAPTION,
		window_style,
		windows_x,
		windows_y,
		windows_width,
		windows_height,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hWnd == NULL) {
		return 0;//失敗時結束程式
	}
	//指定のウィンドウズハンドラのウィンドウズ
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//------------------------------
	//ゲームの初期化　DX3Dの初期化
	//------------------------------
 	Init(hInstance,hWnd);

	MSG msg = {};
	do {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			//------------------------------
			//ゲームの更新処理
			//ゲームの描画
			//------------------------------
			Update();
			Draw();
		}
	} while (msg.message != WM_QUIT);

	//ゲームの終了処理（DX3D）
	Final();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		
		break;
	case WM_CLOSE:
		if (MessageBox(hWnd, "close?", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);//WM_QUIT
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//ゲームの初期化関数
bool Init(HINSTANCE hInstance,HWND hWnd) {

	if (!Keyboard_Initialize(hInstance, hWnd)) {
		return false;
	}

	/*if (!Xinput_Initialize(hWnd)) {
		return false;
	}*/

	//D3Dの初期化
	if (!MyDirect3D_Initialize(hWnd)) {
		return false;
	}
	
	//スプライトの初期化
	Sprite_Initialize();

	InitSound(hWnd);

	Fade_Initialize();

	//ゲームの初期化
	if (!Game_Initialize()) {
		return false;
	}

	return true;
}

//ゲームの更新関数
void Update(void) {
	Keyboard_Update();
	Xinput_Update();
	Game_Update();
	Fade_Update();
}

//ゲームの描画関数
void Draw(void) {

	LPDIRECT3DDEVICE9 g_pD3DDevice = MyDirect3D_GetDevice();
	if (!g_pD3DDevice) {
		return;
	}

	// シーンのクリア clear full screen
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0,255), 1.0f, 0);

	//描画開始
	g_pD3DDevice->BeginScene();

	//ゲームの描画
	Game_Draw();

	Fade_Draw();

	//描画終了
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

//ゲームの終了関数
void Final(void) {
	Game_Finalize();
	
	Sprite_Finalize();

	MyDirect3D_Finallize();

	Keyboard_Finalize();
	Xinput_Finalize();

	UninitSound();
}