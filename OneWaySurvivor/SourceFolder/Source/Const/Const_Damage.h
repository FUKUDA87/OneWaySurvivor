#pragma once
#include<d3dx9.h>

/*ダメージを受ける方法*/

const int Co_Damage_No = 0;//ダメージを受けない
const int Co_Damage_Yes = 1;//ダメージを受ける
const int Co_Damage_No_Parts = 2;//ダメージを受けないが他が受ける
const int Co_Damage_Yes_Parts = 3;//他からのみダメージを受ける

/*当たった物体の種類*/

const int Hit_Type_Player = 1;
const int Hit_Type_Enemy = 2;
const int Hit_Type_Wall = 3;
const int Hit_Type_Ground = 4;
const int Hit_Type_EnemyBoss = 5;

/*レイの方向*/

const int Const_Left = 0;
const int Const_Middle = 1;
const int Const_Right = 2;
const int Const_Previous = 0;
const int Const_Back = 2;

/*判定状況*/

//判定しない
const int Co_Judge_NO = 0;

//判定する
const int Co_Judge_YES = 1;

//ボスの判定
const int Co_Judge_BOSS = 2;