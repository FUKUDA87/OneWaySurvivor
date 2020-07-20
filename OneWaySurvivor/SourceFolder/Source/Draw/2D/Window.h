#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include"../../MaterialManager/TextureManager.h"
#include"../../GameSource/Judgment.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト

#define	SCRW		1280	// ウィンドウ幅（Width
#define	SCRH		720		// ウィンドウ高さ（Height

class Window 
{
public:
	Window();
	~Window() {};
	void Draw2D();
	bool GetMoveFlg(void) {
		return MoveFlg;
	}
	void SetMoveFlg(bool Flg);
	bool Update();

	void DrawSu() {
		Draw2D();
	};
	bool UpdateSu() {
		Update();
	};
protected:
	CHARA2D wind;
	D3DXVECTOR3 TexPos;//textureのPos
	//クォータニオン
	bool MoveFlg;
	QuaAnim2D qua;
	Judg judg;
};