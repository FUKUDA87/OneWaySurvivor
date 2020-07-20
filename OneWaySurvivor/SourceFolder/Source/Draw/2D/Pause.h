#pragma once
#include<d3dx9.h>
#include"../../Fade/FadeDraw.h"
#include"../../GameSource/Struct.h"

class Pause  
{
public:
	Pause();
	~Pause();

	//表示
	void Draw();
	//表示の有無Flg入れ
	void SetDFlg(bool Flg) {
		pau.Base.DrawFlg = Flg;
	}
	//表示の有無Flg渡し
	bool GetDFlg(void) {
		return pau.Base.DrawFlg;
	}

	//ステージセーブの有無Flg入れ
	void SetStaSavFlg(bool Flg) {
		StageSaveFlg = Flg;
	}
	//ステージセーブの有無Flg渡し
	bool GetStaSavFlg(void) {
		return StageSaveFlg;
	}
protected:
	CHARA2D pau;
private:
	//ステージの情報記録用Flg
	bool StageSaveFlg;

	C_FadeDraw *fadeDraw;
	int alpha;
	
};