#pragma once
#include"FadeMove.h"

class C_FadeIn :public C_FadeMove {
public:
	C_FadeMove* Action(bool *MoveFlg, bool *SceneChangeFlg, int *Alpha, int alphaUp);

};