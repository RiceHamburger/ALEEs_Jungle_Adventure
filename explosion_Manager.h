#ifndef EXPLOSION_MANAGER_H
#define EXPLOSION_MANAGER_H

#include "explosion.h"

void Explosion_Manager_Init(void);
void Explosion_Manager_Update(void);
void Explosion_Manager_Draw(void);
void Explosion_Manager_Uninit(void);

void Explosion_Create(float x, float y);

#endif