//==================================================
//  ��ʑJ�ڂ̃N���X [fade.cpp]        Autor:��
//==================================================

// �C���N���[�h�t�@�C��
//==================================================
#include "fade.h"
#define FVF_FADE_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

//�t�F�C�g�C�A�E�g�̍�����ʗp�\����
typedef struct
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
} FadeVertex;

//Fade�I�u�W�F�N�g�錾
Fade* g_Fade = NULL;

//�C���X�^���X
//==================================================
Fade::Fade()
{
	init();
}

//�f�X�g���N�^
//==================================================
Fade::~Fade(){}

void Fade::init() {
	g_FadeColor = (0.0f, 0.0f, 0.0f, 1.0f);
	g_Alpha = 0.0f;
	g_AddAlpha = 0.0f;
	g_bOut = false;
	g_bIsFade = false;
}

//�X�V����
//==================================================
void Fade::Update()
{
	static float timeElapsed = 0.0f;
	//timeElapsed += dt;

	if (!g_bIsFade)
	{
		return;
	}

	//0.1�b�ŃA���t�@�l��ς���Ă���
	//if (timeElapsed >= 0.1f) {
		g_Alpha += g_AddAlpha;

		if (g_bOut)
		{
			if (g_Alpha >= 1.0f)
			{
				g_bIsFade = false;
				g_Alpha = 1.0f;

			}
		}
		else
		{
			if (g_Alpha < 0.0f)
			{
				g_Alpha = 0.0f;
				g_bIsFade = false;
			}
		}

		timeElapsed = 0.0f;
	//}
}

//�`�揈��
//==================================================
void Fade::Draw()
{
	if (g_Alpha <= 0.0f)
	{
		return;
	}

	g_FadeColor.a = g_Alpha;
	D3DCOLOR c = g_FadeColor;
	FadeVertex v[] = {
		{ D3DXVECTOR4(0, 0, 1.0f, 1.0f), c },
		{ D3DXVECTOR4(SCREEN_WIDTH, 0, 1.0f, 1.0f), c },
		{ D3DXVECTOR4(0, SCREEN_HEIGHT, 1.0f, 1.0f), c },
		{ D3DXVECTOR4(SCREEN_WIDTH, SCREEN_HEIGHT, 1.0f, 1.0f), c },
	};

	g_d3dDevice->SetFVF(FVF_FADE_VERTEX);
	g_d3dDevice->SetTexture(0, NULL);
	g_d3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(FadeVertex));
}

void Fade::Fade_Start(bool bOut, int frame, D3DCOLOR color)
{
	g_bOut = bOut;
	g_AddAlpha = 1.0f / frame;
	g_FadeColor = color;
	g_bIsFade = true;

	if (g_bOut)
	{
		g_Alpha = 0.0f;
	}
	else
	{
		g_Alpha = 1.0f;
		g_AddAlpha = -g_AddAlpha;
	}
}

bool Fade::Fade_IsFade(void)
{
	return g_bIsFade;
}