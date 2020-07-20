#pragma once
#include<d3dx9.h>
#include<dsound.h>

//#ifndef Struct_H
//#define Strcut_H

//XFILE�̍\����
struct XFILE 
{
	LPD3DXMESH lpMesh;//���b�V���̌`��̃f�[�^
	DWORD NumMaterial;//�O���[�v�̐�
	D3DMATERIAL9 *Mat;//�}�e���A���̓��ex�O���[�v��
	LPDIRECT3DTEXTURE9 *Tex;//�e�N�X�`���̓��ex�O���[�v��
};
//VERTEX�̍\����
struct VERTEX
{
	D3DXVECTOR3 Pos;
	D3DCOLOR Color;
	D3DXVECTOR2 Tex;
};
//TEXTURE�̍\����
struct TEXTURE 
{
	LPDIRECT3DTEXTURE9 Tex;
	int Width, Height;
};

//�\����3D�̍\����
struct  BASE3D {
	D3DXMATRIX Mat, Trans,Rot, RotX, RotY, RotZ, Scal,DrawMat;
	D3DXVECTOR3 Pos,ScaPos,TraPos;
	double AngX, AngY, AngZ;
	bool Flg, DrawFlg, UpdateFlg;//���݂̃I���ƃI�t
	float AttRad,BodRad;//�����蔻��̔��a
	bool MoveFlg;//�����Ă��邩�ǂ���
};
//�\����2D�̍\����
struct  BASE2D {
	D3DXMATRIX Mat, Trans, RotZ, Scal;
	D3DXVECTOR2 Pos,ScaPos,TraPos;
	D3DXVECTOR3 Pos2D;
	float AngZ;
	bool Flg,DrawFlg,UpdateFlg;//���݂̃I���ƃI�t
	bool MFlg;//�����Ă��邩�ǂ���
};
//�L�����̊�{���
struct CHARABASE {
	int MaxHp, NowHp;//Hp
	int DamageSetFlg;//�_���[�W���󂯂�Flg
	int HitFlg;//�_���[�W���󂯂����Ƃ̊m�FFlg
};
//�X�e�[�^�X�̍\����
struct STATUS {
	CHARABASE CharaBase;
	//int NowLevel, MaxLevel;
	//float Attack, Defense, Critical;//�U���͂Ǝ���͂Ɖ^
};

struct S_MeshData
{
	DWORD NumVertex;               // ���_��
	D3DXVECTOR3 BigVec, SmallVec;  //�@BigVec=�傫�����_�ʒu�ASmallVec=���������_�ʒu
};

//XFILE2
struct XFILE_B
{
	XFILE Mesh;
	S_MeshData Data;
};

//�R�̃��b�V��
struct XFILE3
{
	XFILE DrawMesh;//�\���p���f��
	XFILE_B ColMod;//����p���f��
	XFILE DeadMesh;//����p���f��
};

//�Q�[���V�X�e���̏��̍\����
struct CONSTITUTION {
	D3DXVECTOR3 Speed;//�X�s�[�h
	int NowSpeed,MaxSpeed;
	bool CurFlg;//�Ԑ��ύX���̔���
	bool CurLFlg;//�Ԑ��ύX���̍��L�[�ݒ�
	bool CurRFlg;//�Ԑ��ύX���̉E�L�[�ݒ�
	bool DFlg;//�G�̍U������t���O
	bool PEFlg;//�G�Ǝ��@���Փ˃t���O
	unsigned int GroNum;//���̒n��
	D3DXMATRIX JudgMat;//�ԑ̂̕����𓾂邽�߂�Mat
};

//���̕�3D�̍\����
struct Object3D {
	XFILE Mesh;
	BASE3D Base;
};

// �\��
struct S_Base3D_2 {
	BASE3D Base;
	float CullingRad;//�J�����O�p���a
};

//�L�����N�^�[3D�̍\����
struct CHARA3D {
	XFILE3 Mesh;
	BASE3D Base;
	STATUS Sta;
	CONSTITUTION Con;
};

//�摜2D�̍\����
struct CHARA2D {
	TEXTURE TEX;
	BASE2D Base;
};

// �����̔|���S���̕\���s��
struct PolygonMatrix
{
	D3DXMATRIX *Mat;  // �����̍s��
	int Num;          // �s��
};

