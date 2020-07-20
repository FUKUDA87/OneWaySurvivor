#include "FadeIn.h"

C_FadeMove * C_FadeIn::Action(bool * MoveFlg, bool *SceneChangeFlg, int * Alpha, int alphaUp)
{

	if (*MoveFlg == true) {
		*Alpha -= alphaUp;
		if (*Alpha <= 0) {
			*Alpha = 0;
			*MoveFlg = false;
			return new C_FadeNoMove();
		}
	}
	return nullptr;
}
