#pragma once
#include<d3dx9.h>
#include"../GameSource/Judgment.h"
#include"../GameSource/Struct.h"
#include<vector>
#include"Wall.h"

class C_Ground {
public:
	C_Ground(const int *i);
	C_Ground(const D3DXMATRIX *Mat3, const D3DXMATRIX *Mat4,const S_GROUND_INIT_DATA* Init_Data_Ground);
	~C_Ground();
	
	// XVˆ—
	virtual bool Update();

	// •\Ž¦
	virtual void Draw3D() { Draw3DGround(); }

	D3DXMATRIX GetMat(void) { return ground.Base.Mat; }

	bool GetFlg(void) { return ground.Base.Flg; }

	void SetFlg(bool b) { ground.Base.Flg = b; }

	Way GetWay(void) { return way; }

	float GetPosZ(void) { return ground.Base.Pos.z; }

	D3DXMATRIX GetMat0();

	D3DXMATRIX GetMat1();

	bool getCurveGround(void) { return CurveGroundFlg; }

	bool PolygonRayJudg(float *Dis, const D3DXMATRIX *Mat, const D3DXVECTOR3 *Ray);

	bool BallJudgGround(const D3DXVECTOR3 *Pos, const float *Radius);

	// •Ç
	unsigned int GetWallNum(void) { return wall.size(); }
	D3DXMATRIX GetWallMat(const unsigned int *wc) { return wall[*wc]->GetMat(); }
	bool MeshRayJudgWall(float *Dis, const D3DXVECTOR3 *Pos, const D3DXVECTOR3 *Ray, const unsigned int * wc);
	S_Base3D_2 GetWallData(const unsigned int *wc) { return wall[*wc]->GetData(); }
	void SetWallDrawFlg(const unsigned int *wc, const bool *DrawFlg) { return wall[*wc]->SetDrawFlg(DrawFlg); }
	S_Capsule GetCapsuleWall(const unsigned int *wc) { return wall[*wc]->GetCapsule(); }
	bool capsuleJudg(const unsigned int *wc, float *sd, int *hitNum, const S_Capsule *c) { return wall[*wc]->capsuleJudg(sd, hitNum, c); }

protected:
	S_Polygon ground;

	Way way;

	D3DXMATRIX DrawMat;

	bool MoveFlg;

	bool IdenFlg;

	std::vector<c_Wall*>wall;

	Judg judg;

	bool CurveGroundFlg;

	void UpdateGround();

	void Draw3DGround();
private:
	void Init();
	void InitWall(void);
};