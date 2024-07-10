#include "game.h"

int bx[], by[];  // �u���b�N�̈ʒu�p
int blockCnt;    // �u���b�N�̐�
int clearCnt;    // �N���A�����邽�߂̃J�E���^�[

// �u���b�N����
void BlockGenerate() {
    int rndX = 0, rndY = 0;
    int x = 0, y = 0;

    // ���W�擾
    if (blockCnt < BLOCK_MAX) {
        //X��Y�̍��W�擾
        while (bx[blockCnt] == 0 || by[blockCnt] == 0) {
            //�����_���Ɏ擾
            rndX = GetRand(SQUARES_SIZE * 15 + 1);
            rndY = GetRand(SQUARES_SIZE * 13 + 1);

            // �}�X�ڂɎ��܂�Ƃ��̂ݔ�肪�Ȃ����`�F�b�N����i���܂�Ȃ��������͂܂���蒼���j
            if ((rndX % SQUARES_SIZE == 0 && rndY % SQUARES_SIZE == 0) && mapData[rndY / SQUARES_SIZE][rndX / SQUARES_SIZE] == SQUARE_NONE) {
                // ����Ă����蒼���B��肪�Ȃ������烋�[�v���甲���J�E���g�𑝂₵�摜��������
                if (BlockCheck(rndX, rndY) == true) {
                    // �v���C���[�Ɠ����ꏊ�ɂ͂Ȃ�Ȃ��悤�ɂ���
                    if (rndX == px && rndY == py) {
                        continue;
                    }
                    bx[blockCnt] = rndX;
                    by[blockCnt] = rndY;
                    break;
                }
                else {
                    continue;
                }
            }
        }

        //�}�b�v�f�[�^�ύX
        x = bx[blockCnt] / SQUARES_SIZE;
        y = by[blockCnt] / SQUARES_SIZE;
        mapData[y][x] = SQUARE_BLOCK;

        // �J�E���g�𑝂₷
        blockCnt++;
        clearCnt++;
    }
}

// �u���b�N���_�u���ĂȂ����`�F�b�N
bool BlockCheck(int rx, int ry) {
    // �ŏ��̃u���b�N�̏ꍇ�͂��̂܂�true��Ԃ�
    // 2�ڈȍ~��for���[�v�Ŕ�肪�Ȃ������ה���Ă���false��Ԃ�
    if (blockCnt > 0) {
        for (int i = 0; i < blockCnt; i++) {
            // ����Ă���
            if (bx[i] == rx && by[i] == ry) {
                return false;
            }
            // ����ĂȂ�������
            else if (i == blockCnt - 1) {
                return true;
            }
        }
    }
    else {
        return true;
    }
    return false;
}

// �����Ɋ������܂ꂽ�u���b�N����������
void DestroyBlocks() {
    for (int i = 0; i < blockCnt; i++) {
        if ((bx[i] == BombX && by[i] == BombY) ||
            (bx[i] == BombX - SQUARES_SIZE && by[i] == BombY) ||
            (bx[i] == BombX - SQUARES_SIZE * 2 && by[i] == BombY) ||
            (bx[i] == BombX + SQUARES_SIZE && by[i] == BombY) ||
            (bx[i] == BombX + SQUARES_SIZE * 2 && by[i] == BombY) ||
            (bx[i] == BombX && by[i] == BombY - SQUARES_SIZE) ||
            (bx[i] == BombX && by[i] == BombY - SQUARES_SIZE * 2) ||
            (bx[i] == BombX && by[i] == BombY + SQUARES_SIZE) ||
            (bx[i] == BombX && by[i] == BombY + SQUARES_SIZE * 2)) {

            // �u���b�N�������A�}�b�v�f�[�^�������Ȃ���Ԃɂ���
            int y = by[i] / SQUARES_SIZE;
            int x = bx[i] / SQUARES_SIZE;

            if (BombX < bx[i]) {
                if (mapData[y][x - 1] != SQUARE_WALL) {
                    mapData[y][x] = SQUARE_NONE;
                    bx[i] = 0;
                    by[i] = 0;
                    clearCnt--;
                    if (bombCount < BLOCK_MAX) {
                        score += 10;
                    }
                }
            }
            else if (BombX > bx[i]) {
                if (mapData[y][x + 1] != SQUARE_WALL) {
                    mapData[y][x] = SQUARE_NONE;
                    bx[i] = 0;
                    by[i] = 0;
                    clearCnt--;
                    if (bombCount < BLOCK_MAX) {
                        score += 10;
                    }
                }
            }
            else if (BombY < by[i]) {
                if (mapData[y - 1][x] != SQUARE_WALL) {
                    mapData[y][x] = SQUARE_NONE;
                    bx[i] = 0;
                    by[i] = 0;
                    clearCnt--;
                    if (bombCount < BLOCK_MAX) {
                        score += 10;
                    }
                }
            }
            else if (BombY > by[i]) {
                if (mapData[y + 1][x] != SQUARE_WALL) {
                    mapData[y][x] = SQUARE_NONE;
                    bx[i] = 0;
                    by[i] = 0;
                    clearCnt--;
                    if (bombCount < BLOCK_MAX) {
                        score += 10;
                    }
                }
            }
        }
    }
}
