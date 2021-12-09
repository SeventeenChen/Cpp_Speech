#pragma once

#include <vector>
#include <string>
#include <iostream>
using namespace std;

#ifndef _pi_
#define _pi_  3.1415926535898
#endif


/*-----------------------------------------------------------------
// 输入：语音信号in_array，窗函数win，帧移frame_shift
// 输出：分帧后数组，帧数 x 帧长
// 功能描述：分帧
// 作者：SeventeenChen
// 日期：2021/12/09
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
std::vector<vector<double> > enframe(vector<double> in_array, vector<double> win, int frame_shift);

/*-----------------------------------------------------------------
// 输入：窗长（int），窗类型：矩形"default"/汉明"hamming"/汉宁"hanning"
// 输出：窗函数（vector）
// 功能描述：窗函数赋值
// 作者：SeventeenChen
// 日期：2021/12/09
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
std::vector<double> window(int window_length, string window_type);