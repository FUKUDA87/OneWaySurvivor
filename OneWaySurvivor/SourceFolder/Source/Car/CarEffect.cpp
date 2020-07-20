#include "CarEffect.h"
#include"../Draw/Effect/Car/Smoke/CarSmoke.h"

C_CarEffect::C_CarEffect()
{
	carEffectManager = new C_CarEffectManager();

	carEffectUpdateManager.push_back(new c_CarSmoke());
}

C_CarEffect::~C_CarEffect()
{
	DeleteCarEffect();
	
	if (carEffectManager != nullptr)delete carEffectManager;
}

void C_CarEffect::DrawCarEffect(const D3DXVECTOR3 *CameraPos)
{
	if (carEffectUpdateManager.size() > 0)
	{
		for (auto && em : carEffectUpdateManager)em->Draw3D(CameraPos);
	}

	if (carEffectManager != nullptr)carEffectManager->Draw3D(CameraPos);
}

bool C_CarEffect::UpdateCarEffect(void)
{
	// 更新に必要な情報作成
	s_CarEffectUpdateData updateData;
	updateData.CharaBase = CharaBase;
	updateData.CarNo = BodyData.CarBodyNo;
	updateData.Mat = Car.Base.Mat;
	updateData.MoveVec = brj.MoveVec;
	updateData.ScalMat = Car.Base.Scal;
	updateData.Scal = Car.Base.ScaPos;

	// 更新
	if (carEffectUpdateManager.size() > 0)
	{
		for (unsigned int emc = 0; emc < carEffectUpdateManager.size(); emc++) {
			if (carEffectUpdateManager[emc]->Update(&updateData) != true) {
				delete carEffectUpdateManager[emc];
				carEffectUpdateManager.erase(carEffectUpdateManager.begin() + emc);
				emc--;
			}
		}
	}

	if (carEffectManager != nullptr)carEffectManager->Update(&updateData);

	return true;
}

void C_CarEffect::InitBall3D(void)
{
	/*bool flg = false;
	S_Capsule c = GetCapsule(&flg);

	NewEffect(new C_Ball3DVec(&c.vs, &c.r, 1.0f));
	NewEffect(new C_Ball3DVec(&c.ve, &c.r, 1.0f));*/
}

void C_CarEffect::DeleteCarEffect(void)
{
	if (carEffectUpdateManager.size() < 1)return;

	//全て削除
	for (unsigned int ec = 0; ec < carEffectUpdateManager.size(); ec++) {
		delete carEffectUpdateManager[ec];
		carEffectUpdateManager.erase(carEffectUpdateManager.begin() + ec);
		ec--;
	}
}

