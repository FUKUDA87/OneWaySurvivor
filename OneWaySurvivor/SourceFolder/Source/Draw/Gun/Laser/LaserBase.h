#pragma once
#include"../../../GameSource/Struct.h"
#include<d3dx9.h>

class LaserBase {
private:
protected:
	S_Polygon lasS;//始点
	S_Polygon Las;//レーザー
	S_Polygon lasE;//終点
	float LasDis;
	bool lasFlg;
public:
	virtual void Init() {
		lasFlg = false;
	};
	LaserBase();
	LaserBase(float Dis);
	~LaserBase() {};
	virtual bool UpdateS() { return true; };//始点
	virtual bool UpdateS(D3DXMATRIX Mat,D3DXMATRIX Tmp) { return true; };//始点
	virtual bool UpdateL() { return true; };//線
	virtual bool UpdateL(float Dis,bool Flg) { return true; };//線
	virtual bool UpdateE() { return true; };//終点
	virtual void Draw3D() {};
	D3DXMATRIX GetLasMat() {
		return Las.Base.Mat;
	};
	float GetLasDis() {
		return LasDis;
	}
	virtual D3DXVECTOR3 GetLasVec() {
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	virtual void SetLasFlg(bool Flg) {
		lasFlg = Flg;
	}
	virtual bool GetLasFlg(void) {
		return lasFlg;
	}
};