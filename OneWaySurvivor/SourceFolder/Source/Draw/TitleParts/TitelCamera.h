#pragma once
#include<d3dx9.h>
#include"../../Player/Camera.h"
#ifndef TitleCamera_H
#define TitleCamera_H

class TitleCamera:public Camera {
private:
protected:
public:
	void Init() {};
	TitleCamera() {};
	~TitleCamera() {};
	bool Update(D3DXMATRIX mat);
};

#endif //!_TitleCameraH