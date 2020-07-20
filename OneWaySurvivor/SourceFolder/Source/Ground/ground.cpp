#include"ground.h"
#include"../MaterialManager/TextureManager.h"

extern LPDIRECT3DDEVICE9 lpD3DDevice;
extern TextureManager textureManager;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

C_Ground::C_Ground(const int * i)
{
	Init();
	D3DXMatrixTranslation(&ground.Base.Mat, 0, 0, (ground.Base.Pos.z*2.0f) * (*i));
	DrawMat = ground.Base.Mat;
	IdenFlg = false;

	//StartMatの作成
	way.StartMat = ground.Base.Mat;

	//横の初期化
	way.CurTransX = new float[way.RailNum];
	//車線の幅初期
	float CurX = 10.0f;
	for (int g = way.RailNum - 1; g >= 0; g--) {
		way.CurTransX[g] = CurX;
		CurX -= 5.0f;
	}

	InitWall();
}

C_Ground::C_Ground(const D3DXMATRIX *Mat3, const D3DXMATRIX *Mat4, const S_GROUND_INIT_DATA * Init_Data_Ground)
{
	Init();
	ground.Base.Flg = false;

	S_GROUND_INIT_DATA L_Init_Data = *Init_Data_Ground;

	if ((L_Init_Data.gType < 0) || (L_Init_Data.gType > 2)) {
		L_Init_Data.gType = 0;
	}
	if (L_Init_Data.LengthAuto == true) {
		L_Init_Data.Length = ground.Base.Pos.z*2.0f;
	}
	way.WayType = L_Init_Data.gType;
	D3DXMATRIX Mat2, Mat1, Trans, RotY;
	D3DXVECTOR3 Pos[4], Vec;
	bool qFlg = true, bc = true;//クォータニオン用のMat管理
	if (L_Init_Data.gType != 0) {
		way.Ang = L_Init_Data.Ang;
	}
	if (L_Init_Data.gType == 0) {//真っ直ぐ
		D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, L_Init_Data.Length);
		Mat2 = Trans * (*Mat3);
		Mat1 = Trans * (*Mat4);
		judg.SetPosM(&Pos[0], &Mat1);
		judg.SetPosM(&Pos[1], &Mat2);
		judg.SetPosM(&Pos[2], Mat3);
		judg.SetPosM(&Pos[3], Mat4);
		ground.Base.Mat = *Mat4;
		//中心点
		D3DXVECTOR3 gVec, gPos;
		gVec = Pos[2] - Pos[3];
		gVec /= 2.0f;
		gPos = Pos[3];
		gPos += gVec;
		gVec = Pos[1] - Pos[2];
		gVec /= 2.0f;
		gPos += gVec;
		judg.SetMatP(&ground.Base.Mat, &gPos);
		qFlg = false;
	}
	else {
		if (L_Init_Data.gType == 1) {//カーブ(左肩上がり)
			D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, L_Init_Data.Length);
			if (L_Init_Data.Ang < 0.0f)L_Init_Data.Ang *= -1.0f;
			D3DXMatrixRotationY(&RotY, D3DXToRadian(L_Init_Data.Ang));
			Mat2 = Trans * (*Mat3);
			Mat2 = RotY * Mat2;
			ground.Base.RotY = RotY;
			judg.SetPosM(&Pos[1], &Mat2);
			judg.SetPosM(&Pos[2], Mat3);
			judg.SetPosM(&Pos[3], Mat4);
			D3DXVec3TransformNormal(&Vec, &D3DXVECTOR3(-1.0f, 0.0f, 0.0f), &Mat2);
			Pos[0] = Pos[1] + Vec * (ground.Base.Pos.x*2.0f);
			//中心点
			D3DXVECTOR3 gVec, gPos;
			gVec = Pos[2] - Pos[3];
			gVec /= 2.0f;
			ground.Base.Mat = *Mat4;
			gPos = Pos[3];
			gPos += gVec;
			gVec = Pos[1] - Pos[2];
			gVec /= 2.0f;
			gPos += gVec;
			judg.SetMatP(&ground.Base.Mat, &gPos);
			ground.Tex = textureManager.GetTexture("syadou10-1.png", 650, 300, NULL);
			CurveGroundFlg = true;
		}
		else {
			if (L_Init_Data.gType == 2) {//カーブ(右肩上がり)
				D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, L_Init_Data.Length);
				if (L_Init_Data.Ang > 0.0f)L_Init_Data.Ang *= -1.0f;
				D3DXMatrixRotationY(&RotY, D3DXToRadian(L_Init_Data.Ang));
				Mat1 = Trans * (*Mat4);
				Mat1 = RotY * Mat1;
				ground.Base.RotY = RotY;
				judg.SetPosM(&Pos[0], &Mat1);
				judg.SetPosM(&Pos[2], Mat3);
				judg.SetPosM(&Pos[3], Mat4);
				D3DXVec3TransformNormal(&Vec, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &Mat1);
				Pos[1] = Pos[0] + Vec * (ground.Base.Pos.x*2.0f);
				//中心点
				D3DXVECTOR3 gVec, gPos;
				gVec = Pos[3] - Pos[2];
				gVec /= 2.0f;
				ground.Base.Mat = *Mat3;
				gPos = Pos[3];
				gPos += gVec;
				gVec = Pos[0] - Pos[3];
				gVec /= 2.0f;
				gPos += gVec;
				judg.SetMatP(&ground.Base.Mat, &gPos);
				bc = false;
				//ground.TEX.Tex = textureManager.GetTexture("Texture/syadou8.png", ground.TEX.Width, ground.TEX.Height, NULL);
				CurveGroundFlg = true;
			}
		}
	}
	ground.v[0].Pos = Pos[0];
	ground.v[1].Pos = Pos[1];
	ground.v[2].Pos = Pos[2];
	ground.v[3].Pos = Pos[3];
	IdenFlg = true;
	D3DXMatrixIdentity(&DrawMat);

	//StartMatの作成
	D3DXVECTOR3 NowPos, MoveVec;
	judg.MatMatVec(&MoveVec, *Mat4, *Mat3);
	judg.SetPosM(&NowPos, Mat4);
	NowPos += MoveVec / 2.0f;
	if ((L_Init_Data.gType < 2)) {
		//左と前
		MoveVec = ground.v[1].Pos - ground.v[2].Pos;
	}
	else {
		//右
		MoveVec = ground.v[0].Pos - ground.v[3].Pos;
	}
	NowPos += MoveVec / 2.0f;
	way.StartMat = *Mat4;
	judg.SetMatP(&way.StartMat, &NowPos);

	//横の初期化
	way.CurTransX = new float[way.RailNum];
	//車線の幅初期
	float CurX = 10.0f;
	for (int i = way.RailNum - 1; i >= 0; i--) {
		way.CurTransX[i] = CurX;
		CurX -= 5.0f;
	}

	InitWall();
}

