//==================================================
//  �������ʊǗ��҃N���X [ExplosionManager.h]        Autor:��
//==================================================

#ifndef EXPLOSIONMANAGER_H
#define EXPLOSIONMANAGER_H

#include "explosion.h"

class ExplosionManager {
public:
	static void Explosion_Manager_Init(void);
	static void Explosion_Manager_Update(void);
	static void Explosion_Manager_Draw(void);
	static void Explosion_Manager_Uninit(void);

	static void Explosion_Create(float x, float y);
private:
	static Explosion explosion[EXPLOSION_MAX];
};


#endif