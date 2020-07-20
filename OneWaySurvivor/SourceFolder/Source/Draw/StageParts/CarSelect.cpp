#include "CarSelect.h"
#include"../../MaterialManager/TextureManager.h"

extern TextureManager textureManager;
extern LPD3DXSPRITE lpSprite;	// �X�v���C�g

C_CarSelect::C_CarSelect(const D3DXVECTOR2 * PosA, const D3DXVECTOR2 * ScalA, const D3DXVECTOR2 * ArrScal, const D3DXVECTOR2 * ArrTransPos, const D3DXVECTOR2 * ScalNum)
{
	//������
	InitCS();
	//�ʒu�̃Z�b�g
	Back.Base.Pos = *PosA;
	Back.Base.ScaPos = *ScalA;

	if (ArrNum > 0) {
		for (int a = 0; a < ArrNum; a++) {
			Arr[a].ScaPos = *ArrScal;
			Arr[a].TraPos = *ArrTransPos;
		}
	}
	//���̏�����
	Num = new C_Num2DA(PosA, ScalNum);
}

C_CarSelect::~C_CarSelect()
{
	//�폜
	delete[] Arr;

	if (Num != nullptr) {
		delete Num;
	}
}

void C_CarSelect::InitCS(void)
{
	No = 0;

	//���̏�����------------------------------------------------------------------------------
	ArrNum = 2;
	//�g��
	Arr = new BASE2D[ArrNum];
	//�摜�̃��[�h
	ArrTex = { NULL,150,148 };
	ArrTex.Tex = textureManager.GetTexture("Arr2-2.png", ArrTex.Width, ArrTex.Height, NULL);

	//Back�̏�����-----------------------------------------------------------------------------
	//�摜�̃��[�h
	Back.TEX = { NULL,928,552 };
	Back.TEX.Tex = textureManager.GetTexture("frame1to.png", Back.TEX.Width, Back.TEX.Height, NULL);

}

void C_CarSelect::Draw2DCS(void)
{
	//Back�̕\��-------------------------------------------------------------------------
	D3DXMATRIX TmpMat;
	RECT rcBack = { 0,0, Back.TEX.Width, Back.TEX.Height };

	//�ʒu�Ɗg��̃Z�b�g
	judg.setScalingMat(&Back.Base.Scal, &Back.Base.ScaPos);
	judg.setTransMat(&Back.Base.Mat, &Back.Base.Pos);
	//�s��̍���
	TmpMat = Back.Base.Scal*Back.Base.Mat;
	//�\��
	lpSprite->SetTransform(&TmpMat);
	lpSprite->Draw(Back.TEX.Tex, &rcBack, &D3DXVECTOR3((float)Back.TEX.Width / 2.0f, (float)Back.TEX.Height / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//

	//���̕\��-------------------------------------------------------------------------
	RECT rcArr = { 0,0, ArrTex.Width, ArrTex.Height };

	for (int a = 0; a < ArrNum; a++) {
		//�ʒu�Ɗg��̃Z�b�g
		judg.setScalingMat(&Arr[a].Scal, &Arr[a].ScaPos);
		D3DXVECTOR2 tmpPos=Arr[a].TraPos;
		if (a == 1)tmpPos *= -1.0f;//�ړ��̔��]
		judg.setTransMat(&Arr[a].Trans, &tmpPos);
		//�摜�̉�]�s��쐬
		float AngZ = 0;
		if (a == 1)AngZ = 180;
		D3DXMatrixRotationZ(&Arr[a].RotZ, D3DXToRadian(AngZ));
		//�s��̍���
		TmpMat = Arr[a].RotZ*Arr[a].Trans*Back.Base.Mat;
		TmpMat = Arr[a].Scal*TmpMat;
		//�\��
		lpSprite->SetTransform(&TmpMat);
		lpSprite->Draw(ArrTex.Tex, &rcArr, &D3DXVECTOR3((float)ArrTex.Width / 2.0f, (float)ArrTex.Height / 2.0f, 0.0f), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));//
	}
}

void C_CarSelect::Draw2DAll(void)
{
	Draw2DCS();
	if (Num != nullptr) {
		Num->Draw2D(&No);
	}
}

int C_CarSelect::Touch(void)
{
	if (ArrNum <= 1)return 0;
	//����
	if (judg.PlaneCri(&(Back.Base.Pos + Arr[0].TraPos), &Arr[0].ScaPos, &ArrTex.Width, &ArrTex.Height) == true)return 1;
	if (judg.PlaneCri(&(Back.Base.Pos - Arr[1].TraPos), &Arr[1].ScaPos, &ArrTex.Width, &ArrTex.Height) == true)return 2;
	return 0;
}

bool C_CarSelect::UpdateNo(const int * MeshNo)
{
	No = *MeshNo;
	return true;
}