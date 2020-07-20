#pragma once
#include"../../Draw/2D/Window.h"
#include"../../GameSource/Judgment.h"
#include"../../Scene/SceneNo.h"
#include"../Button/Menu/ButtonGameScene.h"
#include<vector>

class C_NextTouch:public Window {
public:
	C_NextTouch();
	~C_NextTouch();
	// 更新処理
	virtual bool UpdateAll(void);
	//表示
	virtual void Draw2DAll(void);
	//タッチの確認
	virtual int Touch(void);

protected:
	std::vector<c_ButtonGameScene*>m_button;
private:

	int TouchNowNo;// 最新で押されたボタン番号

	// 削除
	void Delete(void);


};