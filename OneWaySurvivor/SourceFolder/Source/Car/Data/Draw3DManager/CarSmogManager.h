#pragma once
#include"CarMeshManager.h"

class C_CarSmogManager {
public:
	//煙の出現位置
	D3DXMATRIX GetPos(const int *CarNo);
	//煙のアニメーション方法
	S_Smoke GetSmog(const int *CarNo);
private:
	//煙の構造体の初期化
	S_Smoke GetInitSmog(const D3DXVECTOR3 *MoveVec, const D3DXVECTOR3 *Frame, const int Alpha, const int AStart, const int ADown, const float PolSize, const float PolBit, const float PolBitUp, const S_Random *Random);
};