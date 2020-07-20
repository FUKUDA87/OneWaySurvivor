#include "CarSideHitSpark.h"
#include"../../../../MaterialManager/TextureManager.h"
#include"../../../../GameSource/Judgment.h"

extern TextureManager textureManager;

C_CarSideHitSpark::C_CarSideHitSpark(const D3DXMATRIX * InitMat, const bool * InitFlg)
{
	//�摜�̃��[�h
	int SparkType;
	if ((rand() % 15) != 1) 
	{
		SparkType = 3;
		PolSize = 0.015f;
	}
	else {
		SparkType = 6;
		//�|���S���T�C�Y�̏�����
		PolSize = 0.01f;
	}
	char TexName[100];
	sprintf_s(TexName, sizeof(TexName), "Spark1-9-%d.png", SparkType);
	Tex = textureManager.GetTexture(TexName, 300, 300, NULL);

	//�|���S���̏�����
	PolNum = 3;
	PolMat = new D3DXMATRIX[PolNum];

	//�ړ������̏�����
	yDown = -0.005f;
	zDown = -(float)(rand() % (20 - 5) + 5) / 10.0f;

	//�p�x�̏�����
	Mat = *InitMat;
	//X���̉�]�p�x�����߂�
	int Big = 6000, Small = -6000;
	Big = Big - Small;
	float Ang = (float)(rand() % Big + Small) / 100.0f;
	yUp = Ang / 100.0f*0.5f;
	yDown = yUp / 10.0f;
	if (yDown > 0.0f)yDown *= -1.0f;
	//���ݎ��Ԃ̌v�Z
	if (Ang < -3000.0f)count->setNowCount(3);
	if (Ang > -3000.0f)count->setNowCount(6);
	if (Ang > 0.0f)count->setNowCount(20);
	if (Ang > 3000.0f)count->setNowCount(30);
	if (*InitFlg == true)count->setNowCount(1);
	//X��]�ƈړ��s��
	D3DXMATRIX Rot, Trans;
	//��]�Ƃ��炵
	float AngY;// , zMove;
	AngY = (float)(rand() % 50) / 10.0f;
	if ((rand() % 2) == 1)AngY *= -1.0f;
	//zMove = 0.15f;
	D3DXMatrixRotationY(&Rot, D3DXToRadian(AngY));
	//���炷
	//D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, zMove);
	//�ʒu�̏�����
	Mat = Rot /** Trans*/ * Mat;
	//���̍s���������
	for (int p = 0; p < PolNum; p++) PolMat[p] = Mat;
	
	for (int i = 0; i < PolNum; i++) {
		//��ړ��ƌ��ړ�
		D3DXMATRIX Tmp;
		D3DXMatrixTranslation(&Tmp, 0.0f, 0.0f, zDown);
		Mat = Tmp * Mat;
		Mat._42 += yUp;
		//�W�����v����
		yUp += yDown;
		//�s��̍X�V
		for (int i = (PolNum - 1); i > 0; i--) PolMat[i] = PolMat[i - 1];
		PolMat[0] = Mat;
	}
}
