#pragma once

#pragma region �Q�[�����Ŏg���w�b�_�[�t�@�C���Ȃǂ̒�`
#include "DxLib.h"	// DX���C�u�����̃w�b�_�[
#include <time.h>	// ���Ԋ֌W�̃w�b�_�[
#include <string>	// stringstream ���g�����߂ɃC���|�[�g
#include <sstream>	// ifstream���g�����߂ɃC���|�[�g
#include <fstream>
//#include <stdlib.h>

using namespace std;
#pragma endregion

#pragma region �Q�[�����Ŏg���萔�̒�`
// �Q�[���̏�ԗp�̒萔
#define GAME_INIT 0		// �^�C�g����ʂ̎�
#define GAME_RULE 1
#define GAME_PLAYING 2	// �Q�[���v���C��
#define GAME_CLEAR 3    // �Q�[���N���A��

// �Q�[���v���C�p�̒萔
#define BLOCK_MAX 20	// �u���b�N�̍ő吔
#define SQUARES_SIZE 32	// �}�X�̃T�C�Y
#define PLAYER_SIZE 30	// �v���C���[�̃T�C�Y
#define ENEMY_SIZE 30
#define STAGE_WIDTH 17	// �X�e�[�W�̃}�X�ڂ̐��i���j
#define STAGE_HEIGHT 15	// �X�e�[�W�̃}�X�ڂ̐��i�c�j

// �}�X�̏�ԗp�̒萔
#define SQUARE_NONE 0	// �����Ȃ��}�X�i�v���C���[��������Ƃ���j
#define SQUARE_WALL 1	// ��
#define SQUARE_BLOCK 2	// �u���b�N
#define SQUARE_ENEMY 3  // �G

#pragma region �ȉ��g��Ȃ��萔�i���ׂăR�����g���j

// �R���g���[���[�p�̒萔�i�S��DxLib.h�ɒ�`�ς݂̂��߃R�����g���j
#define PAD_INPUT_DOWN								(0x00000001)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_LEFT								(0x00000002)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_RIGHT								(0x00000004)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_UP								(0x00000008)	// ���`�F�b�N�}�X�N
#define PAD_INPUT_A									(0x00000010)	// �`�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_B									(0x00000020)	// ?�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_C									(0x00000040)	// �Z�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_X									(0x00000080)	// �w�{�^���`�F�b�N�}�X�N
#define PAD_INPUT_Y									(0x00000100)	// ���{�^���`�F�b�N�}�X�N
#define PAD_INPUT_Z									(0x00000200)
#define PAD_INPUT_L									(0x00000400)
#define PAD_INPUT_R									(0x00000800)
#define PAD_INPUT_START								(0x00001000)
#define PAD_INPUT_M									(0x00002000)	//�I�v�V����
#define PAD_INPUT_D									(0x00004000)    //L3
#define PAD_INPUT_F									(0x00008000)    //R3
#define PAD_INPUT_G									(0x00010000)    //�z�[���{�^��
#define PAD_INPUT_H									(0x00020000)    //�^�b�`�p�b�h
#define PAD_INPUT_I									(0x00040000)    //�}�C�N
#define PAD_INPUT_J									(0x00080000)
#define PAD_INPUT_K									(0x00100000)
#define PAD_INPUT_LL								(0x00200000)
#define PAD_INPUT_N									(0x00400000)
#define PAD_INPUT_O									(0x00800000)
#define PAD_INPUT_P									(0x01000000)
#define PAD_INPUT_RR								(0x02000000)
#define PAD_INPUT_S									(0x04000000)
#define PAD_INPUT_T									(0x08000000)
#define PAD_INPUT_U									(0x10000000)
#define PAD_INPUT_V									(0x20000000)
#define PAD_INPUT_W									(0x40000000)

#pragma endregion
#pragma endregion

