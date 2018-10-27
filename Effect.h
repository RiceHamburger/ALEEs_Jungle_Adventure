#ifndef EFFECT_H_
#define EFFECT_H_

#include <d3dx9.h>

void Effect_Initialize(void);
void Effect_Finalize(void);
void Effect_Update(void);
void Effect_Draw(void);

void Effect_Creat(float x, float y, float radius, int life, D3DCOLOR color);

#endif // EFFECT_H_