/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：stamd.h
// 文件功能描述：语音信号的短时平均幅度差
// 创建者：SeventeenChen
// 时间：2021/12/24
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/
#pragma once

#pragma once
#include <vector>
#include <cmath>
#include <limits>
#include <type_traits>
#include <iostream>
#include <iomanip>
using namespace std;

#ifndef EPS
#define EPS std::numeric_limits<double>::epsilon()
#endif

/*-----------------------------------------------------------------
// 输入：一帧信号（一维数组）
// 输出：信号的短时平均幅度差，维度与信号维度相等
// 功能描述：计算信号的短时平均幅度差
// 作者：SeventeenChen
// 日期：2021/12/24
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
vector<double>amdf(vector<double> in_array);