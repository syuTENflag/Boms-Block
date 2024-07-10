#include "game.h"

#pragma region �O���ϐ��Ăяo��
int px, py;			// ��l���̈ʒu
#pragma endregion

#pragma region �v���C���[�̈ړ�
/*
	�e������for���[�v���݂̂̕ϐ�x�Ay�͂��̂܂܎g���ƃ}�b�v�f�[�^�̒l�ɂȂ邽�߁A
	�v���C���[���W�ɑ������ꍇ�̓}�X�ڂ̃T�C�Y��������
	�v���C���[���W�Ƃ̏����������ꍇ�̓v���C���[���W�̒l���}�X�ڂ̃T�C�Y�Ŋ������l�̐����l���g��
*/


// �E
void PlayerRightMove() {
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			// �E�ׂ̗̃}�X���ǂ��ǂ�������i���W�ύX������֐����ōs���j
			if (((px + PLAYER_SIZE + 1) / SQUARES_SIZE == x) && (py / SQUARES_SIZE == y)) {
				RightHitWall(x, y);
			}
			//px�Apy�̈ʒu������ɂ��ăL�����摜�i�E�ړ��j��`��
			DrawExtendGraph(px, py, px + PLAYER_SIZE, py + PLAYER_SIZE, img02[13], TRUE);
			
		}
	}
}

// ��
void PlayerLeftMove() {
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			// ���ׂ̗̃}�X���ǂ��ǂ�������i���W�ύX������֐����ōs���j
			if (((px - 1) / SQUARES_SIZE == x) && (py / SQUARES_SIZE == y)) {
				LeftHitWall(x, y);
			}
			//px�Apy�̈ʒu������ɂ��ăL�����摜�i���ړ��j��`��
			DrawExtendGraph(px, py, px + PLAYER_SIZE, py + PLAYER_SIZE, img02[9], TRUE);
			
		}
	}
}

// ��
void PlayerUpMove() {
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			// ��ׂ̗̃}�X���ǂ��ǂ�������i���W�ύX������֐����ōs���j
			if ((px / SQUARES_SIZE == x) && ((py - 1) / SQUARES_SIZE == y)) {
				UpHitWall(x, y);
			}
			//px�Apy�̈ʒu������ɂ��ăL�����摜�i��ړ��j��`��
			DrawExtendGraph(px, py, px + PLAYER_SIZE, py + PLAYER_SIZE, img02[1], TRUE);
			
		}
	}
}

// ��
void PlayerDownMove() {
	for (int y = 0; y < STAGE_HEIGHT; y++) {
		for (int x = 0; x < STAGE_WIDTH; x++) {
			// ���ׂ̗̃}�X���ǂ��ǂ�������i���W�ύX������֐����ōs���j
			if ((px / SQUARES_SIZE == x) && ((py + PLAYER_SIZE + 1) / SQUARES_SIZE == y)) {
				DownHitWall(x, y);
			}
			//px�Apy�̈ʒu������ɂ��ăL�����摜�i���ړ��j��`��
			DrawExtendGraph(px, py, px + PLAYER_SIZE, py + PLAYER_SIZE, img02[5], TRUE);
			
		}
	}
}
#pragma endregion

#pragma region �v���C���[�ƕǂ̓����蔻��
/*
	���ꂼ��̈ړ��������}�X�̃}�X�ڂ̒l���n����Ă���̂ŁA�܂����̃}�X���ǂ��u���b�N���Ȃɂ��Ȃ����𔻒肷��
	�����ǂ��u���b�N�ł�������A�v���C���[�̂���ʒu�𒲂ׁA
	�ړ��������}�X�ׂ̗荇���}�X�i�v���C���[�����Ȃ������j�������Ȃ���΂��̕����Ɉړ�������

	�ړ��������}�X�������Ȃ��ꍇ�́A�ړ������������ł͂Ȃ��ix�Ȃ�y�Ay�Ȃ�x�j�̉E�i���j�[�̍��W��y(x)+1�����ׂ�
	���������ł���΁A�ړ������������ł͂Ȃ��ix�Ȃ�y�Ay�Ȃ�x�j��+1�����}�X�������Ȃ������ׂ�
	���������������ꍇ�́A��قǑ������Ƃ�������Ƃɖ߂����l�𒲂ׂĉ����Ȃ���΂��̕����Ɉړ������A
	�����Ȃ���Έړ��������}�X�Ɍ����ړ�������

	��L�̔���łȂɂ��Ȃ���Έړ��������}�X�ɂ͉����Ȃ��̂ł��̂܂܈ړ�������
*/

// �E
void RightHitWall(int x, int y) {
	if (mapData[y][x] != SQUARE_NONE) {
		if (mapData[y + 1][x - 1] == SQUARE_NONE) {
			py += 1;
		}
		else if (mapData[y - 1][x - 1] == SQUARE_NONE) {
			py -= 1;
		}
	}
	else if ((py + PLAYER_SIZE) / SQUARES_SIZE == y + 1) {
		if (mapData[y + 1][x] != SQUARE_NONE) {
			if (mapData[y][x - 1] == SQUARE_NONE) {
				py -= 1;
			}
		}
		else {
			px += 1;
		}
	}
	else {
		px += 1;
	}
}

// ��
void LeftHitWall(int x, int y) {
	if (mapData[y][x] != SQUARE_NONE) {
		if (mapData[y + 1][x + 1] == SQUARE_NONE) {
			py += 1;
		}
		else if (mapData[y - 1][x + 1] == SQUARE_NONE) {
			py -= 1;
		}
	}
	else if ((py + PLAYER_SIZE) / SQUARES_SIZE == y + 1) {
		if (mapData[y + 1][x] != SQUARE_NONE) {
			if (mapData[y][x + 1] == SQUARE_NONE) {
				py -= 1;
			}
		}
		else {
			px -= 1;
		}
	}
	else {
		px -= 1;
	}
}

// ��
void UpHitWall(int x, int y) {
	if (mapData[y][x] != SQUARE_NONE) {
		if (mapData[y + 1][x + 1] == SQUARE_NONE) {
			px += 1;
		}
		else if (mapData[y + 1][x - 1] == SQUARE_NONE) {
			px -= 1;
		}
	}
	else if ((px + PLAYER_SIZE) / SQUARES_SIZE == x + 1) {
		if (mapData[y][x + 1] != SQUARE_NONE) {
			if (mapData[y + 1][x] == SQUARE_NONE) {
				px -= 1;
			}
		}
		else {
			py -= 1;
		}
	}
	else {
		py -= 1;
	}
}

// ��
void DownHitWall(int x, int y) {
	if (mapData[y][x] != SQUARE_NONE) {
		if (mapData[y - 1][x + 1] == SQUARE_NONE) {
			px += 1;
		}
		else if (mapData[y - 1][x - 1] == SQUARE_NONE) {
			px -= 1;
		}
	}
	else if ((px + PLAYER_SIZE) / SQUARES_SIZE == x + 1) {
		if (mapData[y][x + 1] != SQUARE_NONE) {
			if (mapData[y - 1][x] == SQUARE_NONE) {
				px -= 1;
			}
		}
		else {
			py += 1;
		}
	}
	else {
		py += 1;
	}
}
#pragma endregion