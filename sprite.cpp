//==================================================
//  sprite�N���X [Sprite.cpp]        Autor:��
//==================================================

#include <d3dx9.h>
#include "texture.h"
#include "D3Dsetup.h"
#include "sprite.h"

// �ÓI�����o�ϐ�
//==================================================
D3DCOLOR Sprite::m_Color = 0xffffffff;
LPDIRECT3DVERTEXBUFFER9 Sprite::g_pVertexBuffer = NULL;

Sprite::Sprite(){}
Sprite::~Sprite() {}

void Sprite::Sprite_SetColor(D3DCOLOR color) {
	m_Color = color;
}

//�摜�C���f�b�N�X�AX���W�AY���W
void Sprite::Sprite_Draw(int texture_index, float dx, float dy) {

	float texture_width = (float)Texture_GetWidth(texture_index);
	float texture_height = (float)Texture_GetHeight(texture_index);

	float texture_Tx = dx - 0.5f;
	float texture_Ty = dy - 0.5f;
	float texture_Tw = dx + texture_width - 0.5f;
	float texture_Th = dy + texture_height - 0.5f;

	Vertex2D Square[] = {
		{ D3DXVECTOR4(texture_Tx, texture_Ty, 1.0f, 1.0f), m_Color,D3DXVECTOR2(0.0f,0.0f) },//0 0
		{ D3DXVECTOR4(texture_Tw, texture_Ty, 1.0f, 1.0f), m_Color,D3DXVECTOR2(1.0f,0.0f) },//1 1
		{ D3DXVECTOR4(texture_Tx, texture_Th, 1.0f, 1.0f), m_Color,D3DXVECTOR2(0.0f,1.0f) },//3 2
		{ D3DXVECTOR4(texture_Tw, texture_Th, 1.0f, 1.0f), m_Color,D3DXVECTOR2(1.0f,1.0f) }//2 4
	};


	//���_�C���f�b�N�X
	WORD index[] = {
		0,1,2,
		1,3,2,
	};

	g_d3dDevice->SetFVF(FVF_VERTEX2D);
	g_d3dDevice->SetTexture(0, Texture_GetTexture(texture_index));

	g_d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_d3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);


	//Square
	g_d3dDevice->DrawIndexedPrimitiveUP(
		D3DPT_TRIANGLELIST,
		0,
		4,
		2,
		index,
		D3DFMT_INDEX16,
		Square,
		sizeof(Vertex2D)
	);
}

//�摜�C���f�b�N�X�AX���W�AY���W�A�e�N�X�`���̉摜X���W�A�e�N�X�`���̉摜Y���W�A�摜�̉��T�C�Y�A�摜�̗��ăT�C�Y
void Sprite::Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th) {
	
	float texture_width = Texture_GetWidth(texture_index);
	float texture_height = Texture_GetHeight(texture_index);

	float texture_Tx = dx - 0.5f;
	float texture_Ty = dy - 0.5f;
	float texture_Tw = dx + texture_width - 0.5f;
	float texture_Th = dy + texture_height - 0.5f;

	float u0 = (float)tx / texture_width;
	float v0 = (float)ty / texture_height;
	float u1 = (float)(tx + tw) / texture_width;
	float v1 = (float)(ty + th) / texture_height;

	Vertex2D Square[] = {
		{ D3DXVECTOR4(texture_Tx, texture_Ty, 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(tw + texture_Tx, texture_Ty, 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(texture_Tx, texture_Ty + th, 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(tw + texture_Tx, texture_Ty + th, 1.0f, 1.0f), D3DCOLOR_RGBA(255, 255, 255, 255),D3DXVECTOR2(u1,v1) }
	};

	//���z�A�h���X
	Vertex2D* pV;

	//���_�o�b�t�@�̃��b�N
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	memcpy(pV, Square, sizeof(Square));
	g_pVertexBuffer->Unlock();

	g_d3dDevice->SetFVF(FVF_VERTEX2D);
	g_d3dDevice->SetTexture(0, Texture_GetTexture(texture_index));



	g_d3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_d3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_d3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	g_d3dDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Square));

	//Square
	g_d3dDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,
		2,
		Square,
		sizeof(Square[0])
		);

}

void Sprite::Sprite_Initialize(void) {

	//���_�o�b�t�@�̊m��
	g_d3dDevice->CreateVertexBuffer(sizeof(Vertex2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX2D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
}

void Sprite::Sprite_Finalize(void) {
	//���_�o�b�t�@�̉��
	if (g_pVertexBuffer) {
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
}