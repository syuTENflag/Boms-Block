#include "game.h"

#pragma region �O���ϐ��Ăяo��
int BombX, BombY;	// ���e�̈ʒu
int bombCount;		// �g�����{���̐����J�E���g
bool bombFlg;		// �{����u���Ă��邩�ǂ����̃t���O
#pragma endregion

// ���e�̔z�u
void ArrangementBomb() {
	if (px % SQUARES_SIZE >= SQUARES_SIZE / 2) {
		BombX = SQUARES_SIZE * (px / SQUARES_SIZE) + SQUARES_SIZE;
	}
	else
	{
		BombX = SQUARES_SIZE * (px / SQUARES_SIZE);
	}

	if (py % SQUARES_SIZE >= SQUARES_SIZE / 2) {
		BombY = SQUARES_SIZE * (py / SQUARES_SIZE) + SQUARES_SIZE;
	}
	else
	{
		BombY = SQUARES_SIZE * (py / SQUARES_SIZE);
	}
}