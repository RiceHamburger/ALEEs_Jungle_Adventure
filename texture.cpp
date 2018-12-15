#include <d3dx9.h>
#include "direct3d_setup.h"

#define TEXTURE_FILENAME_MAX (30)

typedef struct TextureFile_tag {
	char filename[TEXTURE_FILENAME_MAX];
	int width;
	int height;
}TextureFileData;

static const TextureFileData TEXTURE_FILE_LISE[] = {
	{ "texture/title_bg.png",1024,768 },
	{ "texture/pressspace.png",448,56 },
	{"texture/number.png",320,32},
	{"texture/player.png",256,256},
	{ "texture/Bullet03_64x64.png",16,16 },
	{ "texture/explosjon3.png",512,512 },
	{ "texture/level1_bg.jpg",2048,1536 },
	{ "texture/level1_treebg.png",2048,1536 },
	{ "texture/effect000.jpg",80,80 },
	{ "texture/end_bg.png",1024,768 },
	{ "texture/enemy.png",96,64 },
	{ "texture/tree.png",128,128  },
	{ "texture/mybloodLine.png",256,16 },
	{ "texture/bloodLine100.png",32,4 },
	{ "texture/waterstain.png",192,192 },
	{ "texture/enemy_bullet.png",16,16 },
	{ "texture/player_UI.png",512,64 },
	{ "texture/boss.png",512,512 },
	{ "texture/bossbloodLine.png",700,20 },
	{ "texture/boss_UI.png",1024,64 },
	{ "texture/boss_bullet.png",128,128 },
	{ "texture/number_end.png",320,32},
	{ "texture/health.png",16,16 }
};

static const int TEXTURE_MAX = ARRAYSIZE(TEXTURE_FILE_LISE);
static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_MAX];

int Texture_Load(void) {
	LPDIRECT3DDEVICE9 pDevice = MyDirect3D_GetDevice();
	HRESULT hr;
	int failed_count = 0;

	for (int i = 0;i < TEXTURE_MAX;i++) {
		hr = D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_LISE[i].filename, &g_pTextures[i]);
		
		if (FAILED(hr)) {
			failed_count++;
		}
	}

	return failed_count;
}

void Texture_Release(void) {
	for (int i = 0;i < TEXTURE_MAX;i++) {
		if (g_pTextures[i]) {
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}

LPDIRECT3DTEXTURE9 Texture_GetTexture(int index) {
	return g_pTextures[index];
}

int Texture_GetWidth(int index) {
	return TEXTURE_FILE_LISE[index].width;
}
int Texture_GetHeight(int index) {
	return TEXTURE_FILE_LISE[index].height;
}