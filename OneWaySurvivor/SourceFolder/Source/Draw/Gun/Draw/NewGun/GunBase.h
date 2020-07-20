#pragma once
#include<d3dx9.h>
#include"../../../../GameSource/Struct.h"
#include"../../../../GameSource/CharaBase.h"
#include"../Move/GunMoveBase_A.h"
#include"../Parts/GunPartsDraw.h"
#include"../Parts/Gun_Parts_Category.h"
#include"../Trigger/Gun_Trigger_Base.h"
#include<vector>

class C_GunBase:public C_CharaBase {
public:
	C_GunBase();
	~C_GunBase();

	//更新処理
	bool Update(S_GUN_UPDATE_DATA* s_Update);

	//表示処理
	virtual void Draw(const D3DXVECTOR3* CameraPos);

	//銃の動き渡し
	S_GUN_DATA Get_S_GUN_DATA(void) {
		return M_S_GunData;
	}

	//銃の動きのコンストラクタ
	void New_GunMove(C_GunMoveBase_A *s_GunMove);

	//銃口数渡し
	int Get_GunMouth_Num(void);

	//銃口渡し
	D3DXMATRIX Get_GunMouth_Mat(const unsigned int *MouthNo);

	//引き金の更新
	bool Update_Trigger(const bool *TriggerFlg);

	//銃口のチェンジ
	bool Gun_Mouth_Change(void);

	//レイの判定入れ
	void Set_Ray_Hit_Flg(const bool *Flg) {
		M_S_GunData.Ray_Hit_Flg = *Flg;
	}

	//発射数のリセット
	void Init_Departure_Num(void);

	//銃の表示のサイズ変更
	void Set_ScalPos(const D3DXVECTOR3* s_ScalPos);

	/*
	当たり判定
	*/
	//表示パーツ数渡し
	unsigned int Get_Draw_Parts_Num(void) {
		return M_GunParts.size();
	}

	//ポリゴンFlg
	int Get_Draw_Parts_Draw_JudgFlg(const unsigned int *PartsNo);

	//ポリゴンの頂点渡し
	D3DXVECTOR3 Get_Draw_Parts_Pol_Pos(const unsigned int *PartsNo, const int *PolNo);

	//メッシュ渡し
	LPD3DXMESH Get_Draw_Parts_Mesh(const unsigned int *PartsNo);

	//単位行列の確認
	bool Get_Draw_Parts_Iden_Flg(const unsigned int *PartsNo);

	//表示の行列渡し
	D3DXMATRIX Get_Draw_Parts_Draw_Mat(const unsigned int *PartsNo);

protected:
	/*変数*/

	//銃の動きの変数
	C_GunMoveBase_A *M_GunMove;

	//銃の情報の変数
	S_GUN_DATA M_S_GunData;

	//銃の表示パーツ
	std::vector<C_PartsDraw_Gun*>M_GunParts;

	//銃のカテゴリー
	std::vector<C_Gun_Parts_Category*>M_Category_Data;

	//引き金
	C_Gun_Trigger_Base* M_C_Trigger;

	//表示の処理
	virtual void Draw_Gun(const D3DXVECTOR3* CameraPos);

private:

	//銃の動きの削除
	void Delete_GunMove(void);

	//銃のパーツの表示
	void Draw_GunParts(const D3DXVECTOR3 *CameraPos);

	//レートの確認の関数
	void Judg_Rate(void);
};