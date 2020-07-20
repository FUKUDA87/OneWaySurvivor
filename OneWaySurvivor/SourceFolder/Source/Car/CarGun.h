#pragma once
#include"CarParts.h"
#include"../Draw/Gun/Draw/NewGun/GunLaser.h"
#include"../Draw/Gun/Draw/Move/GunMoveBase_A.h"

class C_CarGun :public C_CarParts {
public:
	~C_CarGun();

	//銃が発射する弾の変更
	void Set_Gun_Bullet_No(const unsigned int *M_GunNo, const int *BulletNo);

	//銃の引き金操作
	void Set_Gun_Trigger(const unsigned int *GunNo, const bool *TriggerFlg);

	//銃の数渡し
	unsigned int Get_Gun_Num(void) { return gun.size(); }

	//表示の銃の情報渡し
	S_GUN_DATA Get_Gun_Data(const unsigned int *DarwGunNo);

	//レイの判定入れ
	void Set_Ray_Hit_Flg(const unsigned int *DrawGunNo, const bool *Flg) { gun[*DrawGunNo]->Set_Ray_Hit_Flg(Flg); }
	
	//レーザーの長さ入れ
	void Set_Ray_Dis(const unsigned int *M_GunNo, const float *Dis);

	// レイ判定
	void RayJudg(BULLETJUDGDATA * BJD, const unsigned int *cc, const RAYDATA * RD, const float * Rad);

	//銃のHpを減らす処理
	bool Damage_Gun(const unsigned int *M_GunNo, const int *Damage);

protected:
	//全ての銃の削除
	void AllDelete_Gun(void);

	//銃の動きを渡す
	virtual C_GunMoveBase_A *Get_GunMove(const int *MoveNo);

	//銃の動きをプレイヤーの操作にする。
	virtual void Set_GunMove_Player(const unsigned int *GunNo);

	std::vector<C_GunLaser*>gun;

	//パーツの初期化
	void New_Set_Car_Parts(const BODYDATA *CarData);
	void New_Set_Car_Parts(const int *CarNo, std::vector<C_Parts_Set_Data*>M_Set_Data);

	//銃のくっつけ
	virtual void New_Car_Parts_Gun(const BODYDATA *CarData);
	virtual void New_Car_Parts_Gun(std::vector<C_Parts_Set_Data*>M_Set_Data);

	// レイ判定
	void RayJudgGun(BULLETJUDGDATA * BJD, const D3DXVECTOR3 *Pos, const int *CarType, const unsigned int *cc, const D3DXVECTOR3 *Ray);


	//表示
	void Draw_Gun(const D3DXVECTOR3 *CameraPos);
	//更新
	void Update_Gun(void);

	//スタンドとジョイントの行列
	D3DXMATRIX Get_Joint_Mat(void);
	D3DXMATRIX Get_Joint_Mat(const int *JointNo);

	/*
	当たり判定
	*/
	//表示パーツ数渡し
	unsigned int Get_Gun_Draw_Parts_Num(const unsigned int *M_GunNo) {
		return gun[*M_GunNo]->Get_Draw_Parts_Num();
	}

	//ポリゴンFlg
	int Get_Gun_Draw_Parts_Draw_JudgFlg(const unsigned int *M_GunNo, const unsigned int *PartsNo);

	//ポリゴンの頂点渡し
	D3DXVECTOR3 Get_Gun_Draw_Parts_Pol_Pos(const unsigned int *M_GunNo, const unsigned int *PartsNo, const int *PolNo);

	//メッシュ渡し
	LPD3DXMESH Get_Gun_Draw_Parts_Mesh(const unsigned int *M_GunNo, const unsigned int *PartsNo);

	//単位行列の確認
	bool Get_Gun_Draw_Parts_Iden_Flg(const unsigned int *M_GunNo, const unsigned int *PartsNo);

	//表示の行列渡し
	D3DXMATRIX Get_Gun_Draw_Parts_Draw_Mat(const unsigned int *M_GunNo, const unsigned int *PartsNo);

	//銃にレイを飛ばしていいかの確認
	bool Ray_Judg_Gun_Flg(const unsigned int *M_GunNo);



private:

	/*関数*/

	//銃の削除
	void Delete_Gun(unsigned int *GunNo);

	//銃の番号が存在するか判定
	bool Judg_GunNo(const unsigned int *GunNo);
};