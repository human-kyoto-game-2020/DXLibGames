
#ifndef RESULT_SCENE_H
#define RESULT_SCENE_H

// 継承する、基底クラスのヘッダー
#include "SceneBase.h"

// リザルトシーンクラス
class ResultScene : public SceneBase
{
public:
	ResultScene();
	virtual ~ResultScene();

	virtual void Exec();	// 処理を行う
	virtual void Draw();	// 描画を行う

};

#endif // #ifndef RESULT_SCENE_H
