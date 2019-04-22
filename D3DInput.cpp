//==================================================
//  DirectX 入力処理クラス [D3DInput.cpp]        Autor:ロ
//==================================================

#include "D3DInput.h"
#include "D3Dsetup.h"

D3DInput* gDInput = 0;

//コンストラクタ
//==================================================
D3DInput::D3DInput(DWORD keyboardCoopFlags, DWORD mouseCoopFlags)
{
	ZeroMemory(mKeyboardState, sizeof(mKeyboardState));
	ZeroMemory(&mMouseState, sizeof(mMouseState));

	// DirectInputオブジェクトの作成
	HR_CHECK(DirectInput8Create(g_d3dApp->getAppInst(), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&mDInput, 0));

	// デバイスの作成
	HR_CHECK(mDInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, 0));
	// データフォーマットを設定
	HR_CHECK(mKeyboard->SetDataFormat(&c_dfDIKeyboard));
	// 協調モードを設定（フォアグラウンド＆非排他モード）
	HR_CHECK(mKeyboard->SetCooperativeLevel(g_d3dApp->getMainWnd(), keyboardCoopFlags));
	// キーボードへのアクセス権を獲得(入力制御開始)
	HR_CHECK(mKeyboard->Acquire());

	//マウスデバイスの作成
	HR_CHECK(mDInput->CreateDevice(GUID_SysMouse, &mMouse, 0));
	HR_CHECK(mMouse->SetDataFormat(&c_dfDIMouse2));
	HR_CHECK(mMouse->SetCooperativeLevel(g_d3dApp->getMainWnd(), mouseCoopFlags));
	HR_CHECK(mMouse->Acquire());
}

//デストラクタ
//==================================================
D3DInput::~D3DInput()
{
	RELEASE_OBJ(mDInput);
	// キーボードへのアクセス権を開放(入力制御終了)
	mKeyboard->Unacquire();
	RELEASE_OBJ(mKeyboard);

	mMouse->Unacquire();
	RELEASE_OBJ(mMouse);
}

// キーボードの更新処理
void D3DInput::keyUpdate()
{
	BYTE aKeyState[256];

	// デバイスからデータを取得
	//HRESULT hr = mKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState);
	//if( FAILED(hr) )
	//{
	//	for (int nCnKey = 0; nCnKey < 256; nCnKey++)
	//	{
	//		// キートリガー・リリース情報を生成
	//		g_aKeyStateTrigger[nCnKey] = (mKeyboardState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
	//		g_aKeyStateRelease[nCnKey] = (mKeyboardState[nCnKey] ^ aKeyState[nCnKey]) & mKeyboardState[nCnKey];


	//		// キープレス情報を保存
	//		mKeyboardState[nCnKey] = aKeyState[nCnKey];
	//	}
	//	//ZeroMemory(mKeyboardState, sizeof(mKeyboardState));

	//	// キーボードへのアクセス権を取得
	//	hr = mKeyboard->Acquire();
	//}
	if (SUCCEEDED(mKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCnKey = 0; nCnKey < 256; nCnKey++)
		{
			// キートリガー・リリース情報を生成
			g_aKeyStateTrigger[nCnKey] = (mKeyboardState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			g_aKeyStateRelease[nCnKey] = (mKeyboardState[nCnKey] ^ aKeyState[nCnKey]) & mKeyboardState[nCnKey];


			// キープレス情報を保存
			mKeyboardState[nCnKey] = aKeyState[nCnKey];
		}
		//ZeroMemory(mKeyboardState, sizeof(mKeyboardState));

		
		
	}
	else {
		// キーボードへのアクセス権を取得
		mKeyboard->Acquire();
	}


	//mouse
	HRESULT hr = mMouse->GetDeviceState(sizeof(DIMOUSESTATE2), (void**)&mMouseState);
	if (FAILED(hr))
	{
		// Mouse lost, zero out mouse data structure.
		ZeroMemory(&mMouseState, sizeof(mMouseState));

		// Try to acquire for next time we poll.
		hr = mMouse->Acquire();
	}
}

//キー入力処理
//==================================================
bool D3DInput::keyDown(char key)
{
	return (mKeyboardState[key] & 0x80) != 0;
}

//キー入力一回処理
//==================================================
bool D3DInput::keyIsTrigger(char key)
{
	return (g_aKeyStateTrigger[key] & 0x80) != 0;
}

bool D3DInput::keyIsRelease(char key)
{
	return (g_aKeyStateRelease[key] & 0x80) != 0;
}

//マウス入力処理
//==================================================
bool D3DInput::mouseButtonDown(int button)
{
	return (mMouseState.rgbButtons[button] & 0x80) != 0;
}

//マウスY軸移動処理
//==================================================
float D3DInput::mouseDY()
{
	POINT po;
	GetCursorPos(&po);
	//return (float)mMouseState.lY;
	return (float)mMouseState.lY;
}