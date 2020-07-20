#pragma once
#include<d3dx9.h>
#include<dsound.h>
#include<string>
#include<map>
#include "wavread.h"
#include"Struct.h"

class SoundManager {
private:
	std::map<std::string, SoundCol>SoundList;
public:
	~SoundManager();
	void GetSound(SoundCol *Sound, std::string FileName);
	void AllDelete(void);
};