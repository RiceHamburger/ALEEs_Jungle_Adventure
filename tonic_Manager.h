#ifndef TONIC_MANAGER_H
#define TONIC_MANAGER_H

#include "tonic.h"

void Tonic_Manager_Init(void);
void Tonic_Manager_Update(void);
void Tonic_Manager_Draw(void);
void Tonic_Manager_Uninit(void);

void Tonic_Create(float x, float y);
bool Tonic_IsEnable(void);
Tonic *TonicMgrGetTonic(void);

#endif