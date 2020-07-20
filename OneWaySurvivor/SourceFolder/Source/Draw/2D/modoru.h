#pragma once
#include"Window.h"
#include<d3dx9.h>

class Modoru :public Window {
protected:
	CHARA2D mod;
	D3DXVECTOR2 sizeM;
public:
	Modoru();
	~Modoru() {};
	void Draw2DM();
	bool UpdateM();

	void DrawSu();
	bool UpdateSu();
};