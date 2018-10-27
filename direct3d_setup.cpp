#include <Windows.h>
#include <d3dx9.h>
#include "direct3d_setup.h"
#include "common.h"

/*-----------------------------
�O���[�o���ϐ��錾
-----------------------------*/
static LPDIRECT3D9 g_pD3D = NULL;
static LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
static D3DPRESENT_PARAMETERS g_D3DPP;

//LPDIRECT3DTEXTURE9 g_pTexture = NULL;


bool MyDirect3D_Initialize(HWND hWnd) {
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	/*
	D3DPRESENT_PARAMETERS �\����
	*/
	ZeroMemory(&g_D3DPP, sizeof(g_D3DPP));
	g_D3DPP.Windowed = TRUE; //�E�B���h�E���[�h���w��
	g_D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD; //�X���b�v�D�G�t�F�N�g
	g_D3DPP.BackBufferFormat = D3DFMT_UNKNOWN;//�o�b�N�o�b�t�@
	g_D3DPP.BackBufferWidth = SCREEN_WIDTH;
	g_D3DPP.BackBufferHeight = SCREEN_HEIGHT;
	g_D3DPP.BackBufferCount = 1;
	g_D3DPP.hDeviceWindow = hWnd;
	g_D3DPP.EnableAutoDepthStencil = TRUE; //�K��TRUE
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
	//dds���k�����܂܃������ɓ����A�e�ʓI�ɗL��
	//file name
	/*if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "rekobenichan.png", &g_pTexture))) {
		return false;
	}*/

	//�A���t�@�u�����h
	//�������d��
	//�pswitch�I���|������p��@
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//�w�i�i���ɕ`���ꂽ��ԁjDEST�̃u�����h�ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//������`���|���S��SRC�̃u�����h�ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	return true;
}

//Direct3D�I������
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

//Direct3D�f�o�C�X�|�C���^�̎擾
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void) {
	return g_pD3DDevice;
}