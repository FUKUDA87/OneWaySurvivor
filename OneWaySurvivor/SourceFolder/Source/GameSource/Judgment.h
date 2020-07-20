#pragma once
#include<d3dx9.h>
#include"Struct.h"

#ifndef Judgm_H
#define Judgm_H

extern LPDIRECT3DDEVICE9 lpD3DDevice;


class Judg {
public:
	//距離判定
	bool BallJudg(const D3DXVECTOR3 *PosA, const D3DXVECTOR3 *PosB,const float *Radius);
	bool BallJudg(float * SmallDis, const D3DXVECTOR3 * PosA, const D3DXVECTOR3 * PosB, const float * Radius, const bool *Flg);
	//距離判定+球と球
	bool ball(D3DXMATRIX mat1, D3DXMATRIX mat2, float rad, D3DXMATRIX *Trans1, D3DXMATRIX *Trans2);
	//距離判定+距離取得
	float BallJudg(const D3DXVECTOR3 * PosA, const D3DXVECTOR3 * PosB);

	//出現する位置に被らない様にする判定
	bool Pop_BallJudg(const D3DXVECTOR3 *PosA, const D3DXVECTOR3 *PosB, const float *Radius);

	//Hpの処理
	bool HPj(int *NowHp, int *NowMaxHp);

	/*レイ判定*/

	//板ポリゴンにレイ判定
	bool RayJudg_Polygon(const D3DXVECTOR3 *Ray_Pos, const D3DXVECTOR3 *Ray_Vec,
		const D3DXVECTOR3 *vA, const D3DXVECTOR3 *vB, const D3DXVECTOR3 *vC, const D3DXVECTOR3 *vD, float *Dis);

	//板ポリゴンにレイ判定(+行列から頂点計算)
	bool RayJudg_Polygon(const D3DXVECTOR3 *Ray_Pos, const D3DXVECTOR3 *Ray_Vec, const D3DXMATRIX *Polygon_Mat,
		const D3DXVECTOR3 *vA, const D3DXVECTOR3 *vB, const D3DXVECTOR3 *vC, const D3DXVECTOR3 *vD, float *Dis);

	//板ポリゴンにレイ判定(+レイ判定種類判定)
	bool RayJudg_Polygon(const D3DXVECTOR3 *Ray_Pos, const D3DXVECTOR3 *Ray_Vec, const D3DXMATRIX *Polygon_Mat,
		const D3DXVECTOR3 *vA, const D3DXVECTOR3 *vB, const D3DXVECTOR3 *vC, const D3DXVECTOR3 *vD,
		float *Dis, const bool *Judg_Type_IdenMat);

	//板ポリゴンにレイ判定+レイが当たった長さ判定
	bool RayJudg_Polygon_SmallDis(const D3DXVECTOR3 *Ray_Pos, const D3DXVECTOR3 *Ray_Vec, const D3DXMATRIX *Polygon_Mat,
		const D3DXVECTOR3 *vA,const D3DXVECTOR3 *vB,const D3DXVECTOR3 *vC,const D3DXVECTOR3 *vD, float *Small_Dis);

	//板ポリゴにレイ判定+レイが当たった長さ判定(+行列から頂点計算)
	bool RayJudg_Polygon_SmallDis(const D3DXVECTOR3 *Ray_Pos, const D3DXVECTOR3 *Ray_Vec,
		const D3DXVECTOR3 *vA, const D3DXVECTOR3 *vB, const D3DXVECTOR3 *vC, const D3DXVECTOR3 *vD, float *Small_Dis);

	//Meshにレイ判定
	bool RayJudg_Mesh(const D3DXVECTOR3 *Ray_Pos, const D3DXVECTOR3 *Ray_Vec,
		const D3DXMATRIX *Draw_Mat, const LPD3DXMESH Mesh, float *Dis);

	//Meshにレイ判定(当たったポリゴン数)
	int RayJudg_Mesh_PolNum(const D3DXVECTOR3 *Ray_Pos, const D3DXVECTOR3 *Ray_Vec,
		const D3DXMATRIX *Draw_Mat, const LPD3DXMESH Mesh, float *Dis);

