#include "SoundManager.h"

extern LPDIRECTSOUND8 lpDSound;	//DirectSoundオブジェクト
void LoadWAVE3D(LPDIRECTSOUNDBUFFER8 &pDSData, LPDIRECTSOUND3DBUFFER8 &pDSData3D, const char *fname);

SoundManager::~SoundManager()
{
	AllDelete();
}

 void SoundManager::GetSound(SoundCol *Sound, std::string FileName)
{
	 if ((SoundList.find(FileName)==SoundList.end())) {
		 LPDIRECTSOUNDBUFFER8 pDSDataTZ;
		 LPDIRECTSOUND3DBUFFER8 pDSData3DTZ;
		 LoadWAVE3D(pDSDataTZ, pDSData3DTZ, &FileName[0]);
		 SoundList[FileName].Sound= pDSDataTZ;
		 SoundList[FileName].Sound3D= pDSData3DTZ;
	 }
	 //else {
		 Sound->Sound = SoundList[FileName].Sound;
		 Sound->Sound3D = SoundList[FileName].Sound3D;
	 //}
	 return;
}

void SoundManager::AllDelete(void)
{
	for (auto itr = SoundList.begin(); itr != SoundList.end(); itr++) {
		if (itr->second.Sound != nullptr) {
			/*itr->second.Sound->Release();
			itr->second.Sound3D->Release();*/
		}
	}
	SoundList.clear();

}
