#include "3DSound.h"

Sound3D::Sound3D()
{
	/*lpSPrimary->QueryInterface(IID_IDirectSound3DListener8, (LPVOID*)&lpSListener);
	lpSListener->SetRolloffFactor(0.5f, DS3D_IMMEDIATE);
	LoadWAVE3D(secondTest[0], secondTest3D[0], "Test.WAV");
	LPDIRECTSOUNDBUFFER lpSTmp;
	for (int i = 1; i < SOUND_NUM; i++) {
		lpDSound->DuplicateSoundBuffer(secondTest[0], &lpSTmp);
		lpSTmp->QueryInterface(IID_IDirectSoundBuffer8, (LPVOID*)&secondTest[i]);
		secondTest[i]->QueryInterface(IID_IDirectSound3DBuffer8, (LPVOID*)&secondTest3D[i]);
		secondTest3D[i]->SetMode(DS3DMODE_NORMAL, DS3D_IMMEDIATE);
		lpSTmp->Release();
	}*/
}

Sound3D::~Sound3D()
{
	lpSListener->Release();
}
bool Sound3D::Update(/*LPDIRECTSOUND3DBUFFER secondTest3D,*/)
{
		/*DWORD SFlg;
		for (int i = 0; i < SOUND_NUM; i++) {
			secondTest3D[i]->SetPosition(katsuoMat._41, katsuoMat._42, katsuoMat._43, DS3D_IMMEDIATE);//音源の位置
			lpSListener->SetPosition(camPos.x, camPos.y, camPos.z, DS3D_IMMEDIATE);//リスナーの位置
			//リスナーが見ている方向計算
			D3DXVECTOR3 Vec;
			Vec = camLook - camPos;
			D3DXVec3Normalize(&Vec, &Vec);

			lpSListener->SetOrientation(Vec.x, Vec.y, Vec.z, camHead.x, camHead.y, camHead.z, DS3D_IMMEDIATE);//リスナーが見ている方向とリスナーの頭の方向
			secondTest[i]->GetStatus(&SFlg);
			if ((SFlg&DSBSTATUS_PLAYING) == 0) {
				secondTest[i]->Play(0, 0, 0);
				break;
			}
		}*/
	return false;
}