#pragma once
#include"Draw3D_Base2.h"
#include<string>
#include"../../Manager/TextureManager/DrawTextureManager_Base.h"


//板ポリゴンの表示
class C_Draw_Pol_BASE_A :public C_Draw3D_Base2 {
public:
	C_Draw_Pol_BASE_A();
	C_Draw_Pol_BASE_A(const D3DXVECTOR3 *Pos_A, const D3DXVECTOR3 *Pos_B, const D3DXVECTOR3 *Pos_C, const D3DXVECTOR3 *Pos_D);
	C_Draw_Pol_BASE_A(std::string FileName, const S_TEX_POS *Pos);
	C_Draw_Pol_BASE_A(std::string FileName, const S_TEX_DRAW_DATA* Data);

	//表示関数
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos);

	//移動量のセット
	void Set_MoveVec(const D3DXVECTOR3 *MoveVec);


	//メッシュ渡し
	LPD3DXMESH Get_Mesh(void);

	//ポリゴンの頂点渡し
	D3DXVECTOR3 Get_Pol_Pos(const int *PosNo);

	//表示行列の渡し
	D3DXMATRIX Get_DrawMat(void);

protected:

	/*メンバー変数*/
	//表示のテクスチャ
	TEXTURE M_Tex;
	VERTEX v[4];
	D3DXVECTOR3 v_Pos[4];

	/*便利メンバー関数*/

	//テクスチャのロード
	void Texture_Load(std::string FileName, const S_TEX_POS *Pos);
	//テクスチャのロードと色の削除
	void Texture_Load(std::string FileName, const S_TEX_DRAW_DATA* Data);
	//テクスチャの情報渡し
	TEXTURE Get_S_Texture(void) {
		return M_Tex;
	}

	//板ポリゴンの頂点セット
	void Pol_SetPos(const D3DXVECTOR3* v_A, const D3DXVECTOR3* v_B, const D3DXVECTOR3* v_C, const D3DXVECTOR3* v_D);

	//板ポリゴンの透明度の入れ
	void Pol_SetAllColor(const int *Alpha);

	//テクスチャ座標の操作
	void Pol_SetAllTex(const D3DXVECTOR2* t_A, const D3DXVECTOR2* t_B, const D3DXVECTOR2* t_C, const D3DXVECTOR2* t_D);

	//初期化
	void Init_Pol(void);


	//テクスチャなしの表示
	void Draw_Pol_No1(void);

	//テクスチャありの表示
	void Draw_Pol_No2(void);

private:
	
};