#ifndef TONIC_H_
#define TONIC_H_

#include "texture.h"
#include "object.h"

#define TONIC_MAX (20)
#define TONIC_WIDTH (16)

#define TONIC_ADD_HEALTH (50)

class Tonic :public Object {
protected:
	int addHealth;
public:
	Tonic();
	~Tonic();
	void InitTonic(Vector2D pos, TEXTURE_NAME tex_name);
	void TonicActive();
	void TonicDestroy();

	void resetCollision();
	int GetAddHealth();
};

#endif //TONIC_H_