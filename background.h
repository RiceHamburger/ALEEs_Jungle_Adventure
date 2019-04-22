//==================================================
//  背景クラス [background.h]        Autor:ロ
//==================================================
#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "object.h"

//背景クラス
class BackGround:public Object {
public:
	BackGround(int index, Vector2D pos);	//コンストラクタ
	~BackGround();							//デストラクタ
};

#endif // BACKGROUND_H_