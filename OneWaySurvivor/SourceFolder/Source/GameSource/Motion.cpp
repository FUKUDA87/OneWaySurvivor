#include "Motion.h"
#include"../GameSource/Judgment.h"

Motion::Motion()
{
	CurSize = 0.0365f;
}

void Motion::CurveFloat(float * P, const float * A, const float * B, const float * C, const float * AnimeFlame)
{
	*P = pow((1.0f - *AnimeFlame), 2.0f)*(*A) +
		2 * (1.0f - *AnimeFlame)*(*AnimeFlame)*(*B) + pow(*AnimeFlame, 2.0f)*(*C);
}

void Motion::CurvePos(D3DXVECTOR3 * Pos, const D3DXMATRIX * Start_Mat, const D3DXVECTOR3 * PosV,
	const D3DXMATRIX * End_Mat, const float * AnimeFlame)
{
	CurveFloat(&Pos->x, &Start_Mat->_41, &PosV->x, &End_Mat->_41, AnimeFlame);
	CurveFloat(&Pos->y, &Start_Mat->_42, &PosV->y, &End_Mat->_42, AnimeFlame);
	CurveFloat(&Pos->z, &Start_Mat->_43, &PosV->z, &End_Mat->_43, AnimeFlame);
}

bool Motion::Formove(QuaForMove * CarFM, const CONSTITUTION * Con, std::vector<C_Ground_Object*> ground)
{
	Judg judg;

	bool OverFlg = false;//クォータニオンの1.0fを超えたときのFlg

	bool EndFlg = false;//クォータニオン終了Flg

	float VecSize, CurDrawSpeed = 1.0f;

	while (EndFlg != true) {
		//地面のナンバーと次のナンバー
		unsigned int GNo = Con->GroNum, NextGNo = GNo + 1;
		//AnimeFrameが1.0fを超えていた判定
		if (OverFlg == true) {
			//地面が有無確認
			if (ground.size() <= 0) {
				return false;
			}
			//レイ判定時のレイの長さ入れ用
			float Dis;
			//地面レイ判定
			bool JudgFlg = false;
			for (unsigned int g = 0; g < ground.size(); g++) {

				float L_Radius = 40.0f;
				//自分の周囲の地面だけを判定
				if (judg.BallJudg(&judg.SetPosM(&CarFM->NowMat),
					&judg.SetPosM(&ground[g]->GetMat()), &L_Radius) != true) continue;

				//レイ判定
				if (ground[g]->PolygonRayJudg(&Dis,&CarFM->NowMat,&D3DXVECTOR3(0.0f, -1.0f, 0.0f)))
				{

					//レイが当たった時の処理

					GNo = g;
					NextGNo = GNo + 1;
					JudgFlg = true;
					break;

				}

			}
			//判定
			if (JudgFlg == false) {
				//当たっていない
				return false;
			}
		}
		//次の地面の有無
		if (ground.size() - 1 < (unsigned int)(NextGNo)) {
			//無いとき
			return false;
		}
		bool CurInitFlg = false, CurveFlg = true;
		//地面の形
		unsigned int Type = ground[GNo]->GetWay().WayType;
		//初期化
		if (CarFM->QuaInitFlg == false) {
			//初期化した
			CarFM->QuaInitFlg = true;
			//Flg = true;
			D3DXVECTOR3 Vec;
			//カーブ判定Flg
			bool CurHeikinFlg = false;
			//カーブの速度調整判定
			if ((Type == 0) && (ground[NextGNo]->GetWay().WayType == 0)) {
				CurveFlg = false;
			}
			//カーブの判定
			if (CurveFlg == true) {
				float Ang;
				if (Type != 0) {
					Ang = ground[GNo]->GetWay().Ang;
				}
				else {
					Ang = 0.0f;
				}
				bool NoFlg = false;
				//カーブの探索
				for (unsigned int g = NextGNo; g < ground.size(); g++) {
					if ((ground[g]->GetWay().WayType == Type) || (Type == 0)) {
						Type = ground[g]->GetWay().WayType;
					}
					else {
						NextGNo = g;
						NoFlg = true;
						break;
					}
					if (Ang < 90.0f) {
						Ang += ground[g]->GetWay().Ang;
						if (Ang > 90.0f) {
							NextGNo = g - 1;
							NoFlg = true;
							break;
						}
					}
				}
				//見つからなかった時
				if (NoFlg == false) {
					return false;
				}
			}
			//カーブの速度調整
			if (Type != 0) {
				//カーブ
				CarFM->SpeedMul = 1.1f;
			}
			else {
				//ストレート
				CarFM->SpeedMul = 1.0f;
			}
			//startからendまでのVec計算
			judg.MatMatVec(&Vec, ground[GNo]->GetWay().StartMat, ground[NextGNo]->GetWay().StartMat);
			CarFM->WayVec = Vec;
			//ベジェ曲線の判定
			if (Type != 0) {
				CarFM->CurFlg = true;
				CurInitFlg = true;
			}
			else {
				CarFM->CurFlg = false;
			}
		}
		//startMatとendMatのセット
		if (CarFM->QuaMatInitFlg == false) {
			CarFM->StartMat = ground[GNo]->GetWay().StartMat;
			CarFM->EndMat = ground[NextGNo]->GetWay().StartMat;
			CarFM->QuaMatInitFlg = true;
		}
		//ベジェ曲線の計算
		if (CurInitFlg == true) {
			D3DXMATRIX Mat, MatE, RotX, RotY;
			D3DXVECTOR3 wVec = CarFM->WayVec / 2.0f, wPos;
			D3DXMatrixTranslation(&Mat, 0.0f, 0.0f, 0.0f);
			judg.TarEndMat(&MatE, Mat, &RotX, &RotY, CarFM->WayVec, D3DXVECTOR3(0.0f, 0.0f, 1.0f));
			judg.SetPosM(&wPos, &CarFM->StartMat);
			judg.SetMatP(&MatE, &(wPos + wVec));
			float Size = 0.0f, LR = 1.0f;
			if (Type == 1) {
				LR *= -1.0f;
			}
			D3DXVECTOR3 Vec;
			for (unsigned int i = GNo; i < NextGNo; i++) {
				judg.MatMatVec(&Vec, ground[i]->GetWay().StartMat, ground[i + 1]->GetWay().StartMat);
				Size += D3DXVec3Length(&Vec);
			}
			Size += D3DXVec3Length(&CarFM->WayVec);
			D3DXVec3TransformCoord(&CarFM->CurVec,
				&D3DXVECTOR3(CurSize*(float)(NextGNo - GNo)*Size*LR, 0.0f, 0.0f), &MatE);
		}
		//スピードの計算
		if (OverFlg == false) {
			if (CarFM->CurFlg == true) {//カーブ時にスピードを遅くする
				CurDrawSpeed = 0.8f;
			}
			else {
				CurDrawSpeed = 1.0f;
			}
			float Size = D3DXVec3Length(&CarFM->WayVec), NowSpeed = D3DXVec3Length(&Con->Speed)*CarFM->SpeedMulJudg;
			Size *= CarFM->SpeedMul;
			float Speed = NowSpeed * CurDrawSpeed / Size;
			CarFM->AnimeFrame += Speed;
		}
		else {
			//オーバー時の処理
			float wVec;
			wVec = D3DXVec3Length(&CarFM->WayVec);
			wVec *= CarFM->SpeedMul;
			wVec = VecSize / wVec;
			CarFM->AnimeFrame += wVec;
		}
		bool qeFlg = false;
		//オーバー時の計算
		if (CarFM->AnimeFrame > 1.0f) {
			D3DXVECTOR3 Vec;
			Vec = CarFM->WayVec;
			VecSize = D3DXVec3Length(&(Vec*CarFM->AnimeFrame - Vec));
			CarFM->AnimeFrame = 1.0f;
			OverFlg = true;
			qeFlg = true;
		}
		else {
			EndFlg = true;
		}
		//クォータニオン
		judg.AnimeProc(&CarFM->NowMat, CarFM->StartMat, CarFM->EndMat, CarFM->AnimeFrame);
		//ベジェ曲線のクォータニオン
		if (CarFM->CurFlg == true) {
			D3DXVECTOR3 Pos;
			CurvePos(&Pos, &CarFM->StartMat, &CarFM->CurVec, &CarFM->EndMat, &CarFM->AnimeFrame);
			judg.SetMatP(&CarFM->NowMat, &Pos);
		}
		//クォータニオンの終了処理
		if (qeFlg == true) {//前進
			CarFM->QuaInitFlg = false;
			CarFM->QuaMatInitFlg = false;
			CarFM->AnimeFrame = 0.0f;
		}

		//高さ処理
		D3DXMATRIX Tmp;
		D3DXMatrixTranslation(&Tmp, 0.0f, CarFM->BodyHeight, 0.0f);
		CarFM->NowMat = Tmp * (CarFM->NowMat);

		//終了処理
		if (EndFlg == true) break;

	}
	return true;
}

