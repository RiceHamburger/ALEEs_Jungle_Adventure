//==================================================
//  …‚ÌŠÇ—ÒƒNƒ‰ƒX [WaterManager.h]        Autor:ƒ
//==================================================

#ifndef WATERMANAGER_H
#define WATERMANAGER_H

#include "water_stain.h"

class WaterManager {
public:
	static void Water_Manager_Init(void);
	static void Water_Manager_Update(void);
	static void Water_Manager_Draw(void);
	static void Water_Manager_Uninit(void);
private:
	static D3DXVECTOR3 water_position[WATER_MAX];
	static WaterStain waterStain[WATER_MAX];
};


#endif