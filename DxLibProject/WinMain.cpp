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
#include "KeyInput.h"
#include "Error.h"
#include "Timer.h"
#include "XInput.h"
#include "collision.h"

//ゲームループの必須処理
BOOL requiredProcess()
{
    if (ScreenFlip() == -1) return FALSE;
    if (ProcessMessage() == -1) return FALSE;
    if (ClearDrawScreen() == -1) return FALSE;
    if (KeyInput::update() == FALSE) return FALSE;
    if (Timer::update() == FALSE) return FALSE;
    if (XInput::update() == FALSE) return FALSE;

    return TRUE;
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    /* ゲーム処理初期　*/
    SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8); //utf8を使うようにする
    SetWindowText(_T("ゲーム作れ！！")); ///ウィンドウタイトル設定
    SetGraphMode(GRAPH_WIDTH, GRAPH_HEIGHT, GRAPH_COLOR_BIT); //解像度を設定
    SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); //ウィンドウサイズを設定
    SetFontSize(30); //デフォルトのフォントサイズを設定
    SetOutApplicationLogValidFlag(TRUE); //Log.txtの設定
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

    Timer::init(); //タイマーを初期化する
    XInput::init(DX_INPUT_PAD1); //コントローラーを初期化する（コントローラーはゼロ番を使う

    /*サンプルの丸用変数*/
    Circle c1 = { 100.0f, 100.0f, 10.0f };
    Circle c2 = { 300.0f, 300.0f, 100.0f };
    float speed = 100.0f;

    BOOL c2FillFlag = FALSE;

    // while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
    while ( requiredProcess() ) {
        //エスケープで終了
        if (KeyInput::getKeyHit(KEY_INPUT_ESCAPE) >= 1) break;

        if (KeyInput::getKeyHit(KEY_INPUT_E) >= 1) {
            EXIT_ERR(_T("エラーのテストだ！！"));
        }

        

        // fpsの表示
        Timer::drawFps(0, 0);

        float move;
        move = speed;
        if (XInput::getInputHit(MY_XINPUT_LEFTSTICK_RIGHT) >= 1
            || KeyInput::getKeyHit(KEY_INPUT_RIGHT) >= 1
            || XInput::getInputHit(MY_XINPUT_LEFTSTICK_LEFT) >= 1
            || KeyInput::getKeyHit(KEY_INPUT_LEFT) >= 1)
        {
            if (XInput::getInputHit(MY_XINPUT_LEFTSTICK_UP) >= 1
                || KeyInput::getKeyHit(KEY_INPUT_UP) >= 1
                || XInput::getInputHit(MY_XINPUT_LEFTSTICK_DOWN) >= 1
                || KeyInput::getKeyHit(KEY_INPUT_DOWN) >= 1)
            {
                move *= MOVE_CORRECTION;
            }
        }

        /* キー入力かXInputの入力で丸が動く */
        if (   XInput::getInputHit(MY_XINPUT_LEFTSTICK_RIGHT) >= 1
            || KeyInput::getKeyHit(KEY_INPUT_RIGHT) )
            c1.x += move * Timer::getDeltaTime();
        if (   XInput::getInputHit(MY_XINPUT_LEFTSTICK_LEFT) >= 1
            || KeyInput::getKeyHit(KEY_INPUT_LEFT) )
            c1.x -= move * Timer::getDeltaTime();
        if (   XInput::getInputHit(MY_XINPUT_LEFTSTICK_UP) >= 1
            || KeyInput::getKeyHit(KEY_INPUT_UP) )
            c1.y -= move * Timer::getDeltaTime();
        if (   XInput::getInputHit(MY_XINPUT_LEFTSTICK_DOWN) >= 1
            || KeyInput::getKeyHit(KEY_INPUT_DOWN) )
            c1.y += move * Timer::getDeltaTime();

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

