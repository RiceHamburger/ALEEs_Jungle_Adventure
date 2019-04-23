//==================================================
//  �X�R�A�N���X [Score.cpp]        Autor:��
//==================================================
#include "Number.h"
#include "Score.h"

//�`�揈��
//==================================================
void Score::Score_Draw(float x, float y, int score, int fig, bool bLeft, bool bZero)
{
	// �J���X�g�p�̍ő吔�l�����
	int count_stop_score = 1;
	for (int i = 0; i < fig; i++) {
		count_stop_score *= 10;
	}

	if (score >= count_stop_score) {
		score = count_stop_score - 1;
	}


	if (bZero) {
		for (int i = 0; i < fig; i++) {
			int n = score % 10;
			score /= 10;

			Number::Number_Draw(x + NUMBER_WIDTH * (fig - (i + 1)), y, n);
		}
	}
}

// ����������
//==================================================
void Score::Score_Init() {
	Number::Number_Init();
}

//�I������
//==================================================
void Score::Score_Uninit() {
	Number::Number_Uninit();
}