/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：short_time_energy.h
// 文件功能描述：语音信号的短时能量
// 创建者：SeventeenChen
// 时间：2021/12/21
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/
#pragma once
#include <vector>
#include <iostream>
#include "universal.h"
// #include "../../Chapter01_AduioFundamental/Chapter01_AduioFundamental/enframe.h"
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