	//Meshにレイ判定+レイが当たった長さ判定
	bool RayJudg_Mesh_SmallDis(const D3DXVECTOR3 *Ray_Pos, const D3DXVECTOR3 *Ray_Vec,
		const D3DXMATRIX *Draw_Mat, const LPD3DXMESH Mesh, float *Small_Dis);

	/**/

	//3Dから2Dの座標取得
	void Pos2D(D3DXVECTOR3 *Pos_2D,const D3DXVECTOR3 *Pos3D,const D3DXMATRIX *mProj,const D3DXMATRIX *mView,const D3DVIEWPORT9 *Viewport);
	//3Dから2Dの座標取得+playerとenemyの逆位置作成
	void Pos2DPE(D3DXVECTOR3 *Pos_2D,const D3DXMATRIX *eMat,const D3DXMATRIX *pMat, const D3DXMATRIX * mProj, const D3DXMATRIX * mView, const D3DVIEWPORT9 * Viewport);
	//Ang計算
	double Ang(D3DXVECTOR3 pla, D3DXVECTOR3 tar, D3DXVECTOR3 vec);
	
	//外積内積
	bool CroDot(D3DXMATRIX mat, D3DXMATRIX *rot, D3DXVECTOR3 targetPos, D3DXVECTOR3 FrontVec, double *Ang,double ang, bool angF);
	//tragetX回転用(ミサイル回転)
	bool TarRotX(D3DXMATRIX mat, D3DXMATRIX * rotX, D3DXVECTOR3 targetPos, D3DXVECTOR3 FrontVec);
	//tragetY回転用(カツオ回転)
	bool TarRotY(D3DXMATRIX mat,D3DXMATRIX *rotY,  D3DXVECTOR3 targetPos, D3DXVECTOR3 FrontVec);
	//tragetEndMat作成
	bool TarEndMat(D3DXMATRIX *mat,D3DXMATRIX TransMat, D3DXMATRIX * RotXMat, D3DXMATRIX *RotYMat, D3DXVECTOR3 TargetPos, D3DXVECTOR3 FrontVec);

	//行列を座標に変換
	D3DXVECTOR3 SetPosM(const D3DXMATRIX *Mat);
	D3DXVECTOR2 SetPos2DM(const D3DXMATRIX *Mat);
	void SetPosM(D3DXVECTOR3 *Pos, const D3DXMATRIX *Mat);

	//座標を行列に変換
	D3DXMATRIX SetMatP(const D3DXVECTOR3 *Pos);
	void SetMatP(D3DXMATRIX *Mat,const D3DXVECTOR3 *Pos);

	//移動行列のセット
	void setTransMat(D3DXMATRIX *TransMat, const D3DXVECTOR3 *TransPos);
	void setTransMat(D3DXMATRIX *TransMat, const D3DXVECTOR2 *TransPos);
	D3DXMATRIX getTransMat(const D3DXVECTOR3 *TransPos);
	D3DXMATRIX getTransMat(const D3DXVECTOR2 *TransPos);

