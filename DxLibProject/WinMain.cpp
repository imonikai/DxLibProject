/*
* ~文字コードについて~
* 文字列を扱う場合は、_T("テキスト")のようにする。
* これによってマルチバイト文字とワイド文字をビルド時にcharとwchar_tを自動で使い分ける。
* _T()はマクロということ。
* 文字列の変数はTCHAR型のポインタにする。
* TCHARは_T()と同じような感じ。変数の型charとwchar_tを自動で使い分ける。
*
* ~エラー表示について~
* Error.hにメッセージボックスでエラーを表示する関数があるが、
* フルスクリーンモードではメッセージボックスが使えない。
* EXIT_ERR()マクロを使え
*/

#include "DxLib.h"
#include "define.h"
#include "Error.h"
#include "Timer.h"
#include "collision.h"
#include "GameInput.h"
#include "KeyInput.h"
#include "FpsControll.h"

//ゲームループの必須処理
BOOL requiredProcess()
{
    if (ProcessMessage() == -1) return FALSE;
    if (ScreenFlip() == -1) return FALSE;
    if (ClearDrawScreen() == -1) return FALSE;
    if (FpsControll::update() == FALSE) return FALSE;
    if (GameInput::update() == FALSE) return FALSE;
    if (Timer::update() == FALSE) return FALSE;

    return TRUE;
}

//ウィンドウのアクティブ状態が変化したときのコールバック関数
int callBackDeviceLost(int ActiveState, void* UserData)
{
    Timer::init();

    return 1;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
    /* ゲーム処理初期　*/
    SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8); //utf8を使うようにする
    SetWindowText(_T("ゲーム作れ！！")); ///ウィンドウタイトル設定
    SetGraphMode(GRAPH_WIDTH, GRAPH_HEIGHT, GRAPH_COLOR_BIT); //解像度を設定
    SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); //ウィンドウサイズを設定
    SetFontSize(30); //デフォルトのフォントサイズを設定
    SetOutApplicationLogValidFlag(TRUE); //Log.txtの設定
    SetWaitVSyncFlag(TRUE); //垂直同期を待つか設定
    SetUseTransColor(FALSE); //アルファチャンネルのない画像で透過色機能を使うか設定（オフ）
    /*フルスクリーンかウィンドウか選ばせる*/
    if (MessageBox(NULL, _T("フルスクリーンで起動しますか？"), _T("起動オプション"), MB_YESNO) == IDYES) {
        ChangeWindowMode(FALSE);
    }
    else {
        ChangeWindowMode(TRUE);
        SetWindowSizeChangeEnableFlag(TRUE);
    }
    if (DxLib_Init() == -1) { // ＤＸライブラリ初期化処理
        return -1;			// エラーが起きたら直ちに終了
    }
    SetDrawScreen(DX_SCREEN_BACK); //裏画面を使用する
    SetActiveStateChangeCallBackFunction(callBackDeviceLost, NULL); //アクティブ状態が変化したときに変化があったときのコールバックを設定

    FpsControll::init();
    Timer::init(); //タイマーを初期化する
    GameInput::init();

    /*サンプルの丸用変数*/
    Circle c1 = { 100.0f, 100.0f, 10.0f };
    Circle c2 = { 300.0f, 300.0f, 100.0f };
    float speed = 10.0f;

    BOOL c2FillFlag = FALSE;

    // while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
    while ( requiredProcess() ) {

        //エスケープで終了
        if (KeyInput::getKeyHit(KEY_INPUT_ESCAPE) >= 1) break;

        if (KeyInput::getKeyHit(KEY_INPUT_E) >= 1) {
            EXIT_ERR(_T("エラーのテストだ！！"));
        }
        

        // fpsの表示
        DrawFormatString(0, 0, GetColor(255, 255, 255), _T("%.2f"), FpsControll::getFps());

        float move;
        move = speed;
        if (GameInput::getInputHit(GAMEINPUT_UP) || GameInput::getInputHit(GAMEINPUT_DOWN))
        {
            if (GameInput::getInputHit(GAMEINPUT_LEFT) || GameInput::getInputHit(GAMEINPUT_RIGHT))
            {
                move *= MOVE_CORRECTION;
            }
        }

        /* キー入力かXInputの入力で丸が動く */
        if (GameInput::getInputHit(GAMEINPUT_RIGHT))
            c1.x += move;
        if (GameInput::getInputHit(GAMEINPUT_LEFT))
            c1.x -= move;
        if (GameInput::getInputHit(GAMEINPUT_UP))
            c1.y -= move;
        if (GameInput::getInputHit(GAMEINPUT_DOWN))
            c1.y += move;

        if (collisionCircle(c1, c2))
            c2FillFlag = TRUE;
        else
            c2FillFlag = FALSE;

        DrawCircleAA(c2.x, c2.y, c2.r, 32, GetColor(0, 0, 255), c2FillFlag);
        DrawCircleAA(c1.x, c1.y, c1.r, 32, GetColor(255, 0, 0), TRUE);

    }

    DxLib_End();			// ＤＸライブラリ使用の終了処理
    return 0;				// ソフトの終了
}

