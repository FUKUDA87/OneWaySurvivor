#include"Wall.h"
#include"../MaterialManager/TextureManager.h"
#include"../MaterialManager/XfileManager.h"
#include"../GameSource/Judgment.h"
#include"../MaterialManager/XFileManager.h"
#include"../GameSource/StructManager.h"

extern XFileManager xfileManager;
extern LPDIRECT3DDEVICE9 lpD3DDevice;
extern TextureManager textureManager;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

void DrawMesh(XFILE *XFile);

c_Wall::c_Wall(const bool * PolygonIdenFlg, const bool *LeftFlg, const D3DXMATRIX * Mat
	, const D3DXVECTOR3 * StartPos, const D3DXVECTOR3 * EndPos)
{
	//壁3Dの初期化
	//壁のロード
	wallMesh = xfileManager.GetMeshB("Wall3-3.x");

	//壁のコリジョンモデルのロード
	collisionMesh = xfileManager.GetMesh("Wall2CM1.x");

	//サイズ調整
	Wall3D.Base.ScaPos = D3DXVECTOR3(1.0f*0.5f, 3.0f, wallMesh.Data.SmallVec.z - wallMesh.Data.BigVec.z);
	if (Wall3D.Base.ScaPos.z < 0.0f)Wall3D.Base.ScaPos.z *= -1.0f;

	//表示のFlgの初期化
	Wall3D.Base.DrawFlg = true;

	// 位置の初期化
	if (*PolygonIdenFlg == false) 
	{
		//行列の初期化
		D3DXMatrixTranslation(&Wall3D.Base.Mat, EndPos->x, 0.0f, 0.0f);
		Wall3D.Base.Mat = Wall3D.Base.Mat*(*Mat);

		Wall3D.Base.TraPos = D3DXVECTOR3(0.0f, wallMesh.Data.SmallVec.y*-1.0f, 0.0f);
		//幅の調整
		D3DXVECTOR3 Vec = *EndPos - *StartPos;

		InitWallSizeZ(&Vec);

		Wall3D.Base.TraPos.y *= Wall3D.Base.ScaPos.y;
		//反映
		Judg judg;
		judg.setTransMat(&Wall3D.Base.Trans, &Wall3D.Base.TraPos);
		
	}
	else {
		//大きさの初期化
		D3DXVECTOR3 wVec = *EndPos - *StartPos
			, FrontVec = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		InitWallSizeZ(&wVec);

		//位置の代入
		D3DXVECTOR3 Pos = *StartPos + wVec / 2.0f;
		Judg judg;
		judg.setTransMat(&Wall3D.Base.Mat, &Pos);
		//回転
		D3DXMATRIX RotX, RotY;
		judg.TarEndMat(&Wall3D.Base.Mat, Wall3D.Base.Mat, &RotX, &RotY, *EndPos, FrontVec);
		//ｙ方向に移動させるTransMatの作成
		Pos.y = wallMesh.Data.SmallVec.y*Wall3D.Base.ScaPos.y;
		if (Pos.y < 0.0f)Pos.y *= -1.0f;
		D3DXMatrixTranslation(&Wall3D.Base.Trans, 0.0f, Pos.y, 0.0f);

	}

	// 壁のサイズの初期化後の初期化
	
	// 回転
	if (*LeftFlg == true) {
		D3DXMatrixRotationY(&Wall3D.Base.RotY, D3DXToRadian(0.0f));
	}
	else {
		D3DXMatrixRotationY(&Wall3D.Base.RotY, D3DXToRadian(180.0f));
	}

	/*バウンディングスフィアの初期化*/
	Judg judg;
	judg.Get_Draw_Radius(&Wall3D.CullingRad, &wallMesh.Data.BigVec, &wallMesh.Data.SmallVec, &Wall3D.Base.ScaPos);


	// カプセル初期化
	c_StructManager structManager;
	capsule = structManager.getCapsule(&Wall3D.Base.Mat, &Wall3D.Base.ScaPos, &wallMesh.Data.BigVec, &wallMesh.Data.SmallVec);

}

void c_Wall::Draw3D()
{
	if (Wall3D.Base.DrawFlg != true)return;
	
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &GetDrawMat());
	DrawMesh(&wallMesh.Mesh);
	lpD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

D3DXMATRIX c_Wall::GetDrawMat()
{
	D3DXMATRIX TmpMat = GetMat();
	TmpMat = Wall3D.Base.Scal*TmpMat;
	return TmpMat;
}

D3DXMATRIX c_Wall::GetMat()
{
	D3DXMATRIX TmpMat;
	TmpMat = Wall3D.Base.RotY*Wall3D.Base.Trans*Wall3D.Base.Mat;
	return TmpMat;
}

S_Base3D_2 c_Wall::GetData()
{
	return Wall3D;
}

void c_Wall::SetDrawFlg(const bool * DrawFlg)
{
	Wall3D.Base.DrawFlg = *DrawFlg;
}

bool c_Wall::capsuleJudg(float * sd, int *hitNum, const S_Capsule * c)
{
	Judg judg;
	bool b = judg.colCapsuleCapsule(&capsule, c, sd, hitNum);
	return b;
}

bool c_Wall::MeshRayJudg(float * Dis, const D3DXVECTOR3 * Pos, const D3DXVECTOR3 * Ray)
{
	Judg judg;
	return judg.RayJudg_Mesh(Pos, Ray, &GetDrawMat(), collisionMesh.lpMesh, Dis);
}

void c_Wall::InitWallSizeZ(const D3DXVECTOR3 * Ground_Vec)
{

	Wall3D.Base.ScaPos.z = D3DXVec3Length(Ground_Vec) / Wall3D.Base.ScaPos.z;
	if (Wall3D.Base.ScaPos.z < 0.0f)Wall3D.Base.ScaPos.z *= -1.0f;
	Wall3D.Base.ScaPos.z += 0.02f;

	Judg judg;
	judg.setScalingMat(&Wall3D.Base.Scal, &Wall3D.Base.ScaPos);
}