C_Ground::~C_Ground()
{
	if (way.CurTransX != nullptr) delete[] way.CurTransX;

	if (wall.size() > 0)
	{
		for (unsigned int wc = 0; wc < wall.size(); wc++) {
			delete wall[wc];
			wall.erase(wall.begin() + wc);
			wc--;
		}
	}
}

bool C_Ground::Update()
{
	UpdateGround();

	return true;
}

void C_Ground::UpdateGround()
{
	ground.v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	ground.v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	ground.v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	ground.v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);

	ground.v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	ground.v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	ground.v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	ground.v[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

}

void C_Ground::Draw3DGround()
{
	//地面の表示
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetTexture(0, ground.Tex);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &DrawMat);
	lpD3DDevice->SetFVF(FVF_VERTEX);//バグ
	lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, ground.v, sizeof(VERTEX));//2はポリゴン数
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	if (wall.size() > 0)
	{
		for (auto && w : wall)w->Draw3D();
	}
}

void C_Ground::Init()
{
	//画像のロード
	ground.Tex = textureManager.GetTexture("syadou8-2.png", 650, 300, NULL);

	D3DXMatrixTranslation(&ground.Base.Mat, 0, 0, 0);
	ground.Base.Flg = true;
	ground.Base.Pos = D3DXVECTOR3(13.0f, 0.0f, 5.0f);
	way.RailNum = 5;
	MoveFlg = false;
	D3DXMatrixRotationY(&ground.Base.RotY, D3DXToRadian(0.0f));
	D3DXVECTOR3 Pos = ground.Base.Pos;
	ground.v[0].Pos = D3DXVECTOR3(-Pos.x, 0.0f, Pos.z);//x,y,z
	ground.v[1].Pos = D3DXVECTOR3(Pos.x, 0.0f, Pos.z);
	ground.v[2].Pos = D3DXVECTOR3(Pos.x, 0.0f, -Pos.z);
	ground.v[3].Pos = D3DXVECTOR3(-Pos.x, 0.0f, -Pos.z);

	way.WayType = 0;
	way.Ang = 0.0f;

	//地面の表示Flg初期化
	ground.Base.DrawFlg = true;

	CurveGroundFlg = false;
}