//�|���S���l�p�`�̍\����
struct S_Polygon 
{
	VERTEX v[4];
	LPDIRECT3DTEXTURE9 Tex;
	BASE3D Base;
	PolygonMatrix m;
};
//���̏��
struct Way
{
	int WayType;//�ԓ��̌^
	bool Cur;//�J�[�u�̎ԓ�����
	float Ang;
	D3DXMATRIX StartMat;//�N�H�[�^�j�I���p�̎n�_Mat
	int RailNum;//�Ԑ��̐�
	float *CurTransX;//�Ԑ��̏�����Ԃ̉��ړ�Mat
};
struct judgDeta {
	D3DXMATRIX Mat;
	float Rad;
	int Hp;
	int MaxHp;
};
struct QuaAnim {
	D3DXMATRIX EndMat, StartMat,NowMat,RotX,RotY,RotZ,RotA,Trans;
	float Ang;
	float AnimeFrame,FrameUp,Reverse;//Reverse��1.0f��-1.0f
	D3DXVECTOR3 Pos, Vec,StartPos,EndPos;
	bool MoveFlg,ReverseFlg;
	int Count, CountEnd;
};
struct QuaAnim2D {
	D3DXMATRIX EndMat, StartMat, NowMat, RotX, RotY, RotZ, RotA, Trans;
	float Ang;
	float AnimeFrame, FrameUp, Reverse;//Reverse��1.0f��-1.0f
	D3DXVECTOR2 Pos, Vec, StartPos, EndPos;
	bool MoveFlg, ReverseFlg;
	int Count, CountEnd;
};
struct QuaMove {
	float SpeB;
	//int Qup;//�N�H�[�^�j�I���p��Mat[�ϐ�]
	bool qFlg, qGFlg, cFlg;
	unsigned int GroNo;
	D3DXMATRIX StartMat, EndMat;
};
struct EnemyPop {
	int MaxNum;//�ő�o����
	int rePopTime[10];//�G�������܂ł̎���
	int EneNumber[10];//�G�̎��
};
struct CHARAData {
	D3DXMATRIX NowMat,StartMat,EndMat;
	float Rad;
	int Speed;
	unsigned int NowGround;
	bool GroundFlg,DrawFlg,CurFlg;
	LPD3DXMESH Mesh;
};

struct CLONEVERTEX {
	D3DXVECTOR3 Pos;//���W
	D3DXVECTOR3 Normal;//�@��
	D3DXVECTOR2 Tex;//�e�N�X�`�����W
};
struct QuaForMove{
	D3DXMATRIX NowMat, StartMat, EndMat;
	float AnimeFrame, BodyHeight,SpeedMul,SpeedMulJudg;
	bool QuaInitFlg,QuaMatInitFlg,CurFlg;
	D3DXVECTOR3 WayVec, CurVec;
};
//�v���C���[�ȊO�̃X�s�[�h�Ǘ��\����
struct SpeedMove {
	float NowSpeedMul, SpeedUp,MaxSpeed,StopSpeed;
};
//�T�E���h�p�J�����\����
struct SoundCamera {
	D3DXVECTOR3 CamPos, CamLook, CamHead;
};
//���b�V���̃T�C�Y
struct SizePos {
	D3DXVECTOR3 Big, Small;
};
//�T�E���h�\����
struct SoundCol {
	LPDIRECTSOUNDBUFFER8 Sound;
	LPDIRECTSOUND3DBUFFER8 Sound3D;
};
//�N�H�[�^�j�I���A�j���[�V����
struct QuaAnimeC {
	D3DXMATRIX NowMat, StartMat, EndMat;
	float NowAnime, AnimeFrame;
};
//�|���S���p�N�H�[�^�j�I��
struct PolQuaAni
{
	QuaAnimeC Qac;
	//�����x
	int Alpha,AlphaMax;
	float PolSizeNow, PolSizeMax,PolSizeSmall;
};

//�p�[�c�p�N���X
struct S_CAR_PARTS_DATA {
	D3DXVECTOR3 TransPos,Ang;//�ړ��A�p�[�c�ɂȂ���p,��]�p
	int MeshTypeNo;//���b�V�����
	int MeshJointNo;//���b�V���̎�ނ̒��̔ԍ�
};
struct ObjectParts {
	BASE3D Base;
	D3DXMATRIX SuperMat;
};
//�o���b�g�p
struct BULLETRAYJUDG 
{
	D3DXVECTOR3 MoveVec;//�Ԃ̈ړ���
	D3DXVECTOR3 RayPos;//���C�����������ʒu
	bool JudgRayFlg;//���C������������
};

