#pragma once
#include<d3dx9.h>
#include<stdio.h>
#include"../Struct.h"

class C_Option
{
public:
	// データの読み込み
	void Read(void);
	
	// データの書き込み
	void Write(void);

	// データの変更
	void Change(void);

	// データの渡し
	S_OptionData GetOptionData(void) { return optionData; }

	// データ入れ
	void setOptionData(const S_OptionData *data) { optionData = *data; }

	// データの初期化
	void InitData(void);

private:
	S_OptionData optionData;
};