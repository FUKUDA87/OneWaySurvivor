#pragma once
#include"PlayerBase.h"
#include"../GameSource/PartsTrans.h"


class C_PlayerA :public C_PlayerBase {
public:
	C_PlayerA();
	C_PlayerA(const BODYDATA *Data);
	~C_PlayerA();

	//車のボディの更新
	void SetBody(const BODYDATA *Data);
protected:
	//初期化
	virtual void InitPlayerA(void);


	void SaveCar(void);
private:
	//パーツの初期化ロードした情報を入手してパーツを構成
	//virtual void InitPlayerAB(void);
};