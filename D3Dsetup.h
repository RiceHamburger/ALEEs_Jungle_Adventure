//==================================================
//  DirectX設定クラス [D3Dsetup.h]        Autor:ロ
//==================================================

#ifndef D3DSETUP_H
#define D3DSETUP_H

// インクルードファイル
//==================================================
#include <d3dx9.h>
#include <dxerr.h>
#include <string>
#include <vector>

// グローバル関数
//==================================================
class D3DApp;
extern D3DApp* g_d3dApp;
extern LPDIRECT3DDEVICE9 g_d3dDevice;
class Fade;
extern Fade* g_Fade;

// マクロ定義
//==================================================
// メモリ解放
#define RELEASE_OBJ(obj) { if(obj){ obj->Release();obj = NULL; } }
// Debug
#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR_CHECK
	#define HR_CHECK(device)						        \
	{                                                       \
		HRESULT hr = device;                                \
		if(FAILED(hr))                                      \
		{                                                   \
			DXTrace(__FILE__, __LINE__, hr, #device, TRUE); \
		}                                                   \
	}
	#endif
#else
	#ifndef HR_CHECK
	#define HR_CHECK(x) x;
	#endif
#endif
//画面スタイル
#define WINDOW_STYLE (WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME))
//画面サイト
#define SCREEN_WIDTH (1024)
#define SCREEN_HEIGHT (768)
const float EPSILON = 0.001f;

class D3DApp
{
public:
	D3DApp(HINSTANCE hInstance, std::string winCaption, D3DDEVTYPE devType, DWORD requestedVP);
	virtual ~D3DApp();

	HINSTANCE getAppInst();
	HWND      getMainWnd();

	//デバイスの関数
	virtual bool checkDeviceCaps() { return true; }
	virtual void onLostDevice() {}
	virtual void onResetDevice() {}
	//初期化
	virtual void initScene() {}
	//更新
	virtual void updateScene() {}
	//描画
	virtual void drawScene() {}

	//ウィンドウズとD3D初期化
	virtual void initMainWindow();
	virtual void initDirect3D();
	virtual int run();
	virtual LRESULT msgProc(UINT msg, WPARAM wParam, LPARAM lParam);

	//全画面モード
	void enableFullScreenMode(bool enable);
	bool isDeviceLost();

protected:
	//ウィンドウズネーム
	std::string mMainWndCaption;
	//ウィンドウズタイプ
	D3DDEVTYPE  mDevType;
	//
	DWORD       mRequestedVP;

	// アプリケーション, ウィンドウズ, Direct3Dのデータ
	HINSTANCE             mhAppInst;
	HWND                  mhMainWnd;
	LPDIRECT3D9           md3dObject;
	bool                  mAppPaused;
	D3DPRESENT_PARAMETERS md3dPP;
};

#endif // D3DSETUP_H