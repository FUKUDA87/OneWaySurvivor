#pragma once
#include<d3dx9.h>
#include<stdio.h>

//ゲーム側の文字表示のクラス
class C_Text_Num {
public:
	//floatの文字表示
	void Draw_Text_float(const float *Num,const D3DXVECTOR2 *Pos);
	//intの文字表示
	void Draw_Text_int(const int *Num, const D3DXVECTOR2 *Pos);
	//charの文字表示
	void Draw_Text_char(const char *Text, const D3DXVECTOR2 *Pos);
};