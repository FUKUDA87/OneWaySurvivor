#pragma once
#include<d3dx9.h>
#include"../../2D/TextDraw2DBase.h"
#include"../../Num/2D/Num2DBase.h"
#include"../2D/ArrowsButton.h"

class C_SoundVolumeChange
{
public:
	C_SoundVolumeChange(const bool BGMVolumeFlg,const D3DXVECTOR2 *Pos,const int *Volume);
	~C_SoundVolumeChange();

	// çXêVèàóù
	bool Update(const bool *KeyFlg, int *Volume);

	// ï\é¶
	void Draw2D(void);

private:
	C_ArrowsButton *arrows;
	c_Num2DBase *num;
	C_TextDraw2DBase *text;

	int volume;

	D3DXVECTOR2 pos, transNum, transText;
};