/*
	�^�C�g����ʏ����̃\�[�X
*/
#pragma region main.h�̃C���N���[�h

#include "game.h"

#pragma endregion
void TitleDraw() {
	// �^�C�g�����̃t�H���g�T�C�Y���w�肵�w��̍��W�ɕ`�悷��
	SetFontSize(75);
	DrawFormatString(88, 150, Color_Yellow, "BLOCK PUZZLE");

	// �w���̃t�H���g�T�C�Y���w�肵�w��̍��W�ɕ`�悷��
	SetFontSize(40);
	DrawFormatString(100, 240, Color_Yellow, "PS�R���g���[���[��\n�^�b�`�p�b�h��������\n�@�@�@�X�^�[�g");

	
	if (GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_H) {// �^�b�`�p�b�h
		game_start = GAME_PLAYING;
		
		WaitTimer(100);

		
	}
}