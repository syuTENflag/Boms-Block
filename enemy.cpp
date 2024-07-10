#include "game.h"
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <thread>

#pragma region 外部変数呼び出し
int ex, ey;			// 敵の位置
#pragma endregion


// 敵の初期座標
int enemyX = 480;
int enemyY = 416;

int MoveCount = 0;


void UpdateEnemy() {
    // プレイヤーと敵のグリッド座標を計算
    int enemyGridX = enemyX / SQUARES_SIZE;
    int enemyGridY = enemyY / SQUARES_SIZE;
    int playerGridX = px / SQUARES_SIZE;
    int playerGridY = py / SQUARES_SIZE;

    // 敵がプレイヤーから一定のマンハッタン距離以上離れている場合、ランダムに移動
    if (abs(playerGridX - enemyGridX) + abs(playerGridY - enemyGridY) >= 2) {
        if (MoveCount >= 30) {
            MoveCount = 0; // ムーブカウントのリセット
            int randomDirection = rand() % 4; // 0: 右, 1: 左, 2: 上, 3: 下

            switch (randomDirection) {
            case 0: // 右に移動
                if (enemyGridX + 1 < STAGE_WIDTH && mapData[enemyGridY][enemyGridX + 1] == SQUARE_NONE) {
                    enemyGridX++;
                }
                break;
            case 1: // 左に移動
                if (enemyGridX - 1 >= 0 && mapData[enemyGridY][enemyGridX - 1] == SQUARE_NONE) {
                    enemyGridX--;
                }
                break;
            case 2: // 上に移動
                if (enemyGridY - 1 >= 0 && mapData[enemyGridY - 1][enemyGridX] == SQUARE_NONE) {
                    enemyGridY--;
                }
                break;
            case 3: // 下に移動
                if (enemyGridY + 1 < STAGE_HEIGHT && mapData[enemyGridY + 1][enemyGridX] == SQUARE_NONE) {
                    enemyGridY++;
                }
                break;
            }
        }
    }
    else {
        // プレイヤーが近くにいる場合、追跡開始
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

    // 移動後の座標を実際のピクセル座標に更新
    enemyX = enemyGridX * SQUARES_SIZE;
    enemyY = enemyGridY * SQUARES_SIZE;
    MoveCount++;

    // プレイヤーと敵の当たり判定
    if (enemyX == px && enemyY == py) {
        // プレイヤーに触れた時の処理
        game_State = GAME_CLEAR;
    }
}

void DrawEnemy() {
    // 敵の描画
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

// 左
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

// 上
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

// 下
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
