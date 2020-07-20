#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include<vector>
#include"../Ground/Ground_Object.h"
#include"../Car/Data/Draw3DManager/CarMeshManager.h"
#include"../GameSource/CharaBase.h"
#include"../GameSource/Const.h"
#include"../GameSource/StructManager.h"

class C_CarBase:public C_CharaBase 
{
public:
	C_CarBase();

	//車体行列渡し
	D3DXMATRIX GetMatCar(void) { return Car.Base.Mat; }

	//車体行列入れ
	void SetMatCar(const D3DXMATRIX *Mat) { Car.Base.Mat = *Mat; }

	//今いる地面のNo入れ
	void SetGroNum(const unsigned int *GroundNo) { Car.Con.GroNum = *GroundNo; }

	//前進アップデート
	virtual bool UpdateCarFM(std::vector<C_Ground_Object*>ground);

	//移動の情報渡し
	CONSTITUTION GetCon(void) { return Car.Con; }

	//今のHp入れ
	virtual bool SetHP(int Damage);
	//今のHp入れ(壁と弾の区別付)
	virtual bool SetHP(int Damage, bool WallFlg);

	//車の存在Flg渡し
	bool GetFlgCar(void) { return Car.Base.Flg; }

	// 横移動の反映
	void SetSideTransMat(const float *MoveX);

	//車情報
	CHARAData GetData(void);

	//移動の情報を渡す
	QuaForMove GetQuaForMove(void);

	//playerのTransMat渡し
	D3DXMATRIX GetTransMatCar(void) { return Car.Base.Trans; }

	//前進判定用関数-----------------------------------------------

	//前進判定用の移動後Mat入れ
	void SetForMoveEndMat(const D3DXMATRIX *Mat) { ForMoveEndMat = *Mat; }

	//前進判定用の移動ベクトル入れ
	void SetForMoveVec(const D3DXVECTOR3 *Vec) { ForMoveVec = *Vec; }
	
	//移動ベクトルの長さ入れ
	void SetQuaVecSize(const float *size) { CarFM.SpeedMulJudg = *size; }

	//前進判定用の移動ベクトル渡し
	D3DXVECTOR3 GetForMoveVec(void) { return ForMoveVec; }

	//前進判定用の移動後Mat渡し
	D3DXMATRIX GetForMoveEndMat(void) { return ForMoveEndMat; }

	//死亡確認(trueで死)
	bool Dead(void);

	//衝突判定することを許可するフラグの渡し
	bool Get_CollisionJudg_TrueFlg(void) { return M_CollisionJudg_TrueFlg; }

	//当たり判定の半径渡し
	float GetBodRadCar(void) { return Car.Base.BodRad; }

	//拡大渡し
	D3DXVECTOR3 GetScalPosCar(void) { return Car.Base.ScaPos; }

	//衝突判定の状態の渡し
	int Get_JudgeType(void) { return M_JudgeType; }

	//前の車の位置のセット
	void SetCarMoveMat(void) { PlaMovMat = Car.Base.Trans*Car.Con.JudgMat; }

	//スピード入れ
	void SetSpeedCar(const D3DXVECTOR3 *spe) { Car.Con.Speed = *spe; }

	// 球判定
	bool BallJudgCar(const D3DXVECTOR3 *Pos, const float *Radius);
	bool BallJudgCar(bool * JudgFlg, float * SmallDis, const D3DXMATRIX * EndMat, const float * Radius);

	//操作・動作できるまでの時間の渡し
	int Get_Move_Stop_Time(void) { return MMove_Stop_Time; }

	//操作・動作できるまでの時間の入れ
	void Set_Move_Stop_Time(const int *Time, const int *Speed);

	//手動と自動の操作情報を入れるクラス
	S_GUN_UPDATE_DATA Get_Gun_Update_Data(void) { return M_S_Gun_Update_Data; }

	// レイ判定
	virtual void RayJudg(BULLETJUDGDATA * BJD, const unsigned int *cc, const RAYDATA * RD, const float * Rad);

