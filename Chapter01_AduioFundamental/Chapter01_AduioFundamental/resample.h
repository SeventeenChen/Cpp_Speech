/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：resample.h
// 文件功能描述：语音信号的重采样
// 创建者：SeventeenChen
// 时间：2021/12/14
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/
#pragma once

#include <vector>
#include <numeric>
#include <iostream>
#include "spline.h"
using namespace std;
using namespace SplineSpace;

/*-----------------------------------------------------------------
// 输入：待重采样信号（一维数组 vector），目标采样率，原始采样率
// 输出：重采样后信号（一维数组 vector）
// 功能描述：一维信号的重采样
// 作者：SeventeenChen
// 日期：2021/12/11
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 日期：
// 版本：
-----------------------------------------------------------------*/
std::vector<double> resample(vector<double> in_array, int target_fs, int source_fs);