
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../Definition.h"

// シーン管理クラス
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Exec();	// シーンの実行
	void Draw();	// シーンの描画

	static void SetNextScene( SceneID next_ );	// 次のシーン設定

private:
	class SceneBase* create_NextScene();	// 次のシーンを作成

private:
	class SceneBase*	m_pScene;		// 実行中のシーン
	static SceneID 		m_NextSceneID;	// 次に作るシーンのID

};

#endif	// #ifndef SCENE_MANAGER_H

