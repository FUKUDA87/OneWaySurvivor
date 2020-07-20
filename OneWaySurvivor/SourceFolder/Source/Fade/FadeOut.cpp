#include "FadeOut.h"

C_FadeOut::C_FadeOut()
{
	CountNum = 50;
}

C_FadeMove * C_FadeOut::Action(bool * MoveFlg, bool *SceneChangeFlg, int * Alpha, int alphaUp)
{
	if (*MoveFlg == true) {
		*Alpha += alphaUp;
		if (*Alpha >= 255) {
			*Alpha = 255;
			CountNum -= 1;
			if (CountNum <= 0) {
				*MoveFlg = false;
				*SceneChangeFlg = true;
				return new C_FadeIn();
			}
		}
	}
	return nullptr;
}
