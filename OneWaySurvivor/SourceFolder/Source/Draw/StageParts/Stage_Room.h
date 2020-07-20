#pragma once
#include"CarSet.h"
#include<string>

class C_Stage_Room_Stand {
public:
	C_Stage_Room_Stand(const D3DXVECTOR3 *Set_Pos, std::string FileName);
	~C_Stage_Room_Stand();

	//表示
	void Draw_Garage_Stand(const D3DXVECTOR3 *CameraPos);

	//更新
	bool Update_Garage_Stand(void);

private:
	C_Draw3D_Base2 * M_Garage_Stand;

	D3DXVECTOR3 M_Stand_Pos;

	//削除
	void Delete_Garage_Stand(void);

	//行列の更新
	void Set_Mat_Garage_Stand(void);

	//表示の初期化
	void New_Garage_Stand(std::string FileName);
};