#ifndef HEALTHBAR_H_
#define HEALTHBAR_H_

#define HEALTHBAR_WIDTH	(256)//2“IŽŸ•û
#define HEALTHBAR_HEIGHT (16)
#define HEALTHBAR_TOTAL	(200)
#define HEALTHBAR_X (98.0f)
#define HEALTHBAR_Y (60.0f)

void Healthbar_Draw(float x, float y, int nowHealth);
void Healthbar_Init();
void Healthbar_Uninit();

#endif // HEALTHBAR_H_