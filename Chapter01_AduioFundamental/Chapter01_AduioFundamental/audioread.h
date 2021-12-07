/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：audioread.h
// 文件功能描述：语音信号的读取
// 创建者：SeventeenChen
// 时间：2021/12/06
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/
#pragma once
#include <string>
#include <iomanip>
#include "Fundamental.h"
/*-----------------------------------------------------------------
// 输入：wav文件名（string），采样率（int），是否显示文件头（bool）
// 输出：wav语音头数据至控制台，wav音频数据（归一化）至txt文件
// 功能描述：语音信号的读取，返回音频数据与采样率
// 作者：SeventeenChen
// 日期：2021/12/06
// 修改人：SeventeenChen
// 记录：可同时返回音频数据与采样频率
// 日期：2021/12/07
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
std::tuple<vector <double>, int> audioread(string filepath, int fs, bool disp_flag);
