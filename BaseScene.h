//==================================================
//  シーンの基礎クラス [BaseScene.h]        Autor:ロ
//==================================================
#ifndef BASESCENE_H_
#define BASESCENE_H_

#include "D3Dsetup.h"

class BaseScene {
public:
	//virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void LostDevice() = 0;
	virtual void ResetDevice() = 0;
};

#endif // BASESCENE_H_