#pragma once
#include<d3dx9.h>

const int Co_Sound_Type_2D = 1;
const int Co_Sound_Type_3D = 2;

const int Co_Sound_Category_Bullet = 1;
const int Co_Sound_Category_BGM = 2;
const int Co_Sound_Category_Warning = 3;
const int Co_Sound_Category_Click = 4;
const int Co_Sound_Category_Explosion = 5;
const int Co_Sound_Category_Bullet_Hit= 6;

// サウンドの命令
const int Co_SoundNew = 1;  // 追加
const int Co_SoundDelete = 2;  // 一部削除
const int Co_SoundStart = 3; // 一部再生
const int Co_SoundStop = 4; // 一部停止
const int Co_SoundDeleteAll = 5; // 全削除
const int Co_SoundStartAll = 6; // 全再生
const int Co_SoundStopAll = 7; // 全停止