struct QUAMAT {
	D3DXMATRIX RotXMat, RotYMat;
};
//�G�̏e��]�p
struct GUNAI {
	BASE3D NowBase;
	//��]�N�H�[�^�j�I��
	QUAMAT Start, End;
	float NowAnime, AnimeFrame;
	//�e�̓�����Flg
	bool GunMoveFlg;

	//���C����t���O
	bool RayJudgFlg;

	//���C������������
	int RayCountNow,RayCountInit;

	//�_�����W
	D3DXVECTOR3 TragetPos;

	//���ː�
	int BulletNum;

	//����Flg
	bool BulletFlg;

	//���ˌ�̔��˃^�C�~���O
	int BulletCount;

	//���ˌ�̋x�e
	int GunCount;

	//�S�Ă̍H���I��
	bool EndFlg;

	//�����t���s��
	D3DXMATRIX ConnectMat;

	//AIFlg
	bool AIFlg;

	//��]�I��Flg
	bool GunMoveEndFlg;

	//���C�̒���
	float RayDis;
};

//�v���C���[�̎ԑ̏��
struct BODYDATA {
	int CarBodyNo;
	int TireNo;
	int StandNo;
	int GunNo;
};
//�v���C���[�̎ԑ̏��
struct BODYDATAFLG {
	bool CarBodyBulletFlg;
	bool CarBodyAttackFlg;
	bool TireBulletFlg;
};
//�ԑ̏��
struct BODYDATACar {
	BODYDATA Body;
	D3DXVECTOR3 ScalPos;
	int MaxHp;
	BODYDATAFLG JudgFlg;//�����蔻��̃_���[�W����Flg
	int EnemyNo;
};
//�e�̕\�����
struct S_GUN_DRAW_NO {
	int GunNo;
	int BulletNo;
	int MuzFlaNo;
	int LaserNo;
};
//�e�̏��
struct GUNDATA {
	BASE3D Base;
	XFILE Mesh;
	//���[�U�[�n�_�ƏI�_
	D3DXVECTOR3 LaserPos_Start,LaserPos_End;
	//���[�U�[����ƃ��[�U�[����̋���
	bool HitRayFlg, JudgRayFlg;
	//���[�U�[�̒���
	float LaserSize;
	//�\���̏��ۊ�
	S_GUN_DRAW_NO DrawNo;
};
struct Object3DGun {
	float AngX, AngY, AngZ;
	D3DXVECTOR3 TransPos, ScalPos;
	bool DrawFlg;
};
//�e�̏��������
struct GUNINITDATA {
	S_GUN_DRAW_NO DrawNo;//�\�����
	CHARABASE  CharaBase;//hp�̃Z�b�g
	float LaserSize;//���C�̒���
	Object3DGun InitGun;
	
};
struct GETGUNDATA {
	int TexNo;
	int MeshNo;
	D3DXVECTOR3 MeshScalPos;
	int PolNum;
	float PolSize;
	int InitCountMax;
	D3DXMATRIX Mat;
	float Speed;
};

// �o�����Ă���Ԃ̏��
struct s_CarType
{
	int Type;
	unsigned int Numbar[3];
};

//�e����p
struct BULLETJUDGDATA {
	s_CarType JudgType;
	s_CarType HitType;
	float SamllDis;//���C�̍ŏ��̒����ۊ�
};
//���C����
struct RAYDATA {
	D3DXMATRIX Mat;
	D3DXVECTOR3 Ray;
};
struct S_ENEMYGUNDATA {
	S_GUN_DRAW_NO DrawNo;
	Object3DGun Gun;
	CHARABASE Hp;
	D3DXVECTOR3 TargetPos;
	int NowPhase;
	QUAMAT NowRot;
	D3DXMATRIX StandMat,TransMat;
	//���C
	bool RayJudgFlg, RayHitFlg;
	float RayDis;
	//���˃t���O
	bool BulletFlg;
	bool LaserFlg;
	//�^�[�Q�b�g�ɏƏ��������Ċ���������
	bool LockonEndFlg;
};

struct S_ENEMYBODYDATA {
	BODYDATA Body;
	D3DXVECTOR3 ScalPos;
	float GroundHeight;
	CHARABASE CharaBase;
};

