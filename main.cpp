//==================================================
//  �v���W�F�N�g��MAIN [main.cpp]        Autor:��
//==================================================

// �C���N���[�h�t�@�C��
//==================================================
#include "D3Dsetup.h"
#include <tchar.h>
#include "texture.h"
#include "D3DInput.h"
#include "SceneManager.h"
#include "sound.h"
#include "fade.h"

class ShowcaseD3DApp : public D3DApp
{
public:
	ShowcaseD3DApp(HINSTANCE hInstance, std::string winCaption, D3DDEVTYPE devType, DWORD requestedVP);
	~ShowcaseD3DApp();

	bool checkDeviceCaps();
	void onLostDevice();
	void onResetDevice();
	void initScene();
	void updateScene();
	void drawScene();

private:
	
};

//main
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int showCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdline);

	ShowcaseD3DApp app(hInstance, "Terrain Adventure", D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING);
	g_d3dApp = &app;

	D3DInput d3dInput(DISCL_NONEXCLUSIVE | DISCL_FOREGROUND, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	gDInput = &d3dInput;

	//�t�F�C�g�C���A�E�g
	Fade fade;
	g_Fade = &fade;

	return g_d3dApp->run();
}

ShowcaseD3DApp::ShowcaseD3DApp(HINSTANCE hInstance, std::string winCaption, D3DDEVTYPE devType, DWORD requestedVP) : D3DApp(hInstance, winCaption, devType, requestedVP)
{
	srand(time_t(0));

	if (!checkDeviceCaps())
	{
		MessageBox(0, "checkDeviceCaps() Failed", 0, 0);
		PostQuitMessage(0);
	}
	
}

ShowcaseD3DApp::~ShowcaseD3DApp()
{
	Texture_Release();
	UninitSound();
}

bool ShowcaseD3DApp::checkDeviceCaps()
{
	return true;
}

void ShowcaseD3DApp::onLostDevice()
{
	SceneManager::LostDevice();
}

void ShowcaseD3DApp::onResetDevice()
{
	SceneManager::ResetDevice();
}

//�Q�[���̏�����
void ShowcaseD3DApp::initScene()
{
	Texture_Load();
	InitSound(g_d3dApp->getMainWnd());

	//Render set
	//�A���t�@�u�����h
	g_d3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//�w�i�i���ɕ`���ꂽ��ԁjDEST�̃u�����h�ݒ�
	g_d3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//������`���|���S��SRC�̃u�����h�ݒ�
	g_d3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_d3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	SceneManager::ChangeScene(SceneManager::TITLE);
	onResetDevice();
}

//�Q�[���̍X�V
void ShowcaseD3DApp::updateScene()
{
	//input update
	gDInput->keyUpdate();

	//fade in/out
	g_Fade->Update();

	SceneManager::Update();
}

//�Q�[���̕`��
void ShowcaseD3DApp::drawScene()
{
	HR_CHECK(g_d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0));

	HR_CHECK(g_d3dDevice->BeginScene());

	SceneManager::Draw();

	//fade in/out
	g_Fade->Draw();

	HR_CHECK(g_d3dDevice->EndScene());
	HR_CHECK(g_d3dDevice->Present(0, 0, 0, 0));
}