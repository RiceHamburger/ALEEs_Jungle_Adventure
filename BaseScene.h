//==================================================
//  シーンの基礎クラス [BaseScene.h]        Autor:ロ
//==================================================
#ifndef BASESCENE_H_
#define BASESCENE_H_

#include "D3Dsetup.h"

//シーンの基礎クラス
class BaseScene {
public:
	//virtual void Init() = 0;
	virtual void Update() = 0;		//抽象的な更新処理関数
	virtual void Draw() = 0;		//抽象的な描画処理関数
	virtual void LostDevice() = 0;	//抽象的な最後のデバイス処理関数
	virtual void ResetDevice() = 0;	//抽象的なリセットのデバイス処理関数
};

#endif // BASESCENE_H_