#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include<string>

class C_DrawTextureManager_Base {
public:
	virtual TEXTURE Get_Texture(const int *TexNo)=0;
protected:
	//テクスチャのロード
	TEXTURE Texture_Load(std::string FileName, const int Width, const int Height);
	//テクスチャのロードと色の削除
	TEXTURE Texture_Load(std::string FileName, const int Width, const int Height, const int r, const int g, const int b);
private:
};