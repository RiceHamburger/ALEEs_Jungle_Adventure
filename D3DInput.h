//==================================================
//  DirectX 入力処理クラス [D3DInput.h]        Autor:ロ
//==================================================

#ifndef D3D_INPUT_H
#define D3D_INPUT_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

class D3DInput
{
public:
	D3DInput(DWORD keyboardCoopFlags, DWORD mouseCoopFlags);
	~D3DInput();

	void keyUpdate();
	bool keyDown(char key);
	bool keyIsTrigger(char key);
	bool keyIsRelease(char key);

	bool mouseButtonDown(int button);
	float mouseDY();

private:
	D3DInput(const D3DInput& rhs);
	D3DInput& operator=(const D3DInput& rhs);
		
private:
	IDirectInput8*       mDInput;

	IDirectInputDevice8* mKeyboard;
	char                 mKeyboardState[256];//キーボードの入力情報ワーク
	char                 g_aKeyStateTrigger[256];//キーボードのトリガー情報ワーク
	char                 g_aKeyStateRelease[256];//キーボードのリリース情報ワーク

	IDirectInputDevice8* mMouse;
	DIMOUSESTATE2        mMouseState;
};
extern D3DInput* gDInput;

#endif // D3D_INPUT_H