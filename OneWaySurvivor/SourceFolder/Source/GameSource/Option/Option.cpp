#include "Option.h"

FILE *fp_b;

void C_Option::Read(void)
{
	// ì«Ç›çûÇ›
	if (fopen_s(&fp_b, "../GameFolder/Data/OptionData/OptionData.dat", "rb") == 0) {
		fread(&optionData, sizeof(S_OptionData), 1, fp_b);
		fclose(fp_b);
	}
	else {
		// èâä˙âª
		InitData();

		// êVãKçÏê¨
		Write();
	}
}

void C_Option::Write(void)
{
	// èëÇ´çûÇ›
	if (fopen_s(&fp_b, "../GameFolder/Data/OptionData/OptionData.dat", "wb") == 0) {
		fwrite(&optionData, sizeof(S_OptionData), 1, fp_b);
		fclose(fp_b);
	}
}

void C_Option::Change(void)
{

}

void C_Option::InitData(void)
{
	optionData.BGMVolume = 0;
	optionData.SEVolume = 0;
	optionData.sensitivity = 4.0f;
	optionData.reverseLR = false;
	optionData.reverseUD = false;
}