	//クォータニオン==============================================================================================
	//アニメーション
	bool AnimeProc(D3DXMATRIX *NowMat, D3DXMATRIX StartMat, D3DXMATRIX EndMat, float AnimeFrame);
	void AnimeQua(D3DXMATRIX *NowMat,const D3DXMATRIX *StartMat,const D3DXMATRIX *EndMat,const float *AnimeFrame);
	bool AnimeProc(D3DXVECTOR3 *NowPos, D3DXVECTOR3 StartPos, D3DXVECTOR3 EndPos, float AnimeFrame);
	//AnimeFrame+=
	bool AnimeFrameInc(float *AnimeFrame, float up, bool upFlg);
	bool AnimeFrameInc(float *AnimeFrame,const float *up,const bool *FrameMoveFlg);
	//アニメーション+AnimeFrame+=
	bool Quaternion(D3DXMATRIX *NowMat, D3DXMATRIX StartMat, D3DXMATRIX EndMat, float *AnimeFrame, float up, bool upFlg);
	bool Quaternion(D3DXVECTOR3 *NowPos, D3DXVECTOR3 StartPos, D3DXVECTOR3 EndPos, float *AnimeFrame, float up, bool upFlg);
	bool Quaternion(D3DXVECTOR2 *NowPos, D3DXVECTOR2 StartPos, D3DXVECTOR2 EndPos, float *AnimeFrame, float up, bool upFlg);
	//レイ判定のDisをPos変換
	D3DXVECTOR3 DisPos(D3DXVECTOR3 PosA, D3DXVECTOR3 PosB, float Dis);
	//ビルボード
	D3DXVECTOR3 Billboard(const D3DXVECTOR3 *OldPos, const D3DXVECTOR3 *NowPos, const D3DXVECTOR3 *camPos, const float *Size);
	//ビルボード＋板ポリ対応
	D3DXVECTOR3 Billboard(const D3DXVECTOR3 *OldPos, const D3DXVECTOR3 *NowPos, const D3DXVECTOR3 *CameraPos, const float *Size, const bool *Reverse);
	//線とレイ2D
	bool LineLine(const D3DXVECTOR2 PosA, const D3DXVECTOR2 VecA, const D3DXVECTOR2 PosB, const D3DXVECTOR2 VecB, float *Dis);
	//画像の半分サイズ
	D3DXVECTOR2 HalfSize(const D3DXVECTOR3 sPos, const int Width, const int Height);
	//2Dの画像の枠計算
	bool PlaneP(RECT *rc, const D3DXVECTOR2 *Pos, const D3DXVECTOR2 *scalSize, const int *Width, const int *Height);
	//2D画像クリック(四角形)
	bool PlaneCri(const D3DXVECTOR2 *Pos, const D3DXVECTOR2 *scalSize, const int *Width, const int *Height);
	bool PlaneCri(const D3DXVECTOR3 *Pos, const D3DXVECTOR3 *scalSize, const int *Width, const int *Height);
	//マウス位置
	POINT GetPoint(void);
	//rayray3D
	bool LineLine3D(D3DXVECTOR3 *GetPos, D3DXVECTOR3 PosA1, D3DXVECTOR3 PosA2, D3DXVECTOR3 PosB1, D3DXVECTOR3 PosB2);
	//vectorPos
	D3DXVECTOR3 VecPos(D3DXMATRIX MatA, D3DXVECTOR3 PosB);
	//**Mat入れ
	bool SetppMat(D3DXMATRIX *Mat, D3DXVECTOR3 PosA, D3DXVECTOR3 PosB, D3DXVECTOR3 PosC, int RailNum, bool bc);
	//Vec=MatB-MatA
	bool MatMatVec(D3DXVECTOR3*Vec, D3DXMATRIX MatA, D3DXMATRIX MatB);
	D3DXVECTOR3 MatMatVec(D3DXMATRIX MatA, D3DXMATRIX MatB);
	bool VecMatIn(D3DXMATRIX *Mat,const D3DXVECTOR3 *Vec);
	//Speedクォータニオン変数
	bool SetFloatQ(float *f);
	bool SetFloatQ(D3DXVECTOR3 *Pos);
	float SlashFloat(float fA, float fB);

	// 絶対値
	void Ads(float *f);
	void Ads(D3DXVECTOR3 *p);

	// 大きさ比較
	bool Big(float *fa, const float *fb);
	bool Big(float *f, const float *fa, const float *fb);
	bool Big(D3DXVECTOR3 *p, const D3DXVECTOR3 *pa, const D3DXVECTOR3 *pb);
	bool Big(D3DXVECTOR3 *BigVec, const D3DXVECTOR3 *p);

	bool Small(float *fa, const float *fb);
	bool Small(D3DXVECTOR3 *SmallVec, const D3DXVECTOR3 *p);

