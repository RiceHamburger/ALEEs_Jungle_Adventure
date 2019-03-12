//==================================================
//  DirectX�ݒ�N���X [D3Dsetup.h]        Autor:��
//==================================================

#ifndef D3DSETUP_H
#define D3DSETUP_H

// �C���N���[�h�t�@�C��
//==================================================
#include <d3dx9.h>
#include <dxerr.h>
#include <string>
#include <vector>

// �O���[�o���֐�
//==================================================
class D3DApp;
extern D3DApp* g_d3dApp;
extern LPDIRECT3DDEVICE9 g_d3dDevice;
class Fade;
extern Fade* g_Fade;

// �}�N����`
//==================================================
// ���������
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
//��ʃX�^�C��
#define WINDOW_STYLE (WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME))
//��ʃT�C�g
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

	//�f�o�C�X�̊֐�
	virtual bool checkDeviceCaps() { return true; }
	virtual void onLostDevice() {}
	virtual void onResetDevice() {}
	//������
	virtual void initScene() {}
	//�X�V
	virtual void updateScene() {}
	//�`��
	virtual void drawScene() {}

	//�E�B���h�E�Y��D3D������
	virtual void initMainWindow();
	virtual void initDirect3D();
	virtual int run();
	virtual LRESULT msgProc(UINT msg, WPARAM wParam, LPARAM lParam);

	//�S��ʃ��[�h
	void enableFullScreenMode(bool enable);
	bool isDeviceLost();

protected:
	//�E�B���h�E�Y�l�[��
	std::string mMainWndCaption;
	//�E�B���h�E�Y�^�C�v
	D3DDEVTYPE  mDevType;
	//
	DWORD       mRequestedVP;

	// �A�v���P�[�V����, �E�B���h�E�Y, Direct3D�̃f�[�^
	HINSTANCE             mhAppInst;
	HWND                  mhMainWnd;
	LPDIRECT3D9           md3dObject;
	bool                  mAppPaused;
	D3DPRESENT_PARAMETERS md3dPP;
};

#endif // D3DSETUP_H