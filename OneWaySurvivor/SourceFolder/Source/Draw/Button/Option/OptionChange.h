#pragma once
#include<d3dx9.h>
#include"../ButtonBase.h"
#include"OptionChangeWindow.h"

class C_OptionChange
{
public:
	C_OptionChange(const int *BGMVolume, const int *SEVolume);
	~C_OptionChange();

	// �\��
	void Draw2D(void);

	// �X�V����
	bool Update(const bool *KeyFlg, int *BGMVolume, int *SEVolume);

private:
	C_ButtonBase *button;

	C_OptionChangeWindow *changeWindow;

	bool modeChangeFlg;


};