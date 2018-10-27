#ifndef TREE_H_
#define TREE_H_

#include "direct3d_setup.h"

#define TREE_WIDTH	(128)
#define TREE_HEIGHT	(128)
#define TREE_MAX	(77)
#define TREE_COLLSION_MAX	(22)

class TREE {
private:
	D3DXVECTOR3 position;
	LPD3DXSPRITE sprite;
	D3DCOLOR color;
	RECT collision_rec;
public:
	TREE();
	~TREE();
	void InitTREE(D3DXVECTOR3 Position);
	void DrawTREE();
	void UninitTREE();
	RECT GetCollision();
};

#endif // TREE_H_