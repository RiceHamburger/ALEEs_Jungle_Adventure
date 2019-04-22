//==================================================
//  DirectX ���͏����N���X [D3DInput.cpp]        Autor:��
//==================================================

#include "D3DInput.h"
#include "D3Dsetup.h"

D3DInput* gDInput = 0;

//�R���X�g���N�^
//==================================================
D3DInput::D3DInput(DWORD keyboardCoopFlags, DWORD mouseCoopFlags)
{
	ZeroMemory(mKeyboardState, sizeof(mKeyboardState));
	ZeroMemory(&mMouseState, sizeof(mMouseState));

	// DirectInput�I�u�W�F�N�g�̍쐬
	HR_CHECK(DirectInput8Create(g_d3dApp->getAppInst(), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&mDInput, 0));

	// �f�o�C�X�̍쐬
	HR_CHECK(mDInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, 0));
	// �f�[�^�t�H�[�}�b�g��ݒ�
	HR_CHECK(mKeyboard->SetDataFormat(&c_dfDIKeyboard));
	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	HR_CHECK(mKeyboard->SetCooperativeLevel(g_d3dApp->getMainWnd(), keyboardCoopFlags));
	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	HR_CHECK(mKeyboard->Acquire());

	//�}�E�X�f�o�C�X�̍쐬
	HR_CHECK(mDInput->CreateDevice(GUID_SysMouse, &mMouse, 0));
	HR_CHECK(mMouse->SetDataFormat(&c_dfDIMouse2));
	HR_CHECK(mMouse->SetCooperativeLevel(g_d3dApp->getMainWnd(), mouseCoopFlags));
	HR_CHECK(mMouse->Acquire());
}

//�f�X�g���N�^
//==================================================
D3DInput::~D3DInput()
{
	RELEASE_OBJ(mDInput);
	// �L�[�{�[�h�ւ̃A�N�Z�X�����J��(���͐���I��)
	mKeyboard->Unacquire();
	RELEASE_OBJ(mKeyboard);

	mMouse->Unacquire();
	RELEASE_OBJ(mMouse);
}

// �L�[�{�[�h�̍X�V����
void D3DInput::keyUpdate()
{
	BYTE aKeyState[256];

	// �f�o�C�X����f�[�^���擾
	//HRESULT hr = mKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState);
	//if( FAILED(hr) )
	//{
	//	for (int nCnKey = 0; nCnKey < 256; nCnKey++)
	//	{
	//		// �L�[�g���K�[�E�����[�X���𐶐�
	//		g_aKeyStateTrigger[nCnKey] = (mKeyboardState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
	//		g_aKeyStateRelease[nCnKey] = (mKeyboardState[nCnKey] ^ aKeyState[nCnKey]) & mKeyboardState[nCnKey];


	//		// �L�[�v���X����ۑ�
	//		mKeyboardState[nCnKey] = aKeyState[nCnKey];
	//	}
	//	//ZeroMemory(mKeyboardState, sizeof(mKeyboardState));

	//	// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
	//	hr = mKeyboard->Acquire();
	//}
	if (SUCCEEDED(mKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCnKey = 0; nCnKey < 256; nCnKey++)
		{
			// �L�[�g���K�[�E�����[�X���𐶐�
			g_aKeyStateTrigger[nCnKey] = (mKeyboardState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			g_aKeyStateRelease[nCnKey] = (mKeyboardState[nCnKey] ^ aKeyState[nCnKey]) & mKeyboardState[nCnKey];


			// �L�[�v���X����ۑ�
			mKeyboardState[nCnKey] = aKeyState[nCnKey];
		}
		//ZeroMemory(mKeyboardState, sizeof(mKeyboardState));

		
		
	}
	else {
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
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

//�L�[���͏���
//==================================================
bool D3DInput::keyDown(char key)
{
	return (mKeyboardState[key] & 0x80) != 0;
}

//�L�[���͈�񏈗�
//==================================================
bool D3DInput::keyIsTrigger(char key)
{
	return (g_aKeyStateTrigger[key] & 0x80) != 0;
}

bool D3DInput::keyIsRelease(char key)
{
	return (g_aKeyStateRelease[key] & 0x80) != 0;
}

//�}�E�X���͏���
//==================================================
bool D3DInput::mouseButtonDown(int button)
{
	return (mMouseState.rgbButtons[button] & 0x80) != 0;
}

//�}�E�XY���ړ�����
//==================================================
float D3DInput::mouseDY()
{
	POINT po;
	GetCursorPos(&po);
	//return (float)mMouseState.lY;
	return (float)mMouseState.lY;
}