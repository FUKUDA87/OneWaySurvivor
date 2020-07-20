#pragma once
#include"../../Player/Camera.h"
#include<d3dx9.h>
#include"../../Key/CMouse.h"


class StageCam :public Camera {
public:
	StageCam();
	~StageCam() {};
	bool Update(D3DXMATRIX mat, D3DXMATRIX tmp, bool MouFlg);
	bool UpdateCar(C_Mouse *Mouse);


	float GetHeight(void) {
		return Height;
	}

	void SetHeight(const float *H_Height) {
		Height = *H_Height;
	}
protected:
	float sizeZ, upY;

	void Init_Car(void);

private:
	float CamAngX, CamAngY, CamSize, CamSizeCha, TransCha, sen, Height;//sen=Š´“x
};