struct S_TEXPOS {
	int x;
	int y;
};
struct S_Random {
	int x, y, z;
};
//���̕\�������p�\����
struct S_Smoke
{
	//�ړ������x�N�g��
	D3DXVECTOR3 MoveVec;
	//�ړ��̃t���[����
	D3DXVECTOR3 Frame;
	//�����x�̕ϐ�
	int Alpha, AStart, ADown;
	//�|���S���̃T�C�Y
	float PolSize,PolBit,PolBitUp;
	//�ړ��ʂ̕ω�
	S_Random Random;
};
//�\���̍\����
struct S_DrawBase {
	//
	D3DXMATRIX Mat;
	D3DXVECTOR3 Pos,TransPos,ScalPos;
	float AngX, AngY, AngZ;
};
//��]�s��
struct S_DrawRotMat {
	D3DXMATRIX X, Y, Z;
};

//�e�̃x�[�X�\����
struct S_BULLET {
	int Damage;
	float Speed;
};

struct S_POL_DATA {
	//�\���|���S����
	int PolNum;
	//�e���_
	D3DXVECTOR3 Pos[4];
	//����
	float Size;
};



//�e�̏��
struct S_BULLET_DATA {
	int DrawType;
	S_BULLET BULLET;
	int TexNo, MeshNo;
};

struct S_GUN_UPDATE_DATA {
	//�蓮
	D3DXMATRIX CameraMat;
	/*����*/
	D3DXVECTOR3 TargetPos;
	//�L����
	int NowPhase;
	//�X�^���h
	D3DXMATRIX StandMat;
	//�{�̂̏��
	bool Gun_Stop_Flg;
};

struct S_BULLET_DEPAR {
	//�e�̔��˃��[�h
	int Bullet_Gun_Mode;//1���e���A�Q�����ˉ񐔁A�R���b���B
	int Count_Departure;//123�̉񐔂̃Z�b�g
};

struct S_GUN_DATA {
	//�\������
	S_DrawBase DrawBase;
	S_DrawRotMat RotMat;
	
	//�^�[�Q�b�g�ɏƏ��������Ċ���������
	bool LockonEndFlg;
	//�L����
	float ScalSize;

	/*���[�U�[*/
	//���[�U�[�̕\���t���O
	bool LaserDrawFlg;
	//���[�U�[�̒���
	float RayDis;
	//���C����t���O
	bool Ray_Hit_Flg;
	bool Ray_Judg_Flg;

	/**/
	//���˃t���O
	bool BulletFlg;

	//���˂����e��
	int Departure_Num;

	//�v���C���[�����삷�邩Flg
	bool PlayerFlg;

	//���̕\���̉�]
	QUAMAT NowRot;

	//������Flg
	bool MoveFlg;

	//�e�̎��������̎��̍\����
	S_BULLET_DEPAR Depar;

	//���[�g�̊m�F
	bool RateFlg;
};

struct S_PARTS_DATA {
	D3DXVECTOR3 JointPos;
};

struct S_GUN_INIT_DATA {

};

struct S_CategoryNo {
	//a=Car.Gun,b=GunNo1.GunNo2
	int a, b;
};

//�\���RD��
struct S_DRAW3D_DATA {
	//�\���̃^�C�v(Pol,Mesh,Pol+Mesh)
	S_CategoryNo Draw3DType;
	//Texture�̃i���o�[
	int TextureNo;
	//���b�V���̃i���o�[
	int MeshNo;
};

//���C����̌��ʂ̍\����
struct S_RayHitJudgData {
	//���C��������������
	bool Flg;
	//���C�����������ʒu
	D3DXVECTOR3 HitPos;
};

//�e�̏������̏��n��
struct S_BULLET3D_INIT_DATA {
	/*�e�̕\��*/
	S_DRAW3D_DATA Draw3D_Data;

	/*�e�̓���*/

	/*�v���C���[�̏ꍇ*/
	S_RayHitJudgData RayHitData;

	/*�G�̏ꍇ*/

};

//�|���S���\���̏�����
struct S_PolMat_INIT {
	int PolNum;
	int TexNo;
	D3DXMATRIX Mat;
	float PolSize;
};

//�e�̃p�[�c�̃f�[�^
struct S_Gun_Parts_Data {
	//�e�������Ƃ��ł���Flg
	bool BulletFlg;
	//�e�̒��S���痣�ꂽ�Ƃ���̍��W
	D3DXVECTOR3 TarnsPos;
	//�e��
	D3DXVECTOR3 MouthPos;
	//���[�g
	int Rate;
	//�eNo
	int BulletNo;
	//�J�e�S���[��
	int CategoryNo;
	//�u���x�ƃ~���T�C�Y
	int Bure, BureSura;

};

