//==================================================
//  DirectX設定クラス [D3Dsetup.cpp]        Autor:ロ
//==================================================

#include "D3Dsetup.h"

//D3D_APP共通用ポインタ
D3DApp* g_d3dApp = 0;
//D3D_Device共通用ポインタ
LPDIRECT3DDEVICE9 g_d3dDevice = 0;

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//ウィンドウズが作られたら、状態メッセージを表示する
	if (g_d3dApp != 0)
		return g_d3dApp->msgProc(msg, wParam, lParam);
	else
		return DefWindowProc(hwnd, msg, wParam, lParam);
}

//コンストラクタ
//==================================================
D3DApp::D3DApp(HINSTANCE hInstance, std::string winCaption, D3DDEVTYPE devType, DWORD requestedVP)
{
	mMainWndCaption = winCaption;
	mDevType = devType;
	mRequestedVP = requestedVP;

	mhAppInst = hInstance;
	mhMainWnd = 0;
	md3dObject = 0;
	mAppPaused = false;
	ZeroMemory(&md3dPP, sizeof(md3dPP));

	initMainWindow();
	initDirect3D();
}

//デストラクタ
//==================================================
D3DApp::~D3DApp()
{
	RELEASE_OBJ(md3dObject);
	RELEASE_OBJ(g_d3dDevice);
}

HINSTANCE D3DApp::getAppInst()
{
	return mhAppInst;
}

HWND D3DApp::getMainWnd()
{
	return mhMainWnd;
}

//ウィンドウズ初期化処理
//==================================================
void D3DApp::initMainWindow()
{
	WNDCLASS wc = {}; //何も入れない
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = mhAppInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
	wc.lpszMenuName = 0;
	wc.lpszClassName = "GameWindow";

	if (!RegisterClass(&wc))
	{
		MessageBox(0, "RegisterClass FAILED", 0, 0);
		PostQuitMessage(0);
	}

	// ウィンドウズのサイズを設定する
	RECT R = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	AdjustWindowRect(&R, WINDOW_STYLE, false);
	mhMainWnd = CreateWindow("GameWindow", mMainWndCaption.c_str(),
		WINDOW_STYLE, 100, 100, R.right, R.bottom,
		0, 0, mhAppInst, 0);

	if (!mhMainWnd)
	{
		MessageBox(0, "CreateWindow FAILED", 0, 0);
		PostQuitMessage(0);
	}

	ShowWindow(mhMainWnd, SW_SHOW);
	UpdateWindow(mhMainWnd);
}

//D3D初期化処理
//==================================================
void D3DApp::initDirect3D()
{
	// D3Dオブジェクトを作る

	md3dObject = Direct3DCreate9(D3D_SDK_VERSION);
	if (!md3dObject)
	{
		MessageBox(0, "Direct3DCreate9 FAILED", 0, 0);
		PostQuitMessage(0);
	}

	D3DDISPLAYMODE mode;
	md3dObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode);
	HR_CHECK(md3dObject->CheckDeviceType(D3DADAPTER_DEFAULT, mDevType, mode.Format, mode.Format, true));
	HR_CHECK(md3dObject->CheckDeviceType(D3DADAPTER_DEFAULT, mDevType, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, false));

	D3DCAPS9 caps;
	HR_CHECK(md3dObject->GetDeviceCaps(D3DADAPTER_DEFAULT, mDevType, &caps));

	DWORD devBehaviorFlags = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		devBehaviorFlags |= mRequestedVP;
	else
		devBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	if (caps.DevCaps & D3DDEVCAPS_PUREDEVICE &&
		devBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
		devBehaviorFlags |= D3DCREATE_PUREDEVICE;

	
	md3dPP.BackBufferWidth = 0;
	md3dPP.BackBufferHeight = 0;
	md3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
	md3dPP.BackBufferCount = 1;
	md3dPP.MultiSampleType = D3DMULTISAMPLE_NONE;
	md3dPP.MultiSampleQuality = 0;
	md3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	md3dPP.hDeviceWindow = mhMainWnd;
	md3dPP.Windowed = true;
	md3dPP.EnableAutoDepthStencil = true;
	md3dPP.AutoDepthStencilFormat = D3DFMT_D24S8;
	md3dPP.Flags = 0;
	md3dPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	md3dPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	HR_CHECK(md3dObject->CreateDevice(
		D3DADAPTER_DEFAULT, 
		mDevType,           // deviceの種類
		mhMainWnd,         
		devBehaviorFlags,   
		&md3dPP,            
		&g_d3dDevice));      
}

//更新処理
//==================================================
int D3DApp::run()
{
	MSG  msg;
	msg.message = WM_NULL;

	__int64 cntsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);
	float secsPerCnt = 1.0f / (float)cntsPerSec;

	__int64 prevTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);

	//ゲームの初期化
	initScene();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			/*if (mAppPaused)
			{
				Sleep(20);
				continue;
			}*/

			if (!isDeviceLost())
			{
				/*__int64 currTimeStamp = 0;
				QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);
				float dt = (currTimeStamp - prevTimeStamp)*secsPerCnt;*/

				//ゲームの更新
				updateScene();
				//ゲームの描画
				drawScene();

				//prevTimeStamp = currTimeStamp;
			}
		}
	}
	return (int)msg.wParam;
}

