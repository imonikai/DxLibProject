#include "Error.h"
#include "KeyInput.h"
#include "define.h"

void ErrorEnd() {
    DxLib_End();
    exit(-1);
}

void ErrorMessageBoxOK(const TCHAR* message) {
    MessageBox(NULL, message, _T("Error"), MB_OK);
}

void ExitWithError(const TCHAR* message, const TCHAR* functionName, int line) {
    SetFontSize((int)(GRAPH_WIDTH / 40));
    while (!ProcessMessage()) {
        ClearDrawScreen();
        DrawFormatString(0, 0, GetColor(255, 255, 255),
            _T("異常が発生しました。\nmsg: %s\nat: %s(%d)\nEscキーを押してソフトを終了します。")
            , message
            , functionName
            , line
        );
        ScreenFlip();
        KeyInput::update();
        if (KeyInput::getKeyHit(KEY_INPUT_ESCAPE))
            break;
    }
    DxLib_End();
    exit(-1);
}