//�F,�n��
struct S_COLOR {
	int r, g, b;
};

struct S_TEX_POS {
	int Width, Height;
};

struct S_TEX_DRAW_DATA
{
	S_TEX_POS Pos;
	S_COLOR Color;
};

struct S_GAGE {
	int Now, Max;
};

//�p�[�c�̃i���o�[���Ǘ�
struct S_PARTS_SET_DATA_No {
	int MeshTypeNo;//���b�V�����
	int MeshJointNo;//���b�V���̎�ނ̒��̔ԍ�
};

//�p�[�c�̏����Z�b�g
struct S_PARTS_SET_DATA {
	int MeshTypeNo;//���b�V�����
	int MeshJointNo;//���b�V���̎�ނ̒��̔ԍ�
	int DrawNo;//�\�����
};

//�p�[�c�̃T�C�Y���Z�b�g
struct S_PARTS_SET_SIZE {
	S_PARTS_SET_DATA_No No;
	D3DXVECTOR3 ScalPos;
};

//�Ԃ̏��������
struct S_CAR_INIT_DATA {
	//�o������Ԃ̔ԍ�
	int CarNo;
	//�Ԑ��ԍ�
	int WayNo;
	//�v���C���[���猩���ԍ�
	unsigned int GroundNo;
	//�Ԃ̎��(�G,��ʎ�)
	int CarType;

};

//�n�ʂ̏��������
struct S_GROUND_INIT_DATA {
	int gType;
	float Ang;
	float Length;
	bool LengthAuto;
};

//�X�e�[�W�̏��
struct S_STAGE_DATA {
	int Stage_Num;
};

//�G�̃f�[�^
struct S_ENEMY_DATA {
	bool CarFlg;
	int Phase_Now;
	bool BossFlg;//�{�X�m�F
};

//���݂̃E�F�[�u�̏��
struct S_NOW_WAVE_DATA {
	int WaveType_Now;//���̃E�F�[�u�̏��
	int Enemy_Alive_Num;//�G�̐�����
};

//���̌����Ə������̏��
struct S_SOUND_DATA {
	//2D��3D
	int Sound_Type;
	//���
	int Sound_CategoryNo;
	//CategoryNo�̒��̎��
	int Sound_No;
	//���̈ʒu
	D3DXVECTOR3 Pos;
	//���̕ύX�̏��
	int Change_Type;
};

//���[�h�ύX
struct S_MODE_CHANGE {
	int Now, Change;
};

//�J�����̏��
struct S_CAMERA_POS {
	D3DXVECTOR3 Pos, Look, Head;
};

//������̖@���̍\����
struct S_Frustum_Vec 
{
	D3DXVECTOR3 nt, nb, nl, nr;
	D3DXVECTOR3 cameraPos;
};

// �I�v�V�����̍\����
struct S_OptionData
{
	int BGMVolume;
	int SEVolume;
	float sensitivity;          // ���x
	bool reverseLR, reverseUD;  // ���E���]�E�㉺���]
};

// �Ԃ̃G�t�F�N�g�̍X�V�ɕK�v�ȏ���
struct s_CarEffectUpdateData
{
	CHARABASE CharaBase;
	int CarNo;
	D3DXMATRIX Mat,ScalMat;
	D3DXVECTOR3 MoveVec,Scal;
};

// AI�̃X�s�[�h�X�V���
struct s_AISpeedUpdateData
{
	bool AliveFlg;// �����t���O
	unsigned int NowGroNo;// ������ł���n�ʂ̔ԍ�
	int NowPhase;// ���݂̃t�F�[�Y
	int TargetSpeed;// ���̎Ԃ̃X�s�[�h
	unsigned int TargetGroNo;// ���̎Ԃ̃X�s�[�h
	bool UpdateStopFlg;
};

// ����
struct S_Line
{
	D3DXVECTOR3 s, e, v;  //�n�_�A�I�_�A�x�N�g��
};

// �J�v�Z��
struct S_Capsule
{
	S_Line l;
	float r;// ���a
	D3DXVECTOR3 vs, ve;// �n�_�I�_�̏������x�N�g��
};

// ������ł�ΉԂ̏��
struct S_SideSparkData
{
	s_CarType type[2];  // ����������
	D3DXMATRIX initMat;  // �ΉԂ̏o���ʒu
	int firstJudgType;    // �ŏ��ɉ����肵�Ă����
};

//#endif // !Struct_H