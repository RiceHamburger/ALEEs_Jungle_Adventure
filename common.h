#ifndef COMMON_H_
#define COMMON_H_

//2D�x�N�g���\����
typedef struct{
	float x;
	float y;
}Vector2D;

//�~�̍\����
typedef struct{
	float cx, cy;
	float r;
}Circle;

//�Q�[���̍L���ݒ�
#define SCREEN_WIDTH (1024)
//�Q�[���̍����ݒ�
#define SCREEN_HEIGHT (768)

#endif // COMMON_H_