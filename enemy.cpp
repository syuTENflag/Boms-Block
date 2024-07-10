#include "game.h"
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <thread>

#pragma region �O���ϐ��Ăяo��
int ex, ey;			// �G�̈ʒu
#pragma endregion


// �G�̏������W
int enemyX = 480;
int enemyY = 416;

int MoveCount = 0;


void UpdateEnemy() {
    // �v���C���[�ƓG�̃O���b�h���W���v�Z
    int enemyGridX = enemyX / SQUARES_SIZE;
    int enemyGridY = enemyY / SQUARES_SIZE;
    int playerGridX = px / SQUARES_SIZE;
    int playerGridY = py / SQUARES_SIZE;

    // �G���v���C���[������̃}���n�b�^�������ȏ㗣��Ă���ꍇ�A�����_���Ɉړ�
    if (abs(playerGridX - enemyGridX) + abs(playerGridY - enemyGridY) >= 2) {
        if (MoveCount >= 30) {
            MoveCount = 0; // ���[�u�J�E���g�̃��Z�b�g
            int randomDirection = rand() % 4; // 0: �E, 1: ��, 2: ��, 3: ��

            switch (randomDirection) {
            case 0: // �E�Ɉړ�
                if (enemyGridX + 1 < STAGE_WIDTH && mapData[enemyGridY][enemyGridX + 1] == SQUARE_NONE) {
                    enemyGridX++;
                }
                break;
            case 1: // ���Ɉړ�
                if (enemyGridX - 1 >= 0 && mapData[enemyGridY][enemyGridX - 1] == SQUARE_NONE) {
                    enemyGridX--;
                }
                break;
            case 2: // ��Ɉړ�
                if (enemyGridY - 1 >= 0 && mapData[enemyGridY - 1][enemyGridX] == SQUARE_NONE) {
                    enemyGridY--;
                }
                break;
            case 3: // ���Ɉړ�
                if (enemyGridY + 1 < STAGE_HEIGHT && mapData[enemyGridY + 1][enemyGridX] == SQUARE_NONE) {
                    enemyGridY++;
                }
                break;
            }
        }
    }
    else {
        // �v���C���[���߂��ɂ���ꍇ�A�ǐՊJ�n
        if (enemyGridX < playerGridX && mapData[enemyGridY][enemyGridX + 1] == SQUARE_NONE) {
            if (MoveCount >= 30) {
                enemyGridX++;
            }
        }
        else if (enemyGridX > playerGridX && mapData[enemyGridY][enemyGridX - 1] == SQUARE_NONE) {
            if (MoveCount >= 30) {
                enemyGridX--;
            }
        }

        if (enemyGridY < playerGridY && mapData[enemyGridY + 1][enemyGridX] == SQUARE_NONE) {
            if (MoveCount >= 30) {
                enemyGridY++;
            }
        }
        else if (enemyGridY > playerGridY && mapData[enemyGridY - 1][enemyGridX] == SQUARE_NONE) {
            if (MoveCount >= 30) {
                enemyGridY--;
            }
        }
    }

    // �ړ���̍��W�����ۂ̃s�N�Z�����W�ɍX�V
    enemyX = enemyGridX * SQUARES_SIZE;
    enemyY = enemyGridY * SQUARES_SIZE;
    MoveCount++;

    // �v���C���[�ƓG�̓����蔻��
    if (enemyX == px && enemyY == py) {
        // �v���C���[�ɐG�ꂽ���̏���
        game_State = GAME_CLEAR;
    }
}

void DrawEnemy() {
    // �G�̕`��
    DrawGraph(enemyX, enemyY, img04[3], TRUE);
}

void RightHitWall_ENEMY(int x, int y) {
    if (mapData[y][x] != SQUARE_NONE) {
        if (mapData[y + 1][x + 1] == SQUARE_NONE) {
            ey += 1;
        }
        else if (mapData[y - 1][x + 1] == SQUARE_NONE) {
            ey -= 1;
        }
    }
    else if ((ey + ENEMY_SIZE) / SQUARES_SIZE == y + 1) {
        if (mapData[y + 1][x] != SQUARE_NONE) {
            if (mapData[y][x + 1] == SQUARE_NONE) {
                ey -= 1;
            }
        }
        else {
            ex += 1;
        }
    }
    else {
        ex += 1;
    }
}

// ��
void LeftHitWall_ENEMY(int x, int y) {
    if (mapData[y][x] != SQUARE_NONE) {
        if (mapData[y + 1][x - 1] == SQUARE_NONE) {
            ey += 1;
        }
        else if (mapData[y - 1][x - 1] == SQUARE_NONE) {
            ey -= 1;
        }
    }
    else if ((ey + ENEMY_SIZE) / SQUARES_SIZE == y + 1) {
        if (mapData[y + 1][x] != SQUARE_NONE) {
            if (mapData[y][x + 1] == SQUARE_NONE) {
                ey -= 1;
            }
        }
        else {
            ex -= 1;
        }
    }
    else {
        ex -= 1;
    }
}

// ��
void UpHitWall_ENEMY(int x, int y) {
    if (mapData[y][x] != SQUARE_NONE) {
        if (mapData[y + 1][x + 1] == SQUARE_NONE) {
            ex += 1;
        }
        else if (mapData[y + 1][x - 1] == SQUARE_NONE) {
            ex -= 1;
        }
    }
    else if ((ex + ENEMY_SIZE) / SQUARES_SIZE == x + 1) {
        if (mapData[y][x + 1] != SQUARE_NONE) {
            if (mapData[y + 1][x] == SQUARE_NONE) {
                ex -= 1;
            }
        }
        else {
            ey -= 1;
        }
    }
    else {
        ey -= 1;
    }
}

// ��
void DownHitWall_ENEMY(int x, int y) {
    if (mapData[y][x] != SQUARE_NONE) {
        if (mapData[y - 1][x + 1] == SQUARE_NONE) {
            ex += 1;
        }
        else if (mapData[y - 1][x - 1] == SQUARE_NONE) {
            ex -= 1;
        }
    }
    else if ((ex + ENEMY_SIZE) / SQUARES_SIZE == x + 1) {
        if (mapData[y][x + 1] != SQUARE_NONE) {
            if (mapData[y - 1][x] == SQUARE_NONE) {
                ex -= 1;
            }
        }
        else {
            ey += 1;
        }
    }
    else {
        ey += 1;
    }
}
