#pragma once
#include"FadeIn.h"

class C_FadeOut :public C_FadeMove {
public:
	C_FadeOut();

	C_FadeMove* Action(bool *MoveFlg, bool *SceneChangeFlg, int *Alpha, int alphaUp);

private:
	int CountNum;
};