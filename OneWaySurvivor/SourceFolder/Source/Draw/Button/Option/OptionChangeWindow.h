#pragma once
#include<d3dx9.h>
#include"SoundVolumeChange.h"
#include<vector>
#include"../../2D/Draw2DBase.h"

class C_OptionChangeWindow
{
public:
	C_OptionChangeWindow(const int *BGMVolume, const int *SEVolume);
	~C_OptionChangeWindow();

	// �\��
	void Draw2D(void);

	// �X�V����
	bool Update(const bool *KeyFlg, int *BGMVolume, int *SEVolume);

private:
	std::vector<C_SoundVolumeChange*>volumeChange;

	C_Draw2DBase *window;
};