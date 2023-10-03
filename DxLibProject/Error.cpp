#include "Error.h"
#include "KeyInput.h"

void ErrorEnd()
{
    DxLib_End();
    exit(-1);
}

void ErrorMessageBoxOK(const TCHAR* message)
{
    MessageBox(NULL, message, _T("Error"), MB_OK);
}

void ErrorMessageWithFinish(const TCHAR* message, const TCHAR* functionName, int line)
{
    printfDx(_T("異常が発生しました。\n%s\n%s(%d)\nEscキーを押してソフトを終了します。")
        , message
        , functionName
        , line
    );
    while (!ProcessMessage()) {
        ClearDrawScreen();
        ScreenFlip();
        KeyInput::update();
        if (KeyInput::getKeyHit(KEY_INPUT_ESCAPE))
            break;
    }
    DxLib_End();
    exit(-1);
}
