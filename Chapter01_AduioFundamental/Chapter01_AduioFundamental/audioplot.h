//----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����audioplot.h
// �ļ����������������źŲ��εĻ���
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/08
// �޸��ˣ�SeventeenChen
// ��¼�����title���
// ���ڣ�2021/12/10
// ����汾��VS2015
//----------------------------------------------------------------
#pragma once
#include <vector>
#include <GLFW/glfw3.h>

int GLFWPlot(std::vector<double> in_dataArray, const char *title);
void audioplot(std::vector<double> in_dataArray);
