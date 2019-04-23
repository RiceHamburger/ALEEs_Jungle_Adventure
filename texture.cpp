//==================================================
//  �e�N�X�`��load [texture.cpp]        Autor:��
//==================================================
#include "D3Dsetup.h"
#include "texture.h"

//�t�@�C���l�[���̍ő��
#define TEXTURE_FILENAME_MAX (30)

//�e�N�X�`���t�@�C���̍\����
typedef struct TextureFile_tag {
	char filename[TEXTURE_FILENAME_MAX];
	int width;
	int height;
}TextureFileData;

//�e�N�X�`���t�@�C���̔z��
static const TextureFileData TEXTURE_FILE_LISE[] = {
	{ "texture/title_bg.png",1024,768 },
	{ "texture/pressspace.png",448,56 },
	{ "texture/number.png",320,32 },
	{ "texture/player.png",256,256 },
	{ "texture/Bullet03_64x64.png",16,16 },
	{ "texture/explosjon3.png",512,512 },
	{ "texture/level1_bg.jpg",2048,1536 },
	{ "texture/level1_treebg.png",2048,1536 },
	{ "texture/effect000.jpg",80,80 },
	{ "texture/end_bg.png",1024,768 },
	{ "texture/enemy.png",96,64 },
	{ "texture/tree.png",128,128 },
	{ "texture/mybloodLine.png",256,16 },
	{ "texture/bloodLine100.png",32,4 },
	{ "texture/waterstain.png",192,192 },
	{ "texture/enemy_bullet.png",16,16 },
	{ "texture/player_UI.png",512,64 },
	{ "texture/boss.png",512,512 },
	{ "texture/bossbloodLine.png",700,20 },
	{ "texture/boss_UI.png",1024,64 },
	{ "texture/boss_bullet.png",128,128 },
	{ "texture/number_end.png",320,32 },
	{ "texture/health.png",16,16 },
	{ "texture/gun.png",32,18 },
	{ "texture/enemy_red.png",96,64 },
};

// �ÓI�����o�ϐ�
//==================================================
static const int TEXTURE_MAX = ARRAYSIZE(TEXTURE_FILE_LISE);
static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_MAX];

// �e�N�X�`�����[�h����
//==================================================
int Texture_Load(void) {
	HRESULT hr;
	int failed_count = 0;

	for (int i = 0;i < TEXTURE_MAX;i++) {
		hr = D3DXCreateTextureFromFile(g_d3dDevice, TEXTURE_FILE_LISE[i].filename, &g_pTextures[i]);
		
		if (FAILED(hr)) {
			failed_count++;
		}
	}

	return failed_count;
}

//�I������
//==================================================
void Texture_Release(void) {
	for (int i = 0;i < TEXTURE_MAX;i++) {
		if (g_pTextures[i]) {
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}

//�e�N�X�`�������
//==================================================
LPDIRECT3DTEXTURE9 Texture_GetTexture(int index) {
	return g_pTextures[index];
}

//�e�N�X�`���̍L�������
//==================================================
int Texture_GetWidth(int index) {
	return TEXTURE_FILE_LISE[index].width;
}

//�e�N�X�`���̍��������
//==================================================
int Texture_GetHeight(int index) {
	return TEXTURE_FILE_LISE[index].height;
}