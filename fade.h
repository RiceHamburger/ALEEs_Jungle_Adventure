//==================================================
//  âÊñ ëJà⁄ÇÃÉNÉâÉX [fade.h]        Autor:Éç
//==================================================
#pragma warning

#ifndef FADE_H_
#define FADE_H_

#include "D3Dsetup.h"

class Fade {
public:
	Fade();
	~Fade();
	void init();
	void Update();
	void Draw();
	void Fade_Start(bool bOut, int frame, D3DCOLOR color);
	bool Fade_IsFade(void);

private:
	D3DXCOLOR g_FadeColor;
	float g_Alpha;
	float g_AddAlpha;
	bool g_bOut;
	bool g_bIsFade;
};

#endif // FADE_H_