#pragma once
#include"CarBase.h"
#include"../Draw/Effect/Car/CarEffectManager.h"
#include"../Draw/Effect/Car/Ball/Ball3DVec.h"

class C_CarEffect:public C_CarBase
{
public:
	C_CarEffect();
	~C_CarEffect();
protected:
	// 表示
	void DrawCarEffect(const D3DXVECTOR3 *CameraPos);

	// 更新処理
	bool UpdateCarEffect(void);

	// 追加
	void NewEffect(c_EffectBase *newEffect) { if (carEffectManager != nullptr)carEffectManager->NewEffect(newEffect); }
	void NewEffect(C_CarEffectManager *newEffect) { carEffectUpdateManager.push_back(newEffect); }

	// 
	void InitBall3D(void);
private:
	// エフェクトの管理
	C_CarEffectManager *carEffectManager;
	std::vector<C_CarEffectManager*>carEffectUpdateManager;

	// 削除
	void DeleteCarEffect(void);
};