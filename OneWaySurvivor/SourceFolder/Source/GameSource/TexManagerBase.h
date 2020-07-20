#pragma once
#include"Struct.h"
#include<stdio.h>
#include"Const.h"

//１つのテクスチャ
class C_TexManagerBase {
public:
	//モデル情報渡し
	virtual LPDIRECT3DTEXTURE9 GetTex(int MeshNo) = 0;
protected:
	//モデル情報探し
	//virtual bool GetMeshJudg(int MeshNo) = 0;
};