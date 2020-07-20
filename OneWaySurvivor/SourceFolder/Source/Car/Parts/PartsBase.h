#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"../../GameSource/CharaBase.h"
#include"../../Draw/DrawBase2/Draw3D_Base2.h"
#include<vector>

class C_PartsBase:public C_CharaBase {
public:
	/*車からの距離
	動き

	*/
	C_PartsBase();
	~C_PartsBase();

	//表示
	virtual void Draw_Parts(const D3DXVECTOR3 *CameraPos);
	virtual void Draw_Parts(const D3DXVECTOR3 *CameraPos,const bool *H_Body_DamageFlg);

	//車の拡大行列のセット
	void Set_ScalPos_Body(const D3DXVECTOR3 *set_Car_ScalPos);
	void Set_ScalPos_Body(const D3DXVECTOR3 *set_Car_ScalPos, const D3DXVECTOR3 *set_Parts_ScalPos);

	//表示の行列渡し
	virtual D3DXMATRIX Get_Draw_Mat(void);

	//表示の表示行列渡し
	virtual D3DXMATRIX Get_Draw_DrawMat(void);

	//表示の表示サイズ渡し
	D3DXVECTOR3 Get_Draw_ScalPos(void);


	//表示情報渡し
	BASE3D Get_BASE3D(void) {
		return M_Base3D;
	}

	//スピードセット
	void SetSpeed(const int *GetNowSpeed, const int *GetMaxSpeed);

	//表示のコンストラクタ
	void Draw_New(C_Draw3D_Base2* set_Draw);

	//車のサイズ渡し
	D3DXVECTOR3 Get_Car_ScalPos(void) {
		return M_Car_ScalPos;
	}

	/*
	判定する渡し
	*/
	//ポリゴンFlg
	int Get_Draw_Draw_JudgFlg(void);

	//ポリゴンの頂点
	D3DXVECTOR3 Get_Draw_Pol_Pos(const int *PosNo);

	//メッシュ
	LPD3DXMESH Get_Draw_Mesh(void);

	//IdenFlg
	bool Get_Draw_Iden_Flg(void);

	//表示半径渡し
	float Get_Draw_Dis(void);

protected:
	//表示情報
	BASE3D M_Base3D;

	//車のサイズ
	D3DXVECTOR3 M_Car_ScalPos;

	//表示変数
	C_Draw3D_Base2* M_Draw;

	//スピード(カーの今のスピードと最大スピード)
	S_GAGE Speed;

	//表示の削除
	void Draw_AllDelete(void);

	//表示１
	virtual void Draw_Draw(const D3DXVECTOR3 *CameraPos);
	virtual void Draw_Draw(const D3DXVECTOR3 *CameraPos,const bool *H_Body_DamageFlg);

	void Set_TransPos(const D3DXVECTOR3 *set_Pos);

	//表示の行列全入れ
	void Set_All_Draw_Mat(const D3DXMATRIX *Mat);

	//表示に車のサイズ入れ
	void Set_Body_ScalPos_Draw(void);
	void Set_Body_ScalPos_Draw(const D3DXVECTOR3 *ScalPos);

	//表示と非表示のフラグ
	bool Draw_Flg;
private:

};