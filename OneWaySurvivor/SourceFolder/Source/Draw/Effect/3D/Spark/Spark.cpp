#include "Spark.h"
#include"../../../../MaterialManager/TextureManager.h"
#include"../../../../GameSource/Judgment.h"

extern LPDIRECT3DDEVICE9		lpD3DDevice;
extern TextureManager textureManager;

#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


C_Spark::C_Spark(const D3DXMATRIX * Mat, const D3DXVECTOR3 * Pos)
{
	Init();
	//�p�x�̏�����
	spark.Base.Mat = *Mat;
	//X���̉�]�p�x�����߂�
	int Big = 3500,Small=-6000;
	Big = Big - Small;
	float Ang = (float)(rand() % Big + Small)/100.0f;
	//X��]�ƈړ��s��
	D3DXMATRIX Rot,Trans;
	//��]
	D3DXMatrixRotationX(&Rot, D3DXToRadian(Ang));
	//���炷
	D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, 0.15f);
	//�ʒu�̏�����
	Judg judg;
	judg.SetMatP(&spark.Base.Mat, Pos);
	spark.Base.Mat = Rot * Trans * spark.Base.Mat;
	//���̍s���������
	for (int p = 0; p < PNum; p++) {
		spark.m.Mat[p] = spark.Base.Mat;
	}
}

C_Spark::~C_Spark()
{
	//�|���S���\���p�̍폜
	if (spark.m.Mat != nullptr) {
		delete[] spark.m.Mat;
	}
}

void C_Spark::Init()
{
	//�ړ���Flg//�|���S�����̏�����
	PNum = 3;
	//�|���S���\���p��Mat�̏�����
	spark.m.Mat = new D3DXMATRIX[PNum];
	CarMoveFlg = false;
	//�摜�̃��[�h
	//�|���S���T�C�Y�̏�����
	PolSize = 0.015f;
	char TexName[100];
	sprintf_s(TexName, sizeof(TexName), "spark10-1.png");
	spark.Tex = textureManager.GetTexture(TexName, 300, 300, NULL);
	//�ړ��s��̏�����
	D3DXMatrixTranslation(&spark.Base.Mat, 0.0f, 0.0f, 0.0f);
	
	for (int p = 0; p < PNum; p++) {
		spark.m.Mat[p] = spark.Base.Mat;
	}

	//�\���̍s��
	D3DXMatrixIdentity(&IdenMat);

	//�ړ������̏�����
	yUp = 0.25f;
	yDown = -0.1f;
	zDown = -0.35f;

	//�����̏�����
	NowCount = 1 * 60;

}

bool C_Spark::Update(void)
{
	return UpdateSpark();
}

bool C_Spark::UpdateSpark(void)
{
	//��ړ��ƌ��ړ�
	D3DXMATRIX Tmp;
	D3DXMatrixTranslation(&Tmp, 0.0f, 0.0f, zDown);
	spark.Base.Mat = Tmp * spark.Base.Mat;
	spark.Base.Mat._42 += yUp;
	//�W�����v����
	if (yUp > 0.0f) {
		yUp += yDown;
	}
	else {
		yUp += yDown * 0.5f;
	}
	//�s��̍X�V
	for (int i = (PNum - 1); i > 0; i--) {
		spark.m.Mat[i] = spark.m.Mat[i - 1];
	}
	//�擪�Ɉ�ԐV�����s��̑��
	spark.m.Mat[0] = spark.Base.Mat;
	return CountUpdate();
}

bool C_Spark::Update(const D3DXVECTOR3 * CarMoveVec)
{
	////�ړ��ʂ����Ă����̂��̌v�Z
	//if (CarMoveFlg == true) {
	//	//�ԑ̂̈ړ��ʂ����Z
	//	judg.VecMatIn(&spark.Base.Mat, *CarMoveVec);
	//	for (int p = 0; p < PNum; p++) {
	//		judg.VecMatIn(&spark.PolMat[p], *CarMoveVec);
	//	}
	//}
	//else {
	//	CarMoveFlg = true;
	//}
	return true;
}

void C_Spark::Draw3DSpark(const D3DXVECTOR3 * CameraPos)
{
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDevice->SetFVF(FVF_VERTEX);//�o�O
	spark.v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	spark.v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	spark.v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	spark.v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	lpD3DDevice->SetTexture(0, spark.Tex);
	lpD3DDevice->SetTransform(D3DTS_WORLD, &IdenMat);
	for (int i = 0; i < (PNum - 1); i++) {
		//�r���{�[�h
		D3DXVECTOR3 vec, oPos, nPos;
		Judg judg;
		judg.SetPosM(&nPos, &spark.m.Mat[i]);
		judg.SetPosM(&oPos, &spark.m.Mat[i + 1]);
		vec = judg.Billboard(&oPos, &nPos, CameraPos, &PolSize);
		spark.v[0].Pos = nPos - vec;
		spark.v[1].Pos = nPos + vec;
		spark.v[2].Pos = oPos + vec;
		spark.v[3].Pos = oPos - vec;
		spark.v[0].Tex = D3DXVECTOR2(0.0f, (float)i / (float)(PNum - 1));
		spark.v[1].Tex = D3DXVECTOR2(1.0f, (float)i / (float)(PNum - 1));
		spark.v[2].Tex = D3DXVECTOR2(1.0f, (float)(i + 1) / (float)(PNum - 1));
		spark.v[3].Tex = D3DXVECTOR2(0.0f, (float)(i + 1) / (float)(PNum - 1));
		lpD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, spark.v, sizeof(VERTEX));//2�̓|���S����
	}
	lpD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	lpD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	lpD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

bool C_Spark::CountUpdate(void)
{
	//��b���炷
	NowCount -= 1;
	if (NowCount <=0) {
		//���Ԃ��o����
		NowCount = 0;
		return false;
	}
	return true;
}

void C_Spark::Draw3D(const D3DXVECTOR3 *CameraPos)
{
	Draw3DSpark(CameraPos);
}