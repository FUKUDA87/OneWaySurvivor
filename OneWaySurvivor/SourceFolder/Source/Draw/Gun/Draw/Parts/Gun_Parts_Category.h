#pragma once
#include<d3dx9.h>

class C_Gun_Parts_Category {
public:
	C_Gun_Parts_Category(const int *set_CategoryNo);

	//更新
	bool Update(void);

	//弾を撃つ渡し
	bool Get_Bullet_Shot_Flg(void);

	//今のレート数渡し
	int Get_NowRate(void) {
		return NowRate;
	}

	//今のレート数に入れる
	void Set_NowRate(const int *Rate) {
		NowRate = *Rate;
	}

	//カテゴリー数渡し
	int Get_CategoryNo(void) {
		return CategoryNo;
	}

	//動きの渡し
	float Get_Move_f(void) {
		return Move_f;
	}

	//動きの入れ
	void Set_Move_f(const float *Flg) {
		Move_f = *Flg;
	}

	//動きの渡し(0が停止、1が動作中、２が動作完了)
	int Get_MoveFlg(void) {
		return MoveFlg;
	}

	//引き金渡し
	bool Get_TriggerFlg(void) {
		return TriggerFlg;
	}

	//引き金の入れ
	void Set_TriggerFlg(const bool *Flg) {
		TriggerFlg = *Flg;
	}

protected:
	//今のレート回数
	int NowRate;

	//カテゴリーNo
	int CategoryNo;

	//動きFlg(0以下が無動,0以上が動作,1以上が動作完了)
	float Move_f;

	//動きのFlg(0が無動、1が動作中、２が動作完了)
	int MoveFlg;
	//引き金
	bool TriggerFlg;
private:
	//カテゴリー数入れ
	void Set_CategoryNo(const int *No) {
		CategoryNo = *No;
	}

	//初期化
	void Init_C_Gun_Parts_Category(void);

	//動きの判定
	void Judg_MoveFlg(void);

	//動きのFlgの入れ
	void Set_MoveFlg(const int Flg) {
		MoveFlg = Flg;
	}
};