void C_Ground::InitWall(void)
{
	// 壁の初期化
	// 左
	bool LeftFlg = true;
	wall.push_back(new c_Wall(&IdenFlg, &LeftFlg, &ground.Base.Mat, &ground.v[3].Pos, &ground.v[0].Pos));
	// 右
	LeftFlg = false;
	wall.push_back(new c_Wall(&IdenFlg, &LeftFlg, &ground.Base.Mat, &ground.v[2].Pos, &ground.v[1].Pos));
}

D3DXMATRIX C_Ground::GetMat0()
{
	//新たな道用
	D3DXMATRIX Trans;
	if (IdenFlg == false) {
		judg.setTransMat(&Trans, &ground.v[0].Pos);
		Trans = Trans * ground.Base.Mat;
	}
	else {
		Trans = ground.Base.Mat;
		D3DXVECTOR3 gPos;
		gPos = ground.v[0].Pos;
		judg.SetMatP(&Trans, &gPos);
		Trans = ground.Base.RotY*Trans;
	}
	return Trans;
}

D3DXMATRIX C_Ground::GetMat1()
{
	D3DXMATRIX Trans;
	if (IdenFlg == false) {
		judg.setTransMat(&Trans, &ground.v[1].Pos);
		Trans = Trans * ground.Base.Mat;
	}
	else {
		Trans = ground.Base.Mat;
		D3DXVECTOR3 gPos;
		gPos = ground.v[1].Pos;
		judg.SetMatP(&Trans, &gPos);
		Trans = ground.Base.RotY*Trans;
	}
	return Trans;
}

bool C_Ground::PolygonRayJudg(float *Dis, const D3DXMATRIX *Mat,const D3DXVECTOR3 *Ray)
{
	return judg.RayJudg_Polygon(&judg.SetPosM(Mat), Ray, &ground.Base.Mat,
		&ground.v[0].Pos, &ground.v[1].Pos, &ground.v[2].Pos, &ground.v[3].Pos, Dis, &IdenFlg);
}

bool C_Ground::BallJudgGround(const D3DXVECTOR3 * Pos, const float * Radius)
{
	return judg.BallJudg(Pos, &judg.SetPosM(&ground.Base.Mat), Radius);
}

bool C_Ground::MeshRayJudgWall(float *Dis, const D3DXVECTOR3 *Pos, const D3DXVECTOR3 *Ray,const unsigned int * wc)
{
	return wall[*wc]->MeshRayJudg(Dis, Pos, Ray);
}
