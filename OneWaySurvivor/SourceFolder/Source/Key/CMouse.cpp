#include "CMouse.h"
#include"../MaterialManager/TextureManager.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// スプライト

extern HWND Hwnd;

void C_Mouse::Init()
{
	BasePt.x = 640;
	BasePt.y = 360;
	ClientToScreen(Hwnd, &BasePt);
	SetCursorPos(BasePt.x, BasePt.y);
}

C_Mouse::C_Mouse()
{
	static bool InitPosFlg = true;
	if (InitPosFlg == true) {
		Init();
		InitPosFlg = false;
	}
	DrawFlg = true;
	TouchFlg = false;
	Hand.TEX = { NULL,25,33 };
	Hand.TEX.Tex = textureManager.GetTexture("Hand2.png", Hand.TEX.Width, Hand.TEX.Height, NULL);
}

C_Mouse::C_Mouse(bool InitPosFlg)
{
	if (InitPosFlg == true) {
		Init();
	}
	DrawFlg = true;
	TouchFlg = false;
	Hand.TEX = { NULL,25,33 };
	Hand.TEX.Tex = textureManager.GetTexture("Hand2.png", Hand.TEX.Width, Hand.TEX.Height, NULL);
}

C_Mouse::~C_Mouse()
{
}

D3DXVECTOR2 C_Mouse::GetPt()
{
	POINT Pt;
	GetCursorPos(&Pt);
	ScreenToClient(Hwnd, &Pt);
	return D3DXVECTOR2((float)Pt.x,(float)Pt.y);
}

void C_Mouse::Draw2D()
{
	if (DrawFlg == true) {
		if (TouchFlg == false) {
			ChaFlg(true);
		}
		else {
			ChaFlg(false);
			RECT rcGa = { 0,0,Hand.TEX.Width, Hand.TEX.Height };
			D3DXVECTOR2 Pos = GetPt();
			D3DXMatrixTranslation(&Hand.Base.Mat, Pos.x, Pos.y,NULL);
			D3DXMatrixScaling(&Hand.Base.Scal, 0.6f, 0.55f, NULL);
			D3DXMATRIX Tmp = Hand.Base.Scal*Hand.Base.Mat;
			lpSprite->SetTransform(&Tmp);
			lpSprite->Draw(Hand.TEX.Tex, &rcGa, &D3DXVECTOR3((float)Hand.TEX.Width/4.0f, 0.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
		}
	}
}

bool C_Mouse::Update()
{
	if (DrawFlg == true) {
		TouchFlg = false;
	}
	return true;
}

bool C_Mouse::CamUpdate(float * AngX, float * AngY, float sen, int revUD, int revLR, bool IncFlg)
{
	//プラスか代入
	if (IncFlg == true) {
		//プラス
		POINT Pt;
		GetCursorPos(&Pt);
		*AngY += (Pt.x - BasePt.x) / sen * revUD;//int Flg2=1かー１で*Flg2;-1でリバース
		*AngX += (Pt.y - BasePt.y) / sen * revLR;//int Flg=1かー１で*Flg;;-1でリバース
		SetCursorPos(BasePt.x, BasePt.y);
	}
	else {
		//代入
		POINT Pt;
		GetCursorPos(&Pt);
		*AngY = (Pt.x - BasePt.x) / sen * revUD;//int Flg2=1かー１で*Flg2;-1でリバース
		*AngX = (Pt.y - BasePt.y) / sen * revLR;//int Flg=1かー１で*Flg;;-1でリバース
		SetCursorPos(BasePt.x, BasePt.y);
	}
	return true;
}

void C_Mouse::ChaFlg(bool mouseFlg)
{
	int c;
	c = ShowCursor(mouseFlg);
	if ((mouseFlg == true) && (c > 0)) {
		while (c>0)
		{
			c = ShowCursor(false);
		}
	}
	else {
		if ((mouseFlg == false) && (c < -1)) {
			while (c <-1)
			{
				c = ShowCursor(true);
			}
		}
	}
	return;
}

void C_Mouse::ChaDrawFlg(bool Flg)
{
	DrawFlg = Flg;
	ChaFlg(DrawFlg);
}

void C_Mouse::SetTouchFlg()
{
	TouchFlg = true;
}
