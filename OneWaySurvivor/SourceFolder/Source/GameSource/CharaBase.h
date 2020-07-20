#pragma once
#include<d3dx9.h>
#include"Struct.h"
#include"../Const/Const_Damage.h"
#include"../Sound/vector/Sound_Data_Vector.h"
#include"../Draw/Hp/HpbarDraw.h"

class C_CharaBase:public C_Sound_Data_Vector {
public:
	C_CharaBase();
	~C_CharaBase();
	
	//死亡確認(trueで死)
	virtual bool Dead(void);
	//ダメージによるHp削り(今のHpが増減したらtrue)
	bool HpDamage(const int *Damage);
	//ダメージによるHp削り(今のHpが増減したらtrue)
	bool HpDamage(const int *DamageSetFlg, const int *Damage);

	//初期化１
	void Init_Hp(const int MaxHp, const int *DamageFlg);

	//ダメージを受けるFlgのセット
	void SetDamageFlg(const int *DamageFlg);

	//パーツのダメージを本体に与えるか決めるFlg
	int Get_Parst_DamageSet_Flg(void);

	//MaxHpの初期化
	void SetNowHp(const int *Hp);

	//構造体渡し
	CHARABASE GetCharaBase(void);

protected:

	C_HpbarDraw *Hpbar;

	//今のHp渡し
	int GetHp(void);

	//構造体代入
	void SetCharaBase(const CHARABASE *CharaBaseS);

	//MaxHpの初期化
	virtual void SetHp(const int *MaxHp);

	CHARABASE CharaBase;

	//ダメージを受けた時のFlg
	bool Body_DamageFlg;

	//ダメージを受けた時のFlgの判定
	void Judg_Body_DamageFlg(void);
private: 
	//初期化渡し
	CHARABASE GetInitAll(const int MaxHp, const int DFlg);
	//ダメージを受ける状態渡し
	bool GetDamageFlg(void);
	//構造体初期化
	CHARABASE GetInitCharaBase(void);
	//別の構造体代入
	void SetCharaBase(const STATUS* S);
};