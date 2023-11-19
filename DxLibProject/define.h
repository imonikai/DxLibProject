#pragma once
#include "DxLib.h"
/*
* ここに定義するのはゲーム全体で普遍的に使いそうな変数だけにする
*/

//ウィンドウサイズ
inline constexpr int WINDOW_WIDTH = 1280;
inline constexpr int WINDOW_HEIGHT = 720;

//描画領域のサイズ
inline constexpr int GRAPH_WIDTH = 1280;
inline constexpr int GRAPH_HEIGHT = 720;
inline constexpr int GRAPH_COLOR_BIT = 32;

//斜め45移動の補正値
inline constexpr float MOVE_CORRECTION = 0.70710677f;


