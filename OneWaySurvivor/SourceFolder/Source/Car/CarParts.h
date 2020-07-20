#pragma once
#include"Parts/PartsBase.h"
#include<vector>
#include"../Car/Data/BaseDataManager/CarDataManager.h"
#include"../GameSource/Judgment.h"
#include"Parts/Car_Parts_Joint.h"
#include"../Const/Const_PartsTypeNo.h"
#include"../GameSource/StructClass/Parts_Set_Data.h"
#include"CarEffect.h"
#include"../GameSource/StructClass/Parts_Set_Size.h"

class C_CarParts:public C_CarEffect {
public:
	C_CarParts();
	~C_CarParts();

	BODYDATA Get_BODYDATA(void) { return BodyData; }

	//カメラに行列渡し
	D3DXMATRIX Get_Camera_Mat(void);

	// 球判定
	void BallJudgParst(BULLETJUDGDATA * BJD, const D3DXVECTOR3 *Pos, const int *CarType, const unsigned int *cc, const D3DXVECTOR3 *Ray, const float *Rad);

	//パーツのHpを減らす処理
	bool Damage_CarParts(const unsigned int *M_CarPartsNo, const int *Damage);

	// レイ判定
	void RayJudg(BULLETJUDGDATA * BJD, const unsigned int *cc, const RAYDATA * RD, const float * Rad);

protected:
	//パーツ表示変数
	std::vector<C_Car_Parts_Joint*>carParts;

	//車のパーツ情報上書きFlg
	bool M_Parts_Save_Flg;

	//パーツの初期化
	virtual void New_Set_Car_Parts(const BODYDATA *CarData);
	virtual void New_Set_Car_Parts(const int *CarNo,std::vector<C_Parts_Set_Data*>M_Set_Data);

	//パーツの全削除
	void Delete_ALL_Parts(void);

	//パーツの初期化(プレイヤー)
	void New_CarParts(const BODYDATA *CarData);
	void New_CarParts(std::vector<C_Parts_Set_Data*>M_Set_Data);
	S_CAR_PARTS_DATA* Get_Data_CarParts(const int *TypeNo,const int JointNo);
	//パーツの初期化(エネミー)

	//車のパーツの情報入手
	void New_Car_Parts_Data(const int *CarNo);

	//車の当たり判定用の情報の初期化
	virtual void New_Car_Judg_Parts(void);


	//車のパーツのサイズの新規検索項目の作成
	void NewCarPartsSize(const int TypeNo, const int JointNo, const D3DXVECTOR3* ScalPos);
	void NewCarPartsSize(const int TypeNo, const int JointNo, const float Size);

	//車のパーツのサイズの情報の検索
	D3DXVECTOR3 GetCarPartsSize(const S_PARTS_SET_DATA_No* No);

	//車のパーツのサイズ情報の作成
	S_PARTS_SET_DATA_No GetDataNo(const int TypeNo, const int JointNo);

	std::vector<S_CAR_PARTS_DATA*>M_CarPartsData;  // 車のパーツ位置情報

	// 車のパーツ位置情報削除
	void DeleteCarPartsData(void);

	// レイ判定
	void RayJudgParts(BULLETJUDGDATA * BJD, const D3DXVECTOR3 *Pos, const int *CarType, const unsigned int *cc, const D3DXVECTOR3 *Ray);


	//パーツの表示
	void Draw_Car_Parts(const D3DXVECTOR3* CameraPos);
	//パーツの更新
	bool Update_Car_Parts(void);
	//パーツの情報渡し

	//パーツの削除
	void Delete_Parts(unsigned int *PartsNo);

	//パーツにダメージ

private:

	//車のパーツ位置情報入手
	void SetCarPartsData(const S_CAR_PARTS_DATA *Data);

	//車のパーツ位置の情報
	S_CAR_PARTS_DATA GetCarPartsData(const unsigned int *PartsNo);

	// 車のパーツ位置情報数渡し
	unsigned int GetCarPartsDataNum(void) {
		return M_CarPartsData.size();
	}

	std::vector<C_Parts_Set_Size*>M_CarPartsSize;  // 車のパーツのサイズをいじる変数

	//車のパーツのサイズ情報の削除
	void DeleteCarPartsSize(void);

};