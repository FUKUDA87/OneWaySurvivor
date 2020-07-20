#include "SideSparkData.h"
#include"../../Const/Const_Damage.h"

C_SideSparkData::~C_SideSparkData()
{
	if (data.size() <= 0)return;

	for (unsigned int dc = 0; dc < data.size(); dc++)
	{
		delete data[dc];
		data.erase(data.begin() + dc);
		dc--;
	}
}

void C_SideSparkData::NewData(const s_CarType * judg, const s_CarType * hit,const D3DXMATRIX *initMat, const int * firstJudgType)
{
	if (*firstJudgType == Hit_Type_Wall)return;

	// ŒŸõ
	if (data.size() > 0)
	{
		for (auto && d : data)
		{
			if (JudgCarType(&d->type[0], judg) && JudgCarType(&d->type[1], hit) ||
				JudgCarType(&d->type[1], judg) && JudgCarType(&d->type[0], hit))
			{

				d->initMat = *initMat;
				return;
			}
		}
	}

	// ’Ç‰Á
	data.push_back(new S_SideSparkData());
	data[data.size() - 1]->type[0] = *judg;
	data[data.size() - 1]->type[1] = *hit;
	data[data.size() - 1]->initMat = *initMat;
	data[data.size() - 1]->firstJudgType = *firstJudgType;
}

void C_SideSparkData::deleteData(unsigned int * c)
{
	delete data[*c];
	data.erase(data.begin() + (*c));
	*c -= 1;
}

bool C_SideSparkData::JudgCarType(const s_CarType * t1, const s_CarType * t2)
{
	if (t1->Type != t2->Type)return false;

	for (int i = 0; i < 3; i++)
	{
		if (t1->Numbar[i] != t2->Numbar[i])return false;
	}
	
	return true;
}
