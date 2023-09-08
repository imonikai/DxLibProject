/*
* ~文字コードについて~
* 文字列を扱う場合は、_T("テキスト")のようにする。
* これによってマルチバイト文字とUnicode文字をビルド時にcharとwchar_tを自動で使い分ける。
* _T()はマクロということ。
* 文字列の変数はTCHAR型のポインタにする。
* TCHARは_T()と同じような感じ。変数の型charとwchar_tを自動で使い分ける。
* 
* ~エラー表示について~
* Error.hにメッセージボックスでエラーを表示する関数があるが、
* フルスクリーンモードではメッセージボックスが使えない。
* ERROR_WITH_FINISH()マクロを使え
*/

#include "DxLib.h"
#include "define.h"
#include "KeyInput.h"
#include "Error.h"

// プログラムは WinMain から始まります 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    /* ゲーム処理初期　*/
    SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8); //utf8を使うようにする
    SetGraphMode(GRAPH_WIDTH, GRAPH_HEIGHT, GRAPH_COLOR_BIT); //解像度を設定
    SetOutApplicationLogValidFlag(DX_LOGTXT_OUTPUT_FLAG); //Log.txtの設定
    /*フルスクリーンかウィンドウか選ばせる*/
    if (MessageBox(NULL, _T("フルスクリーンで起動しますか？"), _T("起動オプション"), MB_YESNO) == IDYES) {
        ChangeWindowMode(FALSE);
    }
    else
    {
        ChangeWindowMode(TRUE);
        SetWindowSizeChangeEnableFlag(TRUE);
    }
    if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
    {
        return -1;			// エラーが起きたら直ちに終了
    }
    SetDrawScreen(DX_SCREEN_BACK); //裏画面を使用する

    // while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
    while ( ScreenFlip() == 0 
        && ProcessMessage() == 0 
        && ClearDrawScreen() == 0 
        && KeyInput::update() == TRUE 
        && KeyInput::getKeyHit(KEY_INPUT_ESCAPE) == 0 
    )
    {
        if (KeyInput::getKeyHit(KEY_INPUT_E) >= 1)
        {
            ERROR_WITH_FINISH(_T("エラーのテストだ！！"));
        }
        //ゲームループ
        DrawCircle(100, 100, 10, GetColor(255, 0, 0), TRUE);

    }

    DxLib_End();			// ＤＸライブラリ使用の終了処理
    return 0;				// ソフトの終了 
}
