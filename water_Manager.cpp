#include "water_Manager.h"

D3DXVECTOR3 water_position[WATER_MAX] = {
	{ 118,202,0},
	{ 958,383,0 },
	{ 1438,802,0 },
	{ 2578,922,0 }
};

WaterStain waterStain[WATER_MAX];

void Water_Manager_Init(void) {
	for (int i = 0;i < WATER_MAX;i++) {
		waterStain[i].SetPosition(water_position[i]);
		waterStain[i].InitSprite();
	}
}

void Water_Manager_Update(void) {
	for (int i = 0;i < WATER_MAX;i++) {
		waterStain[i].UpdateSprite();
	}
}

void Water_Manager_Draw(void) {
	for (int i = 0;i < WATER_MAX;i++) {
		waterStain[i].DrawSprite();
	}
}

void Water_Manager_Uninit(void) {
	for (int i = 0;i < WATER_MAX;i++) {
		waterStain[i].Sprite_Uninit();
	}
}