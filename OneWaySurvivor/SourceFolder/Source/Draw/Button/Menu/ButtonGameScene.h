#pragma once
#include"../ButtonBase.h"

class c_ButtonGameScene:public C_ButtonBase
{
public:
	c_ButtonGameScene();

	// �X�V����
	bool Update(const D3DXVECTOR2 *Pos);

	bool GetDrawChangeFlg(void) { return DrawChangeFlg; }
	virtual void SetDrawChangeFlg(const bool Flg) { DrawChangeFlg = Flg; }

	// �^�b�`�������Ɏ��̓����̔ԍ��n��
	int GetNextNo(void) { return nextNo; }
protected:

	int nextNo;

	D3DXVECTOR2 transPos;  // ��{�̈ʒu�ƈړ��̈ʒu�Ɗg�kx,y

	bool DrawChangeFlg;  // �\���ύXFlg
};