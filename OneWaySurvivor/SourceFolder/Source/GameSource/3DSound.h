#pragma once
#include<d3dx9.h>
#include<dsound.h>

class Sound3D {
private:
	LPDIRECTSOUND3DLISTENER8 lpSListener;
protected:
public:
	Sound3D();
	~Sound3D();
	bool Update();
};