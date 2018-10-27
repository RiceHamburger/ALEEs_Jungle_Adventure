//�v���W�F�N�g��Direct3D���C�u�����C���N���[�h
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

//window�ݒ�
#define CLASS_NAME ("GameWindow")
#define CLASS_NAMEEX ("GameLouise")
#define WINDOW_CAPTION ("ALEE's Jungle Adventure")
#define WINDOW_STYLE (WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME))

//�E�B���h�E�Y�v���V�[�W���i�R�[���o�b�N�֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//�Q�[���̏������֐�
static bool Init(HINSTANCE hInstance,HWND hWnd);
//�Q�[���̍X�V�֐�
static void Update(void);
//�Q�[���̕`��֐�
static void Draw(void);
//�Q�[���̏I���֐�
static void Final(void);

/*-----------------------------
	�O���[�o���ϐ��錾
-----------------------------*/
HWND  hWnd = NULL;


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdline);

	WNDCLASS wc = {}; //��������Ȃ��@*ZeroMemory()
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
		return 0;//���s����������
	}
	//�w��̃E�B���h�E�Y�n���h���̃E�B���h�E�Y
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//------------------------------
	//�Q�[���̏������@DX3D�̏�����
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
			//�Q�[���̍X�V����
			//�Q�[���̕`��
			//------------------------------
			Update();
			Draw();
		}
	} while (msg.message != WM_QUIT);

	//�Q�[���̏I�������iDX3D�j
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
		if (MessageBox(hWnd, "close?", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);//WM_QUIT
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//�Q�[���̏������֐�
bool Init(HINSTANCE hInstance,HWND hWnd) {

	if (!Keyboard_Initialize(hInstance, hWnd)) {
		return false;
	}

	/*if (!Xinput_Initialize(hWnd)) {
		return false;
	}*/

	//D3D�̏�����
	if (!MyDirect3D_Initialize(hWnd)) {
		return false;
	}
	
	//�X�v���C�g�̏�����
	Sprite_Initialize();

	InitSound(hWnd);

	Fade_Initialize();

	//�Q�[���̏�����
	if (!Game_Initialize()) {
		return false;
	}

	return true;
}

//�Q�[���̍X�V�֐�
void Update(void) {
	Keyboard_Update();
	Xinput_Update();
	Game_Update();
	Fade_Update();
}

//�Q�[���̕`��֐�
void Draw(void) {

	LPDIRECT3DDEVICE9 g_pD3DDevice = MyDirect3D_GetDevice();
	if (!g_pD3DDevice) {
		return;
	}

	// �V�[���̃N���A clear full screen
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0,255), 1.0f, 0);

	//�`��J�n
	g_pD3DDevice->BeginScene();

	//�Q�[���̕`��
	Game_Draw();

	Fade_Draw();

	//�`��I��
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);

}

//�Q�[���̏I���֐�
void Final(void) {
	Game_Finalize();
	
	Sprite_Finalize();

	MyDirect3D_Finallize();

	Keyboard_Finalize();
	Xinput_Finalize();

	UninitSound();
}