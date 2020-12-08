
#include "InGameScene.h"
#include "DxLib.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"

// 実行ステップ定義
enum
{
	STEP_START_JINGLE,	// 開始ジングル待ち
	STEP_INPUT,			// 入力待ち
	STEP_CLEAR_JINGLE,	// クリアジングル待ち
	STEP_END,
};

// 倉庫番のサンプルステージ
const int g_SampleStage[STAGE_HEIGHT][STAGE_WIDTH] =
{
	0,0,0,1,1,1,1,1,0,0,0,
	0,0,0,1,3,3,3,1,0,0,0,
	0,0,0,1,0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,1,0,0,0,
	1,1,1,1,1,0,1,1,1,1,1,
	1,0,0,4,0,0,1,0,0,0,1,
	1,0,1,0,0,4,0,4,0,0,1,
	1,0,0,0,1,1,1,0,0,0,1,
	1,1,1,0,1,0,1,0,1,1,1,
	0,0,1,0,1,0,1,0,1,0,0,
	0,0,1,0,0,0,0,0,1,0,0,
	0,0,1,0,0,2,0,0,1,0,0,
	0,0,1,1,1,0,1,1,1,0,0,
};

InGameScene::InGameScene()
	: m_PlayerX( 0 )
	, m_PlayerY( 0 )
{
	// ステージデータを初期化
	for( int y = 0; y < STAGE_HEIGHT; y++ )
	{
		for( int x = 0; x < STAGE_WIDTH; x++ )
		{
			m_StageData[y][x] = g_SampleStage[y][x];
			if( m_StageData[y][x] == ObjectType_Player )
			{
				m_PlayerX = x;
				m_PlayerY = y;
				m_StageData[y][x] = ObjectType_Ground;
			}
		}
	}

	set_Step( STEP_START_JINGLE );
}

InGameScene::~InGameScene()
{
}

void InGameScene::Exec()
{
	switch ( m_Step )
	{
	case STEP_START_JINGLE:	step_StartJingle();	break;
	case STEP_INPUT:		step_Input();		break;
	case STEP_CLEAR_JINGLE:	step_ClearJingle();	break;
	default:									break;
	}
}

void InGameScene::Draw()
{
	// ステージの中身と、プレイヤーを描画(DXライブラリのDrawBoxを使用)
	// 	int DrawBox( int x1 , int y1 , int x2 , int y2 , unsigned int Color , int FillFlag ) ;
	
	// 課題(22日まで)
	// m_StageDataの配列の中身をみて、それぞれの四角形を描画する
	//	ObjectType_Ground,			// 0 なし
	//	ObjectType_Wall,			// 1 白(255, 255, 255)
	//	ObjectType_Target,			// 3 赤(255,   0,   0)
	//	ObjectType_UnsetCrate,		// 4 紫(255,   0, 255)
	//	ObjectType_SetCrate = 7,	// 7 緑(  0, 255,   0)

	DrawBox( m_PlayerX * CHIP_WIDTH,
			 m_PlayerY * CHIP_HEIGHT,
			 m_PlayerX * CHIP_WIDTH  + CHIP_WIDTH,
			 m_PlayerY * CHIP_HEIGHT + CHIP_HEIGHT,
			 GetColor( 0, 0, 255 ),
			 TRUE );

	// 画面左上にデバッグ用の文字を黒で表示する
	DrawString( 20, 20, "InGameScene", GetColor(0,0,0) );
}

bool InGameScene::IsEnd() const
{
	return ( m_Step == STEP_END );
}

// 開始ジングル待ち
void InGameScene::step_StartJingle()
{
	set_Step( STEP_INPUT );
}
// 入力待ち
void InGameScene::step_Input()
{
	InputManager* pInputMng = InputManager::GetInstance();
	if( pInputMng->IsPush(KeyType_Enter) )
	{
		set_Step( STEP_CLEAR_JINGLE );
	}
}
// クリアジングル待ち
void InGameScene::step_ClearJingle()
{
	set_Step( STEP_END );
	SceneManager::SetNextScene( SceneID_Result );
}

