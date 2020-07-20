#pragma once
#include<d3dx9.h>

class c_Ball3D {
public:
	c_Ball3D(float Radius);
	c_Ball3D(float Radius,float alpha);
	~c_Ball3D();

	void Draw();
	void DrawB();

	void SetPos(const D3DXVECTOR3 *Pos) { pos = *Pos; }

	void SetRadius(void);

	float GetRadius(void) { return radius; }

	D3DXVECTOR3 GetPos(void) { return pos; }

protected:
	void Init(void);
	void Release(void);
private:
	LPD3DXMESH lpBall;//メッシュの形状のデータを入れる変数
	D3DMATERIAL9 BallMaterial;//マテリアル（色・材質）
	D3DXVECTOR3 pos;
	float radius;
};
