//==================================================
//  �w�i�N���X [background.h]        Autor:��
//==================================================
#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "object.h"

//�w�i�N���X
class BackGround:public Object {
public:
	BackGround(int index, Vector2D pos);	//�R���X�g���N�^
	~BackGround();							//�f�X�g���N�^
};

#endif // BACKGROUND_H_