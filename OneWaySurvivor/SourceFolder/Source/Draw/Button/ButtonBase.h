#pragma once
#include<d3dx9.h>
#include<vector>
#include"Button2D.h"

class C_ButtonBase
{
public:
	~C_ButtonBase();

	// �\��
	virtual void Draw2D(void);

	// �X�V����
	virtual bool Update(const D3DXVECTOR2 *Pos);

	// �^�b�`����
	virtual bool TouchJudg(void);

protected:
	std::vector<C_Button2D*>button2D;

	D3DXVECTOR2 pos;  // �ʒu


	void Delete(void);
};