//メッセージ処理
//==================================================
LRESULT D3DApp::msgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	// アプリが小さいウィンドウズかそれとも大きいウィンドウズか
	static bool minOrMaxed = false;

	RECT clientRect = { 0, 0, 0, 0 };
	switch (msg)
	{
	case WM_ACTIVATE:
		if (LOWORD(wParam) == WA_INACTIVE)
			mAppPaused = true;
		else
			mAppPaused = false;
		return 0;


		// もしウィンドウズのサイズが変更された時
	case WM_SIZE:
		if (g_d3dDevice)
		{
			md3dPP.BackBufferWidth = LOWORD(lParam);
			md3dPP.BackBufferHeight = HIWORD(lParam);

			if (wParam == SIZE_MINIMIZED)
			{
				mAppPaused = true;
				minOrMaxed = true;
			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				mAppPaused = false;
				minOrMaxed = true;
				onLostDevice();
				HR_CHECK(g_d3dDevice->Reset(&md3dPP));
				onResetDevice();
			}/*
			else if (wParam == SIZE_RESTORED)
			{
				mAppPaused = false;

				if (minOrMaxed && md3dPP.Windowed)
				{
					onLostDevice();
					HR_CHECK(g_d3dDevice->Reset(&md3dPP));
					onResetDevice();
				}
				else
				{

				}
				minOrMaxed = false;
			}*/
		}
		return 0;

	case WM_EXITSIZEMOVE:
		GetClientRect(mhMainWnd, &clientRect);
		md3dPP.BackBufferWidth = clientRect.right;
		md3dPP.BackBufferHeight = clientRect.bottom;
		//onLostDevice();
		//HR_CHECK(g_d3dDevice->Reset(&md3dPP));
		//onResetDevice();

		return 0;

	case WM_CLOSE:
		if (MessageBox(mhMainWnd, "close?", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(mhMainWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			enableFullScreenMode(false);
		else if (wParam == 'F')
			enableFullScreenMode(true);
		return 0;
	}
	return DefWindowProc(mhMainWnd, msg, wParam, lParam);
}

//FULL画面MODE処理
//==================================================
void D3DApp::enableFullScreenMode(bool enable)
{
	// FULLSCREEN
	if (enable)
	{
		// 同じモードなら戻す
		if (!md3dPP.Windowed)
			return;

		int width = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);

		md3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
		md3dPP.BackBufferWidth = width;
		md3dPP.BackBufferHeight = height;
		md3dPP.Windowed = false;

		// ウィンドウズのスタイルを変更する
		SetWindowLongPtr(mhMainWnd, GWL_STYLE, WS_POPUP);

		SetWindowPos(mhMainWnd, HWND_TOP, 0, 0, width, height, SWP_NOZORDER | SWP_SHOWWINDOW);
	}else{
		// 同じモードなら戻す
		if (md3dPP.Windowed)
			return;


		RECT R = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		AdjustWindowRect(&R, WINDOW_STYLE, false);
		md3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
		md3dPP.BackBufferWidth = SCREEN_WIDTH;
		md3dPP.BackBufferHeight = SCREEN_HEIGHT;
		md3dPP.Windowed = true;

		// ウィンドウズのスタイルを変更する
		SetWindowLongPtr(mhMainWnd, GWL_STYLE, WINDOW_STYLE);

		SetWindowPos(mhMainWnd, HWND_TOP, 100, 100, R.right, R.bottom, SWP_NOZORDER | SWP_SHOWWINDOW);
	}

	// デバイスのモードを変換する
	onLostDevice();
	HR_CHECK(g_d3dDevice->Reset(&md3dPP));
	onResetDevice();
}

bool D3DApp::isDeviceLost()
{
	HRESULT hr = g_d3dDevice->TestCooperativeLevel();

	if (hr == D3DERR_DEVICELOST)
	{
		Sleep(20);
		return true;
	}
	else if (hr == D3DERR_DRIVERINTERNALERROR)
	{
		MessageBox(0, "デバイスError", 0, 0);
		PostQuitMessage(0);
		return true;
	}
	
	else if (hr == D3DERR_DEVICENOTRESET)
	{
		onLostDevice();
		HR_CHECK(g_d3dDevice->Reset(&md3dPP));
		onResetDevice();
		return false;
	}
	else
		return false;
}

void GenTriGrid(int numVertRows, int numVertCols,
	float dx, float dz,
	const D3DXVECTOR3& center,
	std::vector<D3DXVECTOR3>& verts,
	std::vector<DWORD>& indices)
{
	int numVertices = numVertRows*numVertCols;
	int numCellRows = numVertRows - 1;
	int numCellCols = numVertCols - 1;

	int numTris = numCellRows*numCellCols * 2;

	float width = (float)numCellCols * dx;
	float depth = (float)numCellRows * dz;

	verts.resize(numVertices);

	float xOffset = -width * 0.5f;
	float zOffset = depth * 0.5f;

	int k = 0;
	for (float i = 0; i < numVertRows; ++i)
	{
		for (float j = 0; j < numVertCols; ++j)
		{
			verts[k].x = j * dx + xOffset;
			verts[k].z = -i * dz + zOffset;
			verts[k].y = 0.0f;

			D3DXMATRIX T;
			D3DXMatrixTranslation(&T, center.x, center.y, center.z);
			D3DXVec3TransformCoord(&verts[k], &verts[k], &T);

			++k; // Next vertex
		}
	}

	indices.resize(numTris * 3);

	
	k = 0;
	for (DWORD i = 0; i < (DWORD)numCellRows; ++i)
	{
		for (DWORD j = 0; j < (DWORD)numCellCols; ++j)
		{
			indices[k] = i   * numVertCols + j;
			indices[k + 1] = i   * numVertCols + j + 1;
			indices[k + 2] = (i + 1) * numVertCols + j;

			indices[k + 3] = (i + 1) * numVertCols + j;
			indices[k + 4] = i   * numVertCols + j + 1;
			indices[k + 5] = (i + 1) * numVertCols + j + 1;

			k += 6;
		}
	}
}