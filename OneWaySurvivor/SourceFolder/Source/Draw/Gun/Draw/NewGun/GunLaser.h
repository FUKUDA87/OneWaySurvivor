#pragma once
#include"GunBullet.h"
#include"../../Laser/LaserBase2.h"

class C_GunLaser :public C_GunBullet {
public:
	~C_GunLaser();
	//表示の処理
	void Draw(const D3DXVECTOR3* CameraPos);
	void GetDis(const float* Dis);
protected:
	C_LaserBase2 *mc_Laser;
	float m_Dis;
	//表示
	void Draw3D_Laser(const D3DXVECTOR3*CamPos);

	//レーザーの作成
	void New_Laser(void);
private:

};