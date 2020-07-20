#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"

#ifndef Cmouse_H
#define Cmouse_H


class C_Mouse{
public:
	void Init();
	C_Mouse();
	C_Mouse(bool InitPosFlg);
	~C_Mouse();
	bool Update();
	bool CamUpdate(float *AngX, float *AngY, float sen,int revUD,int revLR,bool IncFlg);
	void ChaDrawFlg(bool Flg);
	//指にする関数
	void SetTouchFlg();
	D3DXVECTOR2 GetPt();
	void Draw2D();
protected:

private:
	POINT BasePt;
	bool DrawFlg, TouchFlg;
	void ChaFlg(bool mouseFlg);
	CHARA2D Hand;//手カーソル用
};

#endif // !Cmouse_H
