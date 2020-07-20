#pragma once
#include"Spark.h"

class C_SparkDamage :public C_Spark {
public:
	C_SparkDamage(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos);
	//地面(0)と壁(1,2)と車(3)に弾が当たった時の火花
	C_SparkDamage(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos, const int *SparkFlg, const float *Ang);
	~C_SparkDamage();
	
	// 更新処理
	bool Update(void);

	// 表示
	void Draw3D(const D3DXVECTOR3 *CameraPos);
protected:
	//アップデート
	bool UpdateSD(void);
	bool UpdateCar(void);

	//表示
	void DrawSD(const D3DXVECTOR3 *CameraPos);
private:
	//変数----------------------------------------------------------------------------------
	S_Polygon Flash;
	//最初だけ表示Flg
	bool DrawSDFlg;
	//ポリゴンサイズSD
	float PolSizeSD;
	//Updateの仕方Flg
	bool UpdateFlg;
	//関数----------------------------------------------------------------------------------
	//地面判定
	void SparkJudgGround(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos, const int *SparkFlg);
	//壁判定
	void SparkJudgWall(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos, const int *SparkFlg);
	//車判定
	void SparkJudgCar(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos, const int *SparkFlg, const float *Ang);
};