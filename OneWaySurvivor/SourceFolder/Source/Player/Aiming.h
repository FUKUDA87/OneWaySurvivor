#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"

#ifndef Aiming_H
#define Aiming_H


class Aiming {
private:
	CHARA2D aim;
	CHARA2D aimR;
public:
	void Init();
	Aiming();
	~Aiming();
	void Draw();
	void ChaFlg(void);
	void ResFlg(void);
};

#endif // !Aiming_H