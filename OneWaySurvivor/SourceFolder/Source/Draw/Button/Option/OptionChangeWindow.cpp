#include "OptionChangeWindow.h"

C_OptionChangeWindow::C_OptionChangeWindow(const int * BGMVolume, const int * SEVolume)
{
	window = new C_Draw2DBase("frame1to.png", 928, 552, &D3DXVECTOR2(1280.0f / 2.0f, 720.0f / 2.0f), &D3DXVECTOR2(0.6f, 0.6f));

	float y = 70.0f;
	D3DXVECTOR2 p = window->getPos();
	p.y -= y;
	volumeChange.push_back(new C_SoundVolumeChange(true, &p, BGMVolume));

	p = window->getPos();
	p.y += y;
	volumeChange.push_back(new C_SoundVolumeChange(false, &p, SEVolume));


}

C_OptionChangeWindow::~C_OptionChangeWindow()
{
	if (window != nullptr)delete window;

	if (volumeChange.size() <= 0)return;

	for (unsigned int vc = 0; vc < volumeChange.size(); vc++)
	{
		delete volumeChange[vc];
		volumeChange.erase(volumeChange.begin() + vc);
		vc--;
	}
}

void C_OptionChangeWindow::Draw2D(void)
{
	if (window != nullptr)window->Draw2D();

	if (volumeChange.size() <= 0)return;

	for (auto && v : volumeChange)v->Draw2D();
}

bool C_OptionChangeWindow::Update(const bool * KeyFlg, int * BGMVolume, int * SEVolume)
{
	if (volumeChange.size() <= 0)return false;

	for (unsigned int vc = 0; vc < volumeChange.size(); vc++)
	{
		if (vc > 0)
		{
			volumeChange[vc]->Update(KeyFlg,SEVolume);
		}
		else {
			volumeChange[vc]->Update(KeyFlg,BGMVolume);
		}
	}

	return true;
}
