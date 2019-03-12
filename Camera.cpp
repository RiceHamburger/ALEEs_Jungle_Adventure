#include "Camera.h"
//#include "D3Dsetup.h"

Camera::Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors)
{

	this->width = width;
	this->height = height;
	this->angle = angle;
	this->scaleFactors = scaleFactors;

	D3DXMatrixOrthoLH(&orthographicMatrix, width, -height, -1000.0f, 1000.0f);
	D3DXMatrixIdentity(&identityMatrix);
	following = NULL;

	cameraX = 0;
	cameraY = 0;
	canSeeRange.left = cameraX - SCREEN_WIDTH/2;
	canSeeRange.top = cameraY - SCREEN_HEIGHT/2;
	canSeeRange.right = cameraX + SCREEN_WIDTH/2;
	canSeeRange.bottom = cameraY + SCREEN_HEIGHT / 2;
}

Camera::~Camera()
{

}

void Camera::Update()
{
	if (this->following)
	{
		cameraX = this->following->GetPosition().x + 64;
		cameraY = this->following->GetPosition().y + 64;
	}

	canSeeRange.left = cameraX - SCREEN_WIDTH / 2;
	canSeeRange.top = cameraY - SCREEN_HEIGHT / 2;
	canSeeRange.right = cameraX + SCREEN_WIDTH / 2;
	canSeeRange.bottom = cameraY + SCREEN_HEIGHT / 2;

	this->viewMatrix = D3DXMATRIX(
		scaleFactors.x * cos(angle), scaleFactors.x * sin(angle), 0, 0,
		-scaleFactors.y * sin(angle), scaleFactors.y * cos(angle), 0, 0,
		0, 0, scaleFactors.z, 0,
		-cameraX * scaleFactors.x * cos(angle) + cameraY * scaleFactors.y * sin(angle), -cameraX * scaleFactors.y * sin(angle) - cameraY * scaleFactors.y * cos(angle), 0, 1
	);
}

void Camera::Follow(Player* following)
{
	this->following = following;
}

bool Camera::IsFollowing() const
{
	return this->following != NULL;
}

void Camera::SetTransform()
{
	g_d3dDevice->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	g_d3dDevice->SetTransform(D3DTS_WORLD, &identityMatrix);
	g_d3dDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
}

int Camera::GetcameraLX() {
	return this->cameraX - this->width / 2;
}

int Camera::GetcameraLY() {
	return this->cameraY - this->height / 2;
}

int Camera::GetcameraX() {
	return this->cameraX;
}

int Camera::GetcameraY() {
	return this->cameraY;
}

void Camera::Unfollow()
{
	this->following = NULL;
}

void Camera::SetPositionX(int x) {
	this->cameraX += x;
}

void Camera::SetPositionY(int y) {
	this->cameraY += y;
}

RECT* Camera::GetCameraRange() {
	return &canSeeRange;
}