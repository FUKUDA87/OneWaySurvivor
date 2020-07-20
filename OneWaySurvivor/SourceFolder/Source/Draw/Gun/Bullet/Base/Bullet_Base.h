#pragma once
#include<d3dx9.h>
#include"../../../../GameSource/Struct.h"
#include"../../../DrawBase2/Draw3D_Base2.h"
#include<vector>
#include"../../../../GameSource/Count/Count.h"

class C_Bullet_Base{
public:
	//弾の番号と銃口の行列
	C_Bullet_Base(const D3DXMATRIX *Mat);
	//プレイヤーが照準を合わせた時のコンストラクタ
	C_Bullet_Base(const D3DXMATRIX *Mat, const S_RayHitJudgData* RayData);
	~C_Bullet_Base();

	//表示
	virtual void Draw(const D3DXVECTOR3 *CameraPos);

	//発砲者の移動Vec加算
	virtual void MoveVec(const D3DXVECTOR3 *MoveVec);

	//構造体渡し
	S_BULLET Get_S_BULLET(void) {
		return M_S_Bullet;
	}

	//弾の情報の取得
	void Set_S_BULLET(const int *BulletTypeNo);

	//表示の構造体渡し
	BASE3D Get_BASE3D(void) {
		return M_Base;
	}

	//表示の構造体の代入
	void Set_BASE3D(const BASE3D *s_Base) {
		M_Base = *s_Base;
	}

	//行列入れ
	void Set_Mat(const D3DXMATRIX *Mat);

	//前進
	bool Move(void);

	//地面と壁の判定渡し
	bool Get_GroWal_Judg_Flg(void) {
		return M_GroWal_Judg_Flg;
	}

	//地面と壁の判定の入れ
	void Set_GroWal_Jufg_Flg(const bool *Flg) {
		M_GroWal_Judg_Flg = *Flg;
	}
protected:
	//カウントダウンの削除
	void Delete_Count(void);

	/*変数*/
	S_BULLET M_S_Bullet;

	//表示クラス
	std::vector<C_Draw3D_Base2*>M_Draw;
	//移動行列
	BASE3D M_Base;

	/*弾の初期化に使用*/
	S_PolMat_INIT Get_Init_S_PolMat_INIT(const D3DXMATRIX *Mat, const int TexNo, const int PolNum, const float PolSize);

	S_TEX_POS Get_Tex_Pos(const int W, const int H);
private:

	void Init_S_Bullet(void);

	//地面と壁を判定するFlg
	bool M_GroWal_Judg_Flg;

	//表示の全削除
	void M_Draw_Delete_All(void);

	//弾を照準の方向に傾ける処理
	void RayPos_Bullet(const S_RayHitJudgData* RayData);

	//初期化
	void Init(void);

	C_Count *M_Count;
};