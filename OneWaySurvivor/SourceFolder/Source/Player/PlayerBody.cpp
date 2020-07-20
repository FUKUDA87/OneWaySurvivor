#include "PlayerBody.h"

C_PlayerBody::C_PlayerBody()
{
	//ロード
	if (fopen_s(&fp_b,"../GameFolder/Data/PlayerData/PlayerBodyData.dat","rb") == 0) {
		fread(&pData, sizeof(BODYDATA), 1, fp_b);
		fclose(fp_b);
	}
	else {
		//ロードできない時
		Save();
	}
}

C_PlayerBody::~C_PlayerBody()
{
	
}

void C_PlayerBody::Save(void)
{
	//txtロード
	
	if (fopen_s(&fp,"../GameFolder/Data/PlayerData/PlayerBodyData.txt","r") == 0) {
		fscanf_s(fp, "%d ", &pData.CarBodyNo);
		fscanf_s(fp, "%d ", &pData.TireNo);
		fscanf_s(fp, "%d ", &pData.StandNo);
		fscanf_s(fp, "%d ", &pData.GunNo);
		fclose(fp);
	}
	else {
		pData.CarBodyNo = CarNo1;
		pData.TireNo = TireNo1;
		pData.StandNo = StandNo1;
		pData.GunNo = 1;
	}
	//txtセーブ
	if (fopen_s(&fp,"../GameFolder/Data/PlayerData/PlayerBodyData.txt","w") == 0) {
		fprintf_s(fp, "%d ", pData.CarBodyNo);
		fprintf_s(fp, "%d ", pData.TireNo);
		fprintf_s(fp, "%d ", pData.StandNo);
		fprintf_s(fp, "%d ", pData.GunNo);
		fclose(fp);
	}
	////datセーブ
	//if (fopen_s(&fp_b,"../GameFolder/Data/PlayerData/PlayerBodyData.dat","wb") == 0) {
	//	fwrite(&pData, sizeof(PLAYERBODYDATA), 1, fp_b);
	//	fclose(fp_b);
	//}
}

void C_PlayerBody::Save2(void)
{
	//txtロード

	//txtセーブ
	if (fopen_s(&fp,"../GameFolder/Data/PlayerData/PlayerBodyData.txt","w") == 0) {
		fprintf_s(fp, "%d ", pData.CarBodyNo);
		fprintf_s(fp, "%d ", pData.TireNo);
		fprintf_s(fp, "%d ", pData.StandNo);
		fprintf_s(fp, "%d ", pData.GunNo);
		fclose(fp);
	}
	//datセーブ
	if (fopen_s(&fp_b, "../GameFolder/Data/PlayerData/PlayerBodyData.dat","wb") == 0) {
		fwrite(&pData, sizeof(BODYDATA), 1, fp_b);
		fclose(fp_b);
	}
}

void C_PlayerBody::SetPData(const BODYDATA * Data)
{
	pData = *Data;
	Save2();
}
