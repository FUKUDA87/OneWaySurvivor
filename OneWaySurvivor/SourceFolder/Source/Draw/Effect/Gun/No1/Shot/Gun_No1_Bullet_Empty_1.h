#pragma once
#include"Gun_No1_Shot_Effect.h"
#include"../../../../../Draw/DrawBase2/Draw_Mesh_Base_A.h"
#include"../../../../../GameSource/Count/Count.h"

class C_Gun_No1_Bullet_Enpty :public C_Draw_Mesh_Base {
public:
	C_Gun_No1_Bullet_Enpty(const D3DXMATRIX *GunMat);
	~C_Gun_No1_Bullet_Enpty();

	//表示関数
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos);

	//移動量のセット
	virtual void Set_MoveVec(const D3DXVECTOR3 *MoveVec);

	bool Update(void);
protected:
	//移動ベクトル
	D3DXVECTOR3 M_MoveVec;
	//yの減らす量
	float yDown;

	C_Count *M_Count;

	//初期化
	void Init_Bullet(void);

private:

};