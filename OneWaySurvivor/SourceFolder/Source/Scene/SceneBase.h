#pragma once
#include<d3dx9.h>

class SceneBase
{
private:
	DWORD NowTime, PrevTime, NowTime0, PrevTime0;
	int Cnt, Fps;
public:
	virtual ~SceneBase();
	virtual void save(void) {};
	virtual bool road(void) { return true; };
	virtual bool Update(void);
	virtual void Render3D(void);
	virtual void Render3DScreen(void);
	virtual void Render2D(void);
	virtual void SetCamera(void);

	void Frame(void);
};