#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"


class C_EnemySelect {
public:
	BODYDATACar GetEnemy(const int EnemyNo);
protected:

private:
	//パーツデータ
	BODYDATACar eData;
	//検索判定用
	bool GetEnemyJudg(const int EnemyNo);

	//敵１
	bool GetEnemy1(const int EnemyNo);
	//敵１
	bool GetEnemyBoss1(const int EnemyNo);
};