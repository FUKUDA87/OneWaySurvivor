#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"../../Const/Const_Draw_Judg.h"

class C_Draw3D_Base2 {
public:
	C_Draw3D_Base2();

	//表示関数
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos)=0;
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos,bool *Body_DamageFlg);

	//移動量のセット
	virtual void Set_MoveVec(const D3DXVECTOR3 *MoveVec) = 0;

	//更新処理
	virtual bool Update(void);

	//拡大と縮小の直し(掛け算)
	void Set_ScalPos_Update(const D3DXVECTOR3 *set_ScalPos);

	//行列渡し
	D3DXMATRIX Get_Mat(void) {
		return M_Mat;
	}

	//行列のセット
	virtual void Set_Mat(const D3DXMATRIX*Mat) {
		M_Mat = *Mat;
	}

	//拡大と縮小の渡し
	D3DXVECTOR3 Get_ScalPos(void) {
		return M_ScalPos;
	}

	//表示行列の渡し
	virtual D3DXMATRIX Get_DrawMat(void);

	//メッシュの判定渡し
	int Get_Draw_JudgFlg(void) {
		return Draw_JudgFlg;
	}

	//メッシュ渡し
	virtual LPD3DXMESH Get_Mesh(void)=0;
	
	//ポリゴンの頂点渡し
	virtual D3DXVECTOR3 Get_Pol_Pos(const int *PosNo) = 0;

	//全体のサイズ渡し
	D3DXVECTOR3 Get_ScalPos_Body(void) {
		return M_ScalPos_Body;
	}

	bool Get_IdenFlg(void) {
		return IdenFlg;
	}

	//円の半径渡し
	virtual float Get_Dis(void) {
		return 0.0f;
	}

protected:
	//表示用行列
	D3DXMATRIX M_Mat;
	D3DXVECTOR3 M_ScalPos,M_ScalPos_Init,M_ScalPos_Body;//_Initは初期化時の変化用変数_Bodyは全体の拡大行列

	//MoveVecを足す時に最初だけ足さないFlg
	bool MoveVecFlg;

	//表示にアイデンティティを使用しているか
	bool IdenFlg;

	/*メンバー関数*/

	//MoveVecFlgの判定
	bool Get_MoveVecFlg(void);

	//行列の代入(1)
	void Base_Set_Mat_No1(const D3DXMATRIX *Mat) {
		M_Mat = *Mat;
	}

	//単位行列の作成
	D3DXMATRIX Get_IdenMat(void);

	//
	void Base_Set_MoveVec(const D3DXVECTOR3 *MoveVec);

	//拡大と縮小の直し
	void Set_ScalPos_Init(const D3DXVECTOR3 *set_ScalPos);

	int Draw_JudgFlg;//判定物の確認用

	//サイズの作成
	D3DXVECTOR3 Get_SizeVec(const float *Size);

private:
	//初期化
	void Init(void);
};