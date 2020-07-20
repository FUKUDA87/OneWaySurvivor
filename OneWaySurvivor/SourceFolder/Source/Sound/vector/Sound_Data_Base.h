#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class C_Sound_Data_Base {
public:

	C_Sound_Data_Base(const S_SOUND_DATA *Set_Data);

	//î•ñ“n‚µ
	S_SOUND_DATA Get_Data(void) {
		return M_S_Data;
	}

	//ƒƒjƒ…[‚Ì•ÏX
	void Change_Menu(void) {
		if (M_S_Data.Change_Type < 0)M_S_Data.Change_Type *= -1;
	}
protected:

private:
	S_SOUND_DATA M_S_Data;
};