#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"

class c_Wall {
public:
	c_Wall(const bool *PolygonIdenFlg,const bool *LeftFlg,const D3DXMATRIX *Mat
		,const D3DXVECTOR3 *StartPos,const D3DXVECTOR3 *EndPos);

	// 表示
	void Draw3D();

	//壁3Dの行列渡し
	D3DXMATRIX GetMat();

	//壁の情報渡し
	S_Base3D_2 GetData();

	//表示の変更
	void SetDrawFlg(const bool *DrawFlg);

	// 球判定の準備情報
	S_Capsule GetCapsule(void) { return capsule; }

	// カプセル判定
	bool capsuleJudg(float *sd, int *hitNum, const S_Capsule *c);

	// 壁メッシュレイ判定
	bool MeshRayJudg(float *Dis, const D3DXVECTOR3 *Pos, const D3DXVECTOR3 *Ray);

private:
	//壁3D用
	XFILE_B wallMesh;
	XFILE collisionMesh;

	S_Base3D_2 Wall3D;

	S_Capsule capsule;

	//壁のサイズの初期化
	void InitWallSizeZ(const D3DXVECTOR3 * Ground_Vec);

	//壁3Dの表示行列渡し
	D3DXMATRIX GetDrawMat();
};