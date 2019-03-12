#ifndef TONIC_H_
#define TONIC_H_

#include "texture.h"
#include "object.h"

#define TONIC_MAX (10)
#define TONIC_WIDTH (16)

#define TONIC_ADD_HEALTH (50)

typedef enum
{
	HPUP,
	SHOOTGUN
}TonicState;

class Tonic :public Object {
protected:
	int addHealth;
	
	int this_TonicState;
public:
	Tonic();
	~Tonic();
	void InitTonic(Vector2D pos, TEXTURE_NAME tex_name,TonicState state);
	void TonicActive();
	void TonicDestroy();

	void resetCollision();
	int GetAddHealth();
	int GetState();
};

#endif //TONIC_H_