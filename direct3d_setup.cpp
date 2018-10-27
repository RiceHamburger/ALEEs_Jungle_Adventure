#include <Windows.h>
#include <d3dx9.h>
#include "direct3d_setup.h"
#include "common.h"

/*-----------------------------
グローバル変数宣言
-----------------------------*/
static LPDIRECT3D9 g_pD3D = NULL;
static LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
static D3DPRESENT_PARAMETERS g_D3DPP;

//LPDIRECT3DTEXTURE9 g_pTexture = NULL;


bool MyDirect3D_Initialize(HWND hWnd) {
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	/*
	D3DPRESENT_PARAMETERS 構造体
	*/
	ZeroMemory(&g_D3DPP, sizeof(g_D3DPP));
	g_D3DPP.Windowed = TRUE; //ウィンドウモードを指定
	g_D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD; //スワップ．エフェクト
	g_D3DPP.BackBufferFormat = D3DFMT_UNKNOWN;//バックバッファ
	g_D3DPP.BackBufferWidth = SCREEN_WIDTH;
	g_D3DPP.BackBufferHeight = SCREEN_HEIGHT;
	g_D3DPP.BackBufferCount = 1;
	g_D3DPP.hDeviceWindow = hWnd;
	g_D3DPP.EnableAutoDepthStencil = TRUE; //必ずTRUE
	g_D3DPP.AutoDepthStencilFormat = D3DFMT_D16;
	g_D3DPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	g_D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &g_D3DPP, &g_pD3DDevice);

	if (FAILED(hr))
	{
		hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &g_D3DPP, &g_pD3DDevice);
		if (FAILED(hr))
		{
			return false;
		}
	}

	//bmp.jpg,dds,tga,png
	//dds圧縮したままメモリに入れる、容量的に有利
	//file name
	/*if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rekobenichan.png", &g_pTexture))) {
		return false;
	}*/

	//アルファブレンド
	//処理が重い
	//用switch選擇處理是常用手法
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//背景（既に描かれた状態）DESTのブレンド設定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//今から描くポリゴンSRCのブレンド設定
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	return true;
}

//Direct3D終了処理
void MyDirect3D_Finallize(void) {
	if (g_pD3DDevice) {
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D) {
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//Direct3Dデバイスポインタの取得
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void) {
	return g_pD3DDevice;
}