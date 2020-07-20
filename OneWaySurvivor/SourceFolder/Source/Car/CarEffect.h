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
	// �\��
	void DrawCarEffect(const D3DXVECTOR3 *CameraPos);

	// �X�V����
	bool UpdateCarEffect(void);

	// �ǉ�
	void NewEffect(c_EffectBase *newEffect) { if (carEffectManager != nullptr)carEffectManager->NewEffect(newEffect); }
	void NewEffect(C_CarEffectManager *newEffect) { carEffectUpdateManager.push_back(newEffect); }

	// 
	void InitBall3D(void);
private:
	// �G�t�F�N�g�̊Ǘ�
	C_CarEffectManager *carEffectManager;
	std::vector<C_CarEffectManager*>carEffectUpdateManager;

	// �폜
	void DeleteCarEffect(void);
};