#pragma once
#include<d3dx9.h>
#ifndef KEY_H
#define KEY_H

class Key{
public:
	Key() { Init(); };
	~Key() {};
	//trueでキー操作不能
	void SetFlg(bool Flg) {
		KeyAllFlg = Flg;
	}
	void Init(void) {
		KeyAllFlg = false;
	}
	//Aキー
	bool AKey();
	//Aキー+KeyFlg
	bool AKeyF();
	//Wキー
	bool WKey();
	//Wキー+KeyFlg
	bool WKeyF();
	//Sキー
	bool SKey();
	//Sキー+KeyFlg
	bool SKeyF();
	//Dキー
	bool DKey();
	//Dキー+KeyFlg
	bool DKeyF();
	//左クリック
	virtual bool LClick();
	//左クリック+KeyFlg
	virtual bool LClickF();
	//右クリック
	virtual bool RClick();
	//右クリック+KeyFlg
	bool RClickF();
	//Nキー
	bool NKey();
	//Nキー+KeyFlg
	bool NKeyF();
	//Tキー
	bool TKey();
	//Tキー+KeyFlg
	bool TKeyF();
	//Cキー
	bool CKey();
	//Cキー+KeyFlg
	bool CKeyF();
	//ENTERキー
	bool RETURNKey();
	//ENTERキー+KeyFlg
	bool RETURNKeyF();
	//UPキー
	bool UPKey();
	//UPキー+KeyFlg
	bool UPKeyF();
	//DOWNキー
	bool DOWNKey();
	//DOWNキー+KeyFlg
	bool DOWNKeyF();
	//LEFTキー
	bool LEFTKey();
	//LEFTキー+KeyFlg
	bool LEFTKeyF();
	//RIGHTキー
	bool RIGHTKey();
	//RIGHTキー+KeyFlg
	bool RIGHTKeyF();
	//Zキー
	bool ZKey();
	//Zキー+KeyFlg
	bool ZKeyF();
	//Eキー
	bool EKey();
	//Eキー+KeyFlg
	bool EKeyF();
	//Yキー
	bool YKey();
	//Yキー+KeyFlg
	bool YKeyF();
	//Fキー
	bool FKey();
	//Fキー+KeyFlg
	bool FKeyF();
	//Xキー
	bool XKey();
	//Xキー+KeyFlg
	bool XKeyF();
	//Gキー
	bool GKey();
	//Gキー+KeyFlg
	bool GKeyF();

	//エスケープキー
	bool EscapeKey();
	bool EscapeKey_S();
	bool EscapeKey_F();

	/*
	Num
	*/

	//1+長押し封じ
	bool Num1_Key_F(void);

	//7
	bool Num7Key();
	//8
	bool Num8Key();
	//9
	bool Num9Key();
protected:
	bool KeyAllFlg;
private:
	static bool EscapeFlg;
};

#endif // !KEY_H

/*グローバルで宣言
#include"h+cpp/Key.h"
Key *key;
*/
/*cppで宣言
#include"Key.h"

extern Key *key;
*/