#include "Camera.h"

//コンストラクタ
//==================================================
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

//デストラクタ
//==================================================
Camera::~Camera()
{

}

//更新処理
//==================================================
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

//フォローする目標を設定する
//==================================================
void Camera::Follow(Player* following)
{
	this->following = following;
}

//フォローしているか
//==================================================
bool Camera::IsFollowing() const
{
	return this->following != NULL;
}

//Transform設定処理
//==================================================
void Camera::SetTransform()
{
	g_d3dDevice->SetTransform(D3DTS_PROJECTION, &orthographicMatrix);
	g_d3dDevice->SetTransform(D3DTS_WORLD, &identityMatrix);
	g_d3dDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
}

//カメラ見える範囲の左X座標を取る
//==================================================
int Camera::GetcameraLX() {
	return this->cameraX - this->width / 2;
}

//カメラ見える範囲の左Y座標を取る
//==================================================
int Camera::GetcameraLY() {
	return this->cameraY - this->height / 2;
}

//カメラX座標を取る
//==================================================
int Camera::GetcameraX() {
	return this->cameraX;
}

//カメラY座標を取る
//==================================================
int Camera::GetcameraY() {
	return this->cameraY;
}

//フォローしない設定
//==================================================
void Camera::Unfollow()
{
	this->following = NULL;
}

//X座標を設定する
//==================================================
void Camera::SetPositionX(int x) {
	this->cameraX += x;
}

//Y座標を設定する
//==================================================
void Camera::SetPositionY(int y) {
	this->cameraY += y;
}

//カメラが見える範囲を取る
//==================================================
RECT* Camera::GetCameraRange() {
	return &canSeeRange;
}