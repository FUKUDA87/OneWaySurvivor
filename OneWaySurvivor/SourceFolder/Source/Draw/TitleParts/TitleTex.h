#pragma once
#include<d3dx9.h>
#include"../../GameSource/Const.h"
#include"../../GameSource/Struct.h"

class TitleTex {
private:
protected:
	CHARA2D title[1];
public:
	TitleTex();
	~TitleTex();
	void Draw();
};