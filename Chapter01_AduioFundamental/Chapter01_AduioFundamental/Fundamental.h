/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：Fundamental.h
// 文件功能描述：语音信号的基本操作
// 创建者：SeventeenChen
// 时间：2021/11/28
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/
#pragma once

#include <vector>
#include "audio.h"
#include <string>
#include <tuple>
#include <iostream>
using namespace std;

std::tuple<vector<double>, int> GetFileData(string WcsTrainDataName, int fs, bool disp_flag);
//读取文件内容，返回音频数据和采样率

void GetInputData(std::vector<double> &in_dataArray, std::vector<double>&out_dataArray, int flag);
//GetInputData:用于从音频文件中获取用于处理的数据，in_dataArray是输入语音数据，out_dataArray是输出数据。
//flag==2时，out_dataArray为in_dataArray的偶数序号数；
//flag==1时，out_dataArray=in_dataArray