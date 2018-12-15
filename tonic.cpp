#include "tonic.h"


Tonic::Tonic() {

}
Tonic::~Tonic() {

}

void Tonic::InitTonic(Vector2D pos, TEXTURE_NAME tex_name) {
	Circle objCollision;
	SetPosition(pos);
	SetTextureIndex(tex_name);
	SetWidth(Texture_GetWidth(tex_name));
	SetHeight(Texture_GetHeight(tex_name));

	//îªíËÇÃâ~Çê›íËÇ∑ÇÈ
	objCollision.cx = pos.x + GetWidth() / 2;
	objCollision.cy = pos.y + GetHeight() / 2;
	objCollision.r = GetWidth()*0.5f;
	SetCircleCollision(objCollision);

	addHealth = TONIC_ADD_HEALTH;
}

void Tonic::TonicActive() {

}

void Tonic::TonicDestroy() {
	SetLiveFlag(false);
}

int Tonic::GetAddHealth() {
	return addHealth;
}

void Tonic::resetCollision() {
	Vector2D position = GetPosition();
	SetCircleCollisionX(position.x + GetWidth() / 2);
	SetCircleCollisionY(position.y + GetWidth() / 2);
}