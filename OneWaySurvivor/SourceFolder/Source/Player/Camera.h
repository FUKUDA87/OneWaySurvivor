#pragma once
#include<d3dx9.h>
#include"../Key/CMouse.h"
#include"../Ground/GroundManager.h"

#ifndef Camera_H
#define Camera_H


class Camera{
public:
	void Init();
	Camera();
	Camera(D3DXMATRIX PlayerMat);
	~Camera();
	//TPS用Update
	virtual bool UpdateM(bool MouFlg);
	virtual bool UpdateM(bool MouFlg,C_Mouse *mouse);
	virtual bool Update(D3DXMATRIX mat);
	//クォータニオンのアップデート
	virtual bool UpdateQua(const bool *KeyFlg,const D3DXMATRIX *PlayerMat);
	D3DXVECTOR3 GetLook();
	D3DXVECTOR3 GetPos();
	float GetSize(D3DXVECTOR3 Pos, D3DXVECTOR3 Look);
	float GetAngX() { return camAngX; };
	float GetAngY() { return camAngY; };
	D3DXVECTOR3 GetVec();
	//カメラ位置を入れ
	void SetCamPos(const D3DXVECTOR3 *Pos) {
		camPos = *Pos;
	}
	void SetAngY(float y) {
		camAngY = y;
	}
	void SetAngX(float x) {
		camAngX = x;
	}

	//カメラの行列渡し
	D3DXMATRIX GetMat(void);

	//クォータニオンのフラグ渡し
	bool GetQuaFlg(void) {
		return QuaFlg;
	}

	//クォータニオンのセット
	void SetQuaMat(const D3DXMATRIX *EndQuaRotXMat, const D3DXMATRIX *EndQuaRotYMat, const float *QuaFrameUp);
	//X回転渡し
	D3DXMATRIX GetRotX(void) {
		return CamRotX;
	}
	//X回転入れ
	void SetRotX(const D3DXMATRIX *RotX) {
		CamRotX = *RotX;
	}
	//Y回転渡し
	D3DXMATRIX GetRotY(void) {
		return CamRotY;
	}
	//Y回転入れ
	void SetRotY(const D3DXMATRIX *RotY) {
		CamRotY = *RotY;
	}
	void RotXJudg(const D3DXMATRIX *PlayerMat);

	// 壁と当たり判定
	void WallJudg(const int *RadF,c_GroundManager *groundManager);

protected:
	D3DXVECTOR3 camPos, camLook;
	float camAngY, camAngX;
	float camSize, Big, Small;
	D3DXMATRIX CamMat,CamRotX,CamRotY;
	//前方に向くクォータニオン
	float Anime, FrameUp;
	bool QuaFlg;
	D3DXMATRIX StartRotXMat,EndRotXMat, StartRotYMat, EndRotYMat;
	//マウスのインクリメントFlg
	bool IncFlg;

private:
	// カメラを車正面に向ける処理
	void InitCarCameraMove(const bool *KeyFlg, const D3DXMATRIX *PlayerMat);
};

#endif // !Camera_H
