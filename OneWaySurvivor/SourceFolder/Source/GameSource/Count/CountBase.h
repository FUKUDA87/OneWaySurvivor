#pragma once
#include<d3dx9.h>

class C_CountBase
{
public:
	C_CountBase(const int StartNum);

	// �X�V����(�J�E���g�I�������false)
	bool Update(void);

	// ���̃J�E���g����
	void setNowCount(const int NewCount) { nowCount = NewCount; }

	// ���̃J�E���g�n��
	int getNowCount(void) { return nowCount; }
private:
	int nowCount;
};