#pragma once
#include"Spark.h"

class C_BulGro :public C_Spark {
public:
	C_BulGro(const D3DXMATRIX *Mat,const D3DXVECTOR3 *Pos);
	~C_BulGro();
	
	//アップデート
	bool Update(void);
	//表示
	void Draw3D(const D3DXVECTOR3 *CameraPos);
protected:
	//初期化
	void InitBG(void);
private:
	//煙昇の表示
	S_Polygon Smoke;
	float SmoUpY;
	//煙サイドの表示
	S_Polygon SmokeS[2];
	int SmokeNum;
	//アスファルトの欠片
	XFILE AspMesh;
	BASE3D *AspMat;
	int AspNum;

	//表示の薄れ
	int NowAlpha,AlphaDown;
	//スモークの拡大
	float ScaSmo;
};