#pragma region �Q�[�����Ŏg���֐��̒�`
// �Q�[���i�s���ʗp�̊֐�
void GameInit();											// �Q�[���̏������֐�
void LoadCSV();												// CSV�t�@�C����荞�݊֐�
void TitleScene();											// �^�C�g����ʐ���
void RuleScene();                                           // ���[���̐���
void ClearScene();											// �N���A��ʐ���
void DrawScore();											// �X�R�A����
int GetHitKeyStateAll_2(int GetHitKeyStateAll_InputKey[]);	// �L�[���͎��̒l�擾
void InputGetAction();										// �L�[�������̓R���g���[���[�̓��͂ɂ�菈����U�蕪��
void GameLoop();
void ChangeVolumeSoundMem();

// �v���C���[����p�̊֐�
void PlayerRightMove();				// �v���C���[�̈ړ��i�E�j
void PlayerLeftMove();				// �v���C���[�̈ړ��i���j
void PlayerUpMove();				// �v���C���[�̈ړ��i��j
void PlayerDownMove();				// �v���C���[�̈ړ��i���j
void RightHitWall(int x, int y);	// �v���C���[�ƕǂ̓����蔻��i�E�j
void LeftHitWall(int x, int y);		// �v���C���[�ƕǂ̓����蔻��i���j
void UpHitWall(int x, int y);		// �v���C���[�ƕǂ̓����蔻��i��j
void DownHitWall(int x, int y);		// �v���C���[�ƕǂ̓����蔻��i���j

//�G�p�̊֐�
void UpdateEnemy();
void DrawEnemy();
void RightHitWall_ENEMY(int x, int y);
void LeftHitWall_ENEMY(int x, int y);
void UpHitWall_ENEMY(int x, int y);
void DownHitWall_ENEMY(int x, int y);

// �u���b�N�p�̊֐�
void BlockGenerate();				// �u���b�N����
void DestroyBlocks();				// �u���b�N�j��
bool BlockCheck(int rx, int ry);	// �u���b�N�����邩�ǂ����`�F�b�N

// ���e�p�̊֐�
void ArrangementBomb();	// ���e�̔z�u
#pragma endregion

#pragma region �Q�[�����Ŏg���O���ϐ��̒�`
// �Q�[���i�s���ʗp�̊O���ϐ�
extern int game_State;							// �Q�[���̏�Ԃ��`
extern int clearCnt;							// �N���A�����邽�߂̃J�E���^�[
extern int mapData[STAGE_HEIGHT][STAGE_WIDTH];	// �}�b�v�f�[�^��2�����z��Ɋi�[
extern int frameCount;							// �t���[���J�E���g
extern int score;								// �X�R�A
extern bool firstInitFlg;						// ����N�����ǂ����̃t���O

// �L�[���͊֌W�̊O���ϐ�
extern int Key[256];		// �L�[�{�[�h�̓��͓��e��荞��
extern bool spacePressed;	// �X�y�[�X�L�[��������Ă��邩����

// �摜�A���f�ޗp�̊O���ϐ�
extern int img00, img01[16], img02[20], img03[56], img04[24], img05[30];	// �摜���[�h�p�i�v���C���[���j
extern int fnt01[30], fnt03[40];											// �摜���[�h�p�i�t�H���g�j
extern int gamesound;														// �v���C����BGM
extern int titlesound;														// �^�C�g����ʂ�BGM
extern int clearsound;														// �N���A��ʂ�BGM
extern int bombSound;														// �{����u�������ɗ������ʉ�
extern int bombExSound;														// �{�������������Ƃ��ɗ������ʉ�
extern bool imageVisible;													// �摜�������邩�ǂ�������

// �v���C���[�p�̊O���ϐ�
extern int px, py;	// ��l���̈ʒu

// �G�p�̊O���ϐ�
extern int ex, ey;	// �G�̈ʒu

// �u���b�N�p�̊O���ϐ�
extern int bx[BLOCK_MAX], by[BLOCK_MAX];	// �u���b�N�̈ʒu�i��������̂Ŕz��j
extern int blockCnt;						// �u���b�N�̐�

// ���e�p�̊O���ϐ�
extern int bombCount;		// �g�����{���̐����J�E���g
extern int BombX, BombY;	// ���e�̈ʒu
extern bool bombFlg;		// �{����u���Ă��邩�ǂ����̃t���O
#pragma endregion