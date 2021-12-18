#pragma once
#include <vector>
#include <iostream>
#include "../../Chapter01_AduioFundamental/Chapter01_AduioFundamental/enframe.h"
using namespace std;

/*-----------------------------------------------------------------
// 输入：语音信号in_array，窗函数win，帧移frame_shift
// 输出：每帧短时能量：帧数 x 1
// 功能描述：计算语音信号的短时能量
// 作者：SeventeenChen
// 日期：2021/12/18
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
vector<double> energy(vector<double> in_array, vector<double> win, int frame_shift);