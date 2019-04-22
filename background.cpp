//==================================================
//  �w�i�N���X [background.cpp]        Autor:��
//==================================================
#include "background.h"
#include "sprite.h"
#include "texture.h"

//�R���X�g���N�^
//==================================================
BackGround::BackGround(int index, Vector2D pos)
{
	//�w�i�̈ʒu��ݒ肷��
	SetPosition(pos);
	//�e�N�X�`���̃C���f�b�N�X��ݒ肷��
	SetTextureIndex(index);
	//�w�i�̍L����ݒ肷��
	SetWidth(Texture_GetWidth(index));
	//�w�i�̍�����ݒ肷��
	SetHeight(Texture_GetHeight(index));
}

//�f�X�g���N�^
//==================================================
BackGround::~BackGround(){}