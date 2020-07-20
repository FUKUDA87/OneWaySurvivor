#pragma once
#include<d3dx9.h>
#include"../GameSource/Const.h"
#include"../GameSource/Struct.h"
#include<stdio.h>

class C_PlayerBody {
public:
	C_PlayerBody();
	~C_PlayerBody();

	//ì¬
	void Save(void);
	void Save2(void);


	//“ü‚ê
	void SetPData(const BODYDATA* Data);

	//“n‚µ
	BODYDATA GetPData(void) {
		return pData;
	}
protected:

private:
	//Ô‘Ìî•ñ
	BODYDATA pData;

	FILE* fp;
	FILE *fp_b;
};