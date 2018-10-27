#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <Windows.h>
#include <d3dx9.h>

typedef enum {
	TITLE,
	TITLEBTN,
	NUMBER,
	kMAJYO,
	BULLET,
	EXPLOSION,
	LEVEL_BG,
	LEVEL_TREEBG,
	EFFECT,
	END,
	ENEMY,
	TREE_TEXTURE,
	HEALTH_BAR,
	ENEMYBAR,
	WATERSTAIN,
	SURAIMUBULLET,
	PLAYER_UI,
	BOSS_IMG,
	BOSS_HPBAR,
	BOSS_UI,
	BOSS_BIG_BULLET,
	NUMBER_END
}TEXTURE_NAME;

int Texture_Load(void);
void Texture_Release(void);

LPDIRECT3DTEXTURE9 Texture_GetTexture(int index);

int Texture_GetWidth(int index);
int Texture_GetHeight(int index);

#endif // TEXTURE_H_