	// カプセル判定
	virtual bool capsuleJudg(float *sd, int *hitNum, const S_Capsule *c,const bool *ForMoveJudgFlg);

	// カプセル取得
	S_Capsule GetCapsule(const bool *EndMatFlg);

	D3DXMATRIX getSparkInitMat(const float *MoveVecX,const bool *wallHitFlg);
protected:
	//車のデータ
	BODYDATA BodyData;

	//車のモデル入れ
	void SetMeshCar(int MeshNo);

	//車の情報
	CHARA3D Car;

	QuaForMove CarFM;

	D3DXMATRIX PlaMovMat;//playerの移動前のMat

	//バレット用
	BULLETRAYJUDG brj;

	Judg judg;

	//手動と自動の操作情報を入れるクラス
	S_GUN_UPDATE_DATA M_S_Gun_Update_Data;

	S_Capsule capsule;  // カプセル

	//車の操作者
	int M_Driver;

	//銃の情報の更新
	void Update_Gun_Data(void);

	//操作・動作できるまでの時間を減らす更新の処理
	void Update_Move_Stop_Time(void);

	//銃の動きの停止判定
	bool Get_Stop_Flg(void);

	//衝突判定の状態のセット
	void Set_JudgeType(const int *Type) { M_JudgeType = *Type; }

	// レイ判定
	bool RayJudgCar(const D3DXVECTOR3 *Pos, const D3DXVECTOR3 *Ray, BULLETJUDGDATA * BJD);

	//アップデート
	virtual bool UpdateCar(void);

	//3D表示
	virtual void Draw3DCar(void);

	//パーツの位置調整
	virtual void SetParts(std::vector<C_Ground_Object*>ground);
	
	//車の存在Flg入れ
	void SetFlgCar(const bool *Flg) { Car.Base.Flg = *Flg; }

	//playerのTransMat入れ
	void SetTransMatCar(const D3DXMATRIX *TransMat) { Car.Base.Trans = *TransMat; }

	//スピード入れ
	void SetNowSpeedCar(int spe) { Car.Con.NowSpeed = spe; }

	//弾出現情報入れ
	void SetBPos(D3DXVECTOR3 RayPos, bool RayJudgFlg);

	//無敵アップデート
	bool UpdateCountM(void);

	//矢印作成に必要な情報の取得とアップデート
	virtual void GetPos2DSet(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport) {};

	//移動ベクトル渡し
	D3DXVECTOR3 GetMoveVec(void) { return brj.MoveVec; }

	//カメラの行列のセット
	virtual void Set_CameraMat(const D3DXMATRIX *CameraMat) {
		M_S_Gun_Update_Data.CameraMat = *CameraMat;
	}

	//車の操作者の渡し
	int Get_DriverNo(void) { return M_Driver; }

	/*衝突判定の状態の関数*/

	//衝突判定することを許可するフラグのセット
	void Set_CollisionJudg_TrueFlg(const bool *Flg) { M_CollisionJudg_TrueFlg = *Flg; }

	// 車
	int GetConstCar(void);
private:

	//衝突判定の状態
	int M_JudgeType;

	//操作・動作できるまでの時間
	int MMove_Stop_Time;

	//衝突判定することを許可するフラグ
	bool M_CollisionJudg_TrueFlg;

	//前進クォータニオン用
	D3DXMATRIX ForMoveEndMat;//前進完了時のMat
	D3DXVECTOR3 ForMoveVec;//移動前から移動後のVec
	QuaForMove Q;//前進判定用クォータニオン

	//無敵タイム
	int CountMNum,CountMStart;

	// カプセル初期化
	void capsuleInit(const bool *EndMatFlg);

	//車の表示行列渡し
	virtual D3DXMATRIX GetDrawMatCar(void) {
		return judg.GetDrawMat(&Car.Base.Mat, &Car.Base.Scal, &Car.Base.ScaPos);
	}
};