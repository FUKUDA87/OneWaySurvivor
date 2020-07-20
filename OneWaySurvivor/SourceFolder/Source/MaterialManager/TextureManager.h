#pragma once
#include<d3dx9.h>
#include<string>
#include<map>

class TextureManager 
{
public:
	~TextureManager();
	LPDIRECT3DTEXTURE9 GetTexture(std::string FileName, int Wibth, int Height, D3DCOLOR ColorKey);
	void AllDelete(void);

private:
	std::map<std::string, LPDIRECT3DTEXTURE9>TextureList;
};

