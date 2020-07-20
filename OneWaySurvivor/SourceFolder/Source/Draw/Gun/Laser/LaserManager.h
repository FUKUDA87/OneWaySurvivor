#pragma once
#include"LaserBase.h"
#include<d3dx9.h>

class LaserManager {
private:
	LaserBase *laserBase;
public:
	LaserManager() { 
		laserBase = new LaserBase();
	};
	~LaserManager() { 
		delete laserBase; 
	};
	void LaserCha(LaserBase* NewLaser);
	bool UpdateS(D3DXMATRIX Mat, D3DXMATRIX Tmp);
	bool UpdateL(float Dis, bool Flg);
	void Draw3D() {
		laserBase->Draw3D();
	}
	D3DXMATRIX GetLMat() {
		return laserBase->GetLasMat();
	}
	D3DXVECTOR3 GetLVec() {
		return laserBase->GetLasVec();
	}
	float GetLDis() {
		return laserBase->GetLasDis();
	}
	void SetLFlg(bool Flg) {
		laserBase->SetLasFlg(Flg);
	}
	bool GetLFlg(void) {
		return laserBase->GetLasFlg();
	}
};