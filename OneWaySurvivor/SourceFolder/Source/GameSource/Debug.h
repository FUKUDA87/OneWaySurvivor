#pragma once
#include<d3dx9.h>
#include<stdio.h>
#include"Struct.h"
#include"../Key/Key.h"

#ifndef Debug_H
#define Debug_H

class Debug {
public:
	Debug();
	~Debug() {};
	bool ChangeMode();//デバッグの切り替え
	bool Update();
	bool KeyUpdate();
	void Draw();
	bool GetDebug() { return debugFlg; };
	D3DXMATRIX GetDebugMat();
	void SetDebugMat(D3DXMATRIX mat);
	void SetNum(int i) { num = i; };
	int GetNum() { return num; };
	//float
	void SetFlo(float f) { fl = f; };
private:
	bool debugFlg;
	bool UpFlg, DownFlg, LeftFlg, RightFlg;
	BASE3D debug;

	//表示用
	int cnt;
	D3DXMATRIX Mat;
	//個体
	int num;
	float fl;
	//キー
	Key key;
};

#endif //!Debug_H


/*グローバルで宣言
#include"h+cpp/Debug.h"
Debug *debug;
*/
/*cppで宣言
#include"Debug.h"

extern Debug *debug;
*/