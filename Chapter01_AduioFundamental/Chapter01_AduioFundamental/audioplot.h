//----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：audioplot.h
// 文件功能描述：语音信号波形的绘制
// 创建者：SeventeenChen
// 时间：2021/12/08
// 修改人：SeventeenChen
// 记录：添加title标记
// 日期：2021/12/10
// 软件版本：VS2015
//----------------------------------------------------------------
#pragma once
#include <vector>
#include <GLFW/glfw3.h>

int GLFWPlot(std::vector<double> in_dataArray, const char *title);
void audioplot(std::vector<double> in_dataArray);
