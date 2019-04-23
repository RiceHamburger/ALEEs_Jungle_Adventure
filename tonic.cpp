//==================================================
// �A�C�e���N���X [tonic.cpp]        Autor:��
//==================================================
#include "tonic.h"

//�C���X�^���X
//==================================================
Tonic::Tonic() {

}
//�f�X�g���N�^
//==================================================
Tonic::~Tonic() {

}

// ����������
//==================================================
void Tonic::InitTonic(Vector2D pos, TEXTURE_NAME tex_name,TonicState state) {
	Circle objCollision;
	SetPosition(pos);
	SetTextureIndex(tex_name);
	SetWidth(Texture_GetWidth(tex_name));
	SetHeight(Texture_GetHeight(tex_name));

	//����̉~��ݒ肷��
	objCollision.cx = pos.x + GetWidth() / 2;
	objCollision.cy = pos.y + GetHeight() / 2;
	objCollision.r = GetWidth()*0.5f;
	SetCircleCollision(objCollision);

	addHealth = TONIC_ADD_HEALTH;
	this_TonicState = state;
}

//�X�V����
//==================================================
void Tonic::TonicActive() {

}

//�p������
//==================================================
void Tonic::TonicDestroy() {
	SetLiveFlag(false);
}

//�����͂����
//==================================================
int Tonic::GetAddHealth() {
	return addHealth;
}

//�R���W���������
//==================================================
void Tonic::resetCollision() {
	Vector2D position = GetPosition();
	SetCircleCollisionX(position.x + GetWidth() / 2);
	SetCircleCollisionY(position.y + GetWidth() / 2);
}

//�A�C�e���̃^�C�v�����
//==================================================
int Tonic::GetState() {
	return this_TonicState;
}