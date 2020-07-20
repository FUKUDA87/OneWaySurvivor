#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include<string>


class C_TextureBase {
public:
	
protected:

	/*関数*/

	//テクスチャのロード
	void Texture_Load(std::string FailName, const int Width, const int Height);
	//テクスチャのロードと色の削除
	void Texture_Load(std::string FailName, const int Width, const int Height, const int r, const int g, const int b);
	//テクスチャの情報渡し
	TEXTURE Get_S_Texture(void) {
		return M_Tex;
	}
private:
	TEXTURE M_Tex;
};