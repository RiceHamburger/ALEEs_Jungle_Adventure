#ifndef CAMERA_H_
#define CAMERA_H_

#include <DirectXMath.h>
#include "player.h"
#include "direct3d_setup.h"

#define CAMERA_TARGET_X (2300)
#define CAMERA_TARGET_Y (760)

class Camera {
private:
	DirectX::XMFLOAT3 scaleFactors;
	D3DXMATRIX orthographicMatrix;
	D3DXMATRIX identityMatrix;
	D3DXMATRIX viewMatrix;
	Player *following;
	float angle;
	int width;
	int height;
	int cameraX;
	int cameraY;

	RECT canSeeRange;
public:
	Camera(int width, int height, float angle, DirectX::XMFLOAT3 scaleFactors);
	~Camera();

	void Update();
	void Follow(Player *following);
	bool IsFollowing() const;
	void SetTransform();
	int GetcameraLX();
	int GetcameraX();
	int GetcameraLY();
	int GetcameraY();
	void Unfollow();

	void SetPositionX(int x);
	void SetPositionY(int y);
	RECT* GetCameraRange();
};


#endif // CAMERA_H_