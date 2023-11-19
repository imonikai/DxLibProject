#pragma once
#include "DxLib.h"

#define EXIT_ERR(message) ExitWithError(message, _T(__FUNCTION__), __LINE__)

void ErrorEnd(); //DXライブラリを終了してソフトも終了する
void ErrorMessageBoxOK(const TCHAR*); /*引数のエラーメッセージを表示 _T()で文字列を囲うこと */
void ExitWithError(const TCHAR*, const TCHAR*, const int);
