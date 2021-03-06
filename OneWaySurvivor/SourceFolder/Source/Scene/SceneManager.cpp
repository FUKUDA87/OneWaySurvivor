#include"SceneManager.h"
SceneManager::SceneManager() {
	nowScene = nullptr;
}
SceneManager::~SceneManager() {
	if (nowScene != nullptr) {
		delete nowScene;
	}
}
void SceneManager::NowScene(void) {
	if (nowScene != nullptr) {
		nowScene->Frame();//今のシーンを実行
	}
}
void SceneManager::changeScene(SceneBase *NewScene) {
	if (nowScene != nullptr) {
		delete nowScene;
	}
	nowScene = NewScene;
}