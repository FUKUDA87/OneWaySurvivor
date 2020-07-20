#include "OptionChange.h"
#include"OptionButton.h"
#include"../../../GameSource/Judgment.h"

C_OptionChange::C_OptionChange(const int * BGMVolume, const int * SEVolume)
{
	button = new C_OptionButton;

	modeChangeFlg = false;

	changeWindow = new C_OptionChangeWindow(BGMVolume, SEVolume);
}

C_OptionChange::~C_OptionChange()
{
	if (button != nullptr)delete button;
	if (changeWindow != nullptr)delete changeWindow;
}

void C_OptionChange::Draw2D(void)
{
	if (button != nullptr)button->Draw2D();
	
	if (modeChangeFlg == true) 
	{
		if (changeWindow != nullptr)changeWindow->Draw2D();
	}
}

bool C_OptionChange::Update(const bool * KeyFlg, int * BGMVolume, int * SEVolume)
{
	if (button != nullptr)
	{
		button->Update(nullptr);

		if (*KeyFlg == true)
		{
			Judg judg;
			if (button->TouchJudg())judg.ReverseFlg(&modeChangeFlg);
		}
	}

	if (modeChangeFlg == true)
	{
		if (changeWindow != nullptr)changeWindow->Update(KeyFlg, BGMVolume, SEVolume);
	}

	return true;
}
