#pragma once
#include<d3dx9.h>
#include<vector>
#include"Ground_Object.h"
#include"../GameSource/Count/Countdown.h"
#include"../GameSource/Count/Count.h"
#include"../Player/PlayerBase.h"
#include"Stage_Ground/Ground_Pop_New.h"

class c_GroundManager
{
public:
	c_GroundManager(C_PlayerBase *player);
	~c_GroundManager();

	// �\��
	void Draw3D(void);

	// �X�V����
	bool Update(C_PlayerBase *player);

	// �n�ʂ̓����蔻��
	bool JudgNowGround(unsigned int *GroundNumber, float *Dis, bool *HitCurveGround, const D3DXMATRIX *Mat);

	// ���H�̌`��ύX
	void SetGroundPop(const int *RoadNo);

	// �Ԃ̏o���̏��쐬
	void InitCarPopData(unsigned int *gNo, D3DXMATRIX *GroundMat, float *TransX,
		const unsigned int *playerGroundNum, const S_CAR_INIT_DATA *Data);

	// �e�Ɠ����蔻��
	void BulletJudg(BULLETJUDGDATA * BJD, const RAYDATA *RD, bool *HitFlg, const float *Rad);

	// ������J�����O
	void FrustumCulling(const S_Frustum_Vec * FV_Data);

	// �ǂƋ�����
	bool CapsuleJudgWall(float *SmallDis,int *hitNum, s_CarType * HitCar, const S_Capsule *c, const s_CarType * JudgCar);

	std::vector<C_Ground_Object*> GetGround(void) { return ground; }

	unsigned int GetGroundNum(void) { return ground.size(); }
	D3DXMATRIX GetGroundMat(const unsigned int* count) { return ground[*count]->GetMat(); }

	unsigned int GetWallNum(const unsigned int* gc) { return ground[*gc]->GetWallNum(); }
	D3DXMATRIX GetWallMat(const unsigned int* gc, const unsigned int *wc) { return ground[*gc]->GetWallMat(wc); }
	S_Capsule GetCapsuleWall(const unsigned int* gc, const unsigned int *wc) { return ground[*gc]->GetCapsuleWall(wc); }
	bool MeshRayJudgWall(float *Dis, const D3DXVECTOR3 *Pos, const D3DXVECTOR3 *Ray, const unsigned int* gc, const unsigned int * wc);

private:
	//�n�ʂ̃����o
	std::vector<C_Ground_Object*>ground;
	Cou *cou;//bill
	std::vector<Cou*>GroCou;
	//�O���\���p�J�E���g�_�E��
	C_Count *LightCount;

	/*�n�ʂ̏��*/
	C_Ground_Pop_New* M_C_Ground_Pop;
};