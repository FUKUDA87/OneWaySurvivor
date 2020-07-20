#pragma once
#include"PartsBase.h"
#include"../../Move/Parts/Move_Parts_Base.h"

class C_Car_Parts_Base :public C_PartsBase {
public:
	C_Car_Parts_Base(const S_CAR_PARTS_DATA *set_Data);
	~C_Car_Parts_Base();

	//表示
	void Draw_Parts(const D3DXVECTOR3 *CameraPos);

	//更新
	bool UpdateParts(const D3DXMATRIX *Mat);
	bool UpdateParts(const D3DXMATRIX *Mat, const int *GetNowSpeed, const int *GetMaxSpeed,const D3DXVECTOR3* Car_ScalPos,const D3DXVECTOR3* Parts_ScalPos);

	//パーツ情報渡し
	S_CAR_PARTS_DATA Get_Parts_Data(void) {
		return M_Parts_Data;
	}

	//動きの初期化
	void New_Move(C_Move_Parts_Base *New);

	//動きのセット
	void Set_I_MoveFlg(const int Flg);

	//表示の行列渡し
	D3DXMATRIX Get_Draw_Mat(void);

	//表示の表示行列渡し
	D3DXMATRIX Get_Draw_DrawMat(void);

protected:
	//車の位置データ
	S_CAR_PARTS_DATA M_Parts_Data;

	//パーツのデータ作成
	S_CAR_PARTS_DATA Get_S_PARTS_DATA(const D3DXVECTOR3 TransPos, const D3DXVECTOR3 Ang);

	//動きの削除
	void Move_Delete(void);

	C_Move_Parts_Base *M_Move;

	//0が停止、１が動け、２がリバース
	int M_I_MoveFlg;
private:

};