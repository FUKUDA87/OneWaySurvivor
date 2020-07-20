#pragma once
#include"ground.h"
#include"Ground_Object_Parts/Object_Base.h"

class C_Ground_Object :public C_Ground {
public:
	C_Ground_Object(const int *i);
	C_Ground_Object(const D3DXMATRIX *Mat3, const D3DXMATRIX *Mat4, const S_GROUND_INIT_DATA * Init_Data_Ground);

	~C_Ground_Object();

	// 更新処理
	bool Update();

	// 表示
	void Draw3D();

	//表示数の渡し
	unsigned int Get_Object_Draw_Num(void) {
		return M_Object.size();
	}

	//情報渡し
	S_Base3D_2 Get_Object_Data(const unsigned int *No);

	//表示のFlgのセット
	void Set_DrawFlg_Object(const unsigned int *No,const bool *Flg);

	//建物の初期化
	void Init_Bill(void);

	//外灯の初期化
	void Init_Light(void);

protected:
	//更新
	void Update_Object(void);
private:
	//表示
	void Draw_Object(void);

	std::vector<C_Object_Base*>M_Object;

	//表示の削除
	void Delete_All_Object(void);

	//表示の行列の取得
	D3DXMATRIX Get_Object_SetMat(const unsigned int *No);
};