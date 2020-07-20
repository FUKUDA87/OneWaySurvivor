#pragma once

#include"SceneBase.h"
class SceneManager
{
private:
	SceneBase *nowScene;//今、実行しているシーン
	SceneBase *Scene;
public:
	SceneManager();
	~SceneManager();
	void NowScene(void);
	void changeScene(SceneBase *NewScene);
};