	//半径を求める
	float GetRad(XFILE_B * MeshData);

	//リバースFlg
	void ReverseFlg(bool *Flg);
	//リバースFlg
	bool ReverseFlg2(const bool *Flg);
	int Reverse(const bool *Flg);

	//スケイリングMat入れ
	void setScalingMat(D3DXMATRIX *ScalMat, const D3DXVECTOR3 *Pos);
	void setScalingMat(D3DXMATRIX *ScalMat, const D3DXVECTOR2 *Pos);
	D3DXMATRIX getScalingMat(const D3DXVECTOR3 *Pos);
	D3DXMATRIX getScalingMat(const D3DXVECTOR2 *Pos);

	//RotXの初期化
	void InitRotX(const D3DXMATRIX * Mat,D3DXMATRIX*RotX);
	//クォータニオン構造体の初期化関数
	QuaAnimeC InitQuaAnime(const D3DXMATRIX *StartMat, const D3DXMATRIX *EndMat, const float *NowAnime, const float *AnimeFrame);
	//初期化１
	void InitMatPos(D3DXMATRIX *Mat, D3DXVECTOR3 *TransPos, D3DXVECTOR3 *ScalPos);
	//表示用の行列作成
	D3DXMATRIX GetDrawMat(const D3DXMATRIX *Mat,D3DXMATRIX *ScalMat, const D3DXVECTOR3 *ScalPos);
	D3DXMATRIX GetDrawMat(const D3DXMATRIX *Mat,const D3DXVECTOR3 *ScalPos);
	//初期化２
	BASE3D GetInitBase3D(const D3DXVECTOR3 *InitPos, const D3DXVECTOR3 *TransPos, const D3DXVECTOR3 *ScalPos,
		const double * AngX, const  double * AngY, const  double * AngZ);

	//判定用の拡大を含めた移動行列の作成
	D3DXMATRIX GetTransMatScal(const D3DXVECTOR3 *TransPos, const D3DXVECTOR3* ScalPos);
	void Get_TransMatScal(D3DXMATRIX *TransMat,const D3DXVECTOR3 *TransPos, const D3DXVECTOR3* ScalPos);

	//行列の合成(MatA*MatB)
	D3DXMATRIX GetMatY(const D3DXMATRIX *MatA, const D3DXMATRIX *MatB);
	//ベクトルの掛け算
	D3DXVECTOR3 GetVecVec(const D3DXVECTOR3 *VecA, const D3DXVECTOR3 *VecB);
	//ベクトルの割り算
	D3DXVECTOR3 GetVecVec_S(const D3DXVECTOR3 *VecA, const D3DXVECTOR3 *VecB);
	//位置の初期化(Gunバージョン)
	BASE3D InitGunParts(const Object3DGun* Init);
	//位置の初期化(Gunバージョン)
	Object3DGun InitSetPartsData(const float AngX,const float AngY,const float AngZ,const D3DXVECTOR3 *TransPos, const D3DXVECTOR3 *ScalPos,const bool DrawFlg);
	//初期化構造体
	S_GUN_DRAW_NO GetInitGUNDRAWNOS(const int GunNo, const int BulletNo, const int MuzFlaNo, const int LaserNo);
	
	//乱数の初期化
	S_Random GetInitRand(const int x, const int y, const int z);
	//単位行列渡し
	D3DXMATRIX Get_IdenMat(void);
	//初期化行列渡し
	D3DXMATRIX Get_Mat_Init(void);
	//送られてきた番号の検索
	bool Hit_No(const unsigned int *No,const unsigned int *NoNum);
	//２D行列にVec3をたす
	D3DXMATRIX Set_2DMat(const D3DXVECTOR3 *Pos);
	//サイズをベクトル変換
	D3DXVECTOR3 Get_Size3D(const float *Size);
	void Get_Size3D(D3DXVECTOR3 *Pos,const float *Size);
	D3DXVECTOR3 Get_Size2D(const float *Size);

	//レイが当たった座標を求める
	D3DXVECTOR3 GetRayHitPos(const D3DXVECTOR3 *RayPos, const D3DXVECTOR3* RayVec, const float *RayDis);

	//Vec3にVec2を足す
	void Set_Vec3_Vec2(D3DXVECTOR3 *Vec3, const D3DXVECTOR2 *Vec2);

	//マイナスをプラスに変換
	void Change_Plus(float *f);
	void Change_Plus(D3DXVECTOR3 *Vec);

	//大きさ判定
	void Judg_BigNum(float *f_A, const float *f_B);
	void Judg_BigNum(D3DXVECTOR3 *Vec_A, const D3DXVECTOR3 *Vec_B);

	//半径のベクトルを求める処理
	D3DXVECTOR3 Get_RadiusVec(const D3DXVECTOR3 *Vec_A, const D3DXVECTOR3 *Vec_B);
	//半径のベクトルを求めた際に半径を計算する
	void Get_Draw_Radius(float *Radius,const D3DXVECTOR3 *Vec_Big, const D3DXVECTOR3 *Vec_Small, const D3DXVECTOR3 *Scal_Pos);

	//ゼロより上のならtureを返す
	bool Judg_PlusNum(const float *Num);

	//番号の判定
	void Judg_Data_Num(int *Now_Num, const int *Max_Num);
	int Judg_Data_Num2(const int *Now_Num, const int *Max_Num);

	//視錐台の法線ベクトルの計算
	void Get_Frustum_NormalVec(S_Frustum_Vec *Data, const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport,const D3DXVECTOR3 *CameraPos);
	//視錐台カリングの判定(視錐台の中にある場合、true)
	bool Judg_Frustum(const S_Frustum_Vec *Data,const D3DXVECTOR3 *Pos, const float *Radius);

	// カプセル同士の衝突判定
	bool colCapsuleCapsule(const S_Capsule *c1, const S_Capsule *c2, float *d);
	bool colCapsuleCapsuleDis(const S_Capsule *c1, const S_Capsule *c2, float *d);
	bool colCapsuleCapsule(const S_Capsule *c1, const S_Capsule *c2, float *d, int *hitNum);

	// 割合計算
	float rate(const float *Base, const float *f) { return (*f) / (*Base); }
	float rate(const int *Base, const float *f) { return (*f) / (float)(*Base); }
private:

	//平面と半径の判定
	bool Judg_Plane_Rad(const D3DXVECTOR3 *Vec, const D3DXVECTOR3 *Pos, const float *Radius);


	// 点と直線の最短距離
	float calcPointLineDist(const D3DXVECTOR3 *p, const S_Line *l, D3DXVECTOR3 *h,float *t);
	// 鈍角判定
	bool isSharpAngle(const D3DXVECTOR3 *p1, const D3DXVECTOR3 *p2, const D3DXVECTOR3 *p3);
	// 点と線分の最短距離
	float calcPointSegmentDist(const D3DXVECTOR3 *p, const S_Line *l, D3DXVECTOR3 *h, float *t);
	// 平行関係
	bool isParallel(const D3DXVECTOR3 *v1, const D3DXVECTOR3 *v2);
	//  ベクトルに掛け算する係数
	D3DXVECTOR3 getPoint(const D3DXVECTOR3 *p, const D3DXVECTOR3 *v, const float *t);
	D3DXVECTOR3 getPoint(const S_Line *l, const float *t);
	// 2直線の最短距離
	float calcLineLineDist(const S_Line *l1, const S_Line *l2, D3DXVECTOR3 *p1, D3DXVECTOR3 *p2, float *t1, float *t2);
	// 0～1の間にクランプ
	void clamp01(float *v);
	// 2線分の最短距離
	float calcSegmentSegmentDist(const S_Line *l1, const S_Line *l2, D3DXVECTOR3 *p1, D3DXVECTOR3 *p2, float *t1, float *t2);
};

#endif // !Judgm_H

/*plus
#include"Judgment.h"

extern Judg *judg;
*/