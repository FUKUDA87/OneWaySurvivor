#pragma once
#include"MeshDataManagerBase.h"

class C_CarDataManager :public C_MeshDataManagerBase {
public:
	//•\¦”‚Ì“Ç‚İ‚İ
	int GetDrawNum(int CarNo, bool SaveFlg);
	//•\¦İ’è‚Ì“Ç‚İ‚İ
	S_CAR_PARTS_DATA GetDrawSet(int CarNo, const int *DrawNo, bool SaveFlg);
protected:
private:
	//ŒŸõ•\¦”
	bool DrawNumJudg(int CarNo);
	//ŒŸõİ’è
	bool DrawSetJudg(int CarNo, const int *DrawNo);
};