#include "Debug.h"

extern LPD3DXFONT lpFontS;

Debug::Debug()
{
	debugFlg = false;
}

bool Debug::ChangeMode()
{
	if (debugFlg == false) {
		if ((key.SKey()) && (key.NKey()) && (key.TKeyF())) {
			debugFlg = true;
			UpFlg = DownFlg = LeftFlg = RightFlg = false;
			cnt = 0;
			return true;
		}
	}
	else {
		if ((key.SKey()) && (key.NKey()) && (key.TKeyF())) {
			debugFlg = false;
			return false;
		}
	}
	return false;
}

bool Debug::Update()
{
	ChangeMode();
	
	return debugFlg;
}

bool Debug::KeyUpdate()
{
	if (key.UPKeyF()) {
		UpFlg = true;
	}
	else {
		UpFlg = false;
	}
	if (key.DOWNKeyF()) {
		DownFlg = true;
	}
	else {
		DownFlg = false;
	}
	if (key.LEFTKeyF()) {
		LeftFlg = true;
	}
	else {
		LeftFlg = false;
	}
	if (key.RIGHTKeyF()) {
		RightFlg = true;
	}
	else {
		RightFlg = false;
	}
	return true;
}

void Debug::Draw()
{
	if (debugFlg == true) {
		RECT rcCon = { 0,0,0,0 };
		char TextB[200];
		sprintf_s(TextB, sizeof(TextB), "x:%f\ny:%f\nz:%f",debug.Mat._41, debug.Mat._42, debug.Mat._43);
		lpFontS->DrawTextA(NULL, TextB, -1, &rcCon, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
		//float
		RECT rcFlo = { 0,200,0,0 };
		//char TextB[200];
		sprintf_s(TextB, sizeof(TextB), "%f", fl);
		lpFontS->DrawTextA(NULL, TextB, -1, &rcFlo, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

D3DXMATRIX Debug::GetDebugMat()
{
	if (debugFlg == true) {
		if (UpFlg == true) {
			D3DXMATRIX Trans;
			D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, 0.0f);
			debug.Mat = Trans * debug.Mat;
		}
		if (DownFlg == true) {
			D3DXMATRIX Trans;
			D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, 0.0f);
			debug.Mat = Trans * debug.Mat;
		}
		if (LeftFlg == true) {
			D3DXMATRIX Trans;
			D3DXMatrixTranslation(&Trans, -0.5f, 0.0f, 0.0f);
			debug.Mat = Trans * debug.Mat;
		}
		if (RightFlg == true) {
			D3DXMATRIX Trans;
			D3DXMatrixTranslation(&Trans, 0.5f, 0.0f, 0.0f);
			debug.Mat = Trans * debug.Mat;
		}
	}
	
		Mat = debug.Mat;
	
	return debug.Mat;
}

void Debug::SetDebugMat(D3DXMATRIX mat)
{
	debug.Mat = mat;
}
