#include "MoveCur.h"

void MoveCur::RailC(D3DXMATRIX *mat,float f)
{
	D3DXMATRIX tmp;
	D3DXMatrixTranslation(&tmp, 0.1f*f, 0, 0);
	*mat= (*mat)*tmp;
}

void MoveCur::Curve(CHARA3D *chara)
{
	/*if (chara->Base.AngY == true) {
		float AngY;
		AngY = 1.0;
		if (chara->Con.CurLFlg == true) {
			AngY = -AngY;
		}
		if (chara->Con.CurFlg == false) {
			if ((chara->Base.AngY < PAng) && (chara->Base.AngY > -PAng)) {
				D3DXMATRIX TmpMat;
				D3DXMatrixRotationY(&TmpMat, D3DXToRadian(AngY));
				chara->Base.Mat = TmpMat * chara->Base.Mat;
				chara->Base.AngY += AngY;
			}
			else {
				chara->Con.CurFlg = true;
			}
		}
		if (chara->Con.CurFlg == true) {
			if (((int)chara->Base.AngY) != 0) {
				if (chara->Base.AngY < 0) {
					Ang = +Ang;
				}
				else {
					Ang = -Ang;
				}
				D3DXMATRIX TmpMat;
				D3DXMatrixRotationY(&TmpMat, D3DXToRadian(Ang));
				player.Base.Mat = TmpMat * player.Base.Mat;
				player.Base.AngY += Ang;
			}
			else {
				player.Con.CurLFlg = false;
				player.Con.CurRFlg = false;
				player.Con.CurFlg = false;
				if (player.Con.PEFlg == false) {
					player.Con.NowRail = player.Con.NextRail;
				}
				else {
					player.Con.PEFlg = false;
				}
			}
		}
	}*/
}
