#include "Car_Pop_Base.h"

C_Car_Pop_Base::C_Car_Pop_Base():Car_PopNo(0)
{
	M_Car_Pop_EndFlg = false;
	M_Car_Pop_Flg=false;

	//ê∂ê¨Ç≥ÇÍÇÈínñ ÇÃèâä˙âª
	M_Ground_Type = 0;

	Init_Stage_Data();
}

C_Car_Pop_Base::~C_Car_Pop_Base()
{
	Delete_All_Car();
}

void C_Car_Pop_Base::New_Car_Data(const int CarType,const int CarNo,const int Count, const unsigned int GroundNo, const int WayNo)
{
	S_CAR_INIT_DATA Data;

	Data.CarNo = CarNo;
	Data.CarType = CarType;
	Data.GroundNo = GroundNo;
	Data.WayNo = WayNo;

	M_Car_Data.push_back(new C_Car_Pop_Data(&Data, &Count));
}

void C_Car_Pop_Base::New_Car_Data(const int CarType, const int CarNo, const int Count, const unsigned int GroundNo)
{
	New_Car_Data(CarType, CarNo, Count, GroundNo, Co_Rail_Type_Random);
}

bool C_Car_Pop_Base::Update_Car_Count(void)
{
	if (M_Car_Pop_EndFlg != false)return false;

	if (M_Car_Data.size() < 1)return false;

	if (M_Car_Data[Car_PopNo]->Update_Count() != false) {
		M_Car_Pop_Flg = true;
	}

	return false;
}

void C_Car_Pop_Base::Delete_All_Car(void)
{
	if (M_Car_Data.size() < 1)return;

	for (unsigned int d = 0; d < M_Car_Data.size(); d++) {
		delete M_Car_Data[d];
		M_Car_Data.erase(M_Car_Data.begin() + d);
		d--;
	}
}

void C_Car_Pop_Base::Init_Stage_Data(void)
{
	M_Stage_Data.Enemy_Alive_Num = 0;
	M_Stage_Data.WaveType_Now = Co_Wave_Type_Normal;
}

S_CAR_INIT_DATA C_Car_Pop_Base::Get_Next_Car_Data(void)
{

	if(M_Car_Data.size()<1)return S_CAR_INIT_DATA();

	return M_Car_Data[Car_PopNo]->Get_Data();
}

bool C_Car_Pop_Base::Get_Car_Pop_Flg(void)
{
	if (M_Car_Data.size() < 1)return false;

	if (M_Car_Pop_EndFlg == true)return false;

	return M_Car_Pop_Flg;
}

void C_Car_Pop_Base::Car_Init_Rear(void)
{
	M_Car_Pop_Flg = false;

	if (M_Car_Data.size() < 1)return;

	delete M_Car_Data[Car_PopNo];
	M_Car_Data.erase(M_Car_Data.begin() + Car_PopNo);

	if (M_Car_Data.size() < 1)New_All_Pop();
	
}
