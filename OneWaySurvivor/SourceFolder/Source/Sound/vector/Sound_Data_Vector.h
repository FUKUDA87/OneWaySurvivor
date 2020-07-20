#pragma once
#include"Sound_Data_Base.h"
#include<vector>
#include"../../Const/Const_Sound_Type.h"

class C_Sound_Data_Vector {
public:
	~C_Sound_Data_Vector();

	//î•ñ“n‚µ
	S_SOUND_DATA Get_Sound_Data(const unsigned int *No);

	//î•ñ”“n‚µ
	unsigned int Get_Sound_Data_Num(void);

	//íœ
	void Delete_Sound(unsigned int *No);

	//V‹K
	void New_Sound_Data(const S_SOUND_DATA *Set_Data);
	void New_Sound_Data(const int *Type,const int *Category,const int No,const int *Change);
	void New_Sound_Data(const int *Category, const int No,const D3DXVECTOR3* Pos, const int *Change);
	void New_Sound_Data_Change_No(const int *Type, const int *Category, const int No, const int *Change);

	//‘S‚Ä‚Ì•ÏX“à—e‚ğ•ÏX‚·‚é
	void Change_Menu_All(void);

protected:

private:
	std::vector<C_Sound_Data_Base*>M_C_Data;
};