//==================================================
//  背景クラス [background.cpp]        Autor:ロ
//==================================================
#include "background.h"
#include "sprite.h"
#include "texture.h"

//コンストラクタ
//==================================================
BackGround::BackGround(int index, Vector2D pos)
{
	//背景の位置を設定する
	SetPosition(pos);
	//テクスチャのインデックスを設定する
	SetTextureIndex(index);
	//背景の広さを設定する
	SetWidth(Texture_GetWidth(index));
	//背景の高さを設定する
	SetHeight(Texture_GetHeight(index));
}

//デストラクタ
//==================================================
BackGround::~BackGround(){}