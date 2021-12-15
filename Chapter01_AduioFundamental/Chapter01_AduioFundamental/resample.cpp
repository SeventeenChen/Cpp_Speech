/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：resample.cpp
// 文件功能描述：语音信号的重采样
// 创建者：SeventeenChen
// 时间：2021/12/11
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/

#include "resample.h"

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
std::vector<double> resample(vector<double> in_array, int target_fs, int source_fs)
{
	int source_len, target_len;
	double duration;	// 序列时长初始化（秒）
	double resample_stepsize = (double) source_fs / target_fs;	// 重采样序列自变量步长
	double leftBound = 0, rightBound = 0;	//边界导数

	source_len = in_array.size();		// 已知序列长度
	std::vector<double> source_x(source_len);	// 已知序列自变量初始化
	std::iota(source_x.begin(), source_x.end(), 0);	// 递增序列
	// vector ---> array
	double *x0 = new double[source_len];	// 已知序列自变量数组初始化
	if (!source_x.empty())
	{
		memcpy(x0, &source_x[0], source_len * sizeof(double));	// 赋值
	}
	double *y0 = new double[source_len];	// 已知序列因变量数组初始化
	if (!in_array.empty())
	{
		memcpy(y0, &in_array[0], source_len * sizeof(double));
	}
	Spline sp(x0, y0, source_len, GivenSecondOrder, leftBound, rightBound);
	duration = double(source_len) / source_fs;
	target_len = floor(duration * target_fs);	// 重采样后序列长度
	std::vector<double> target_x(target_len);	// 初始化重采样后序列自变量
	std::vector<double> target_y(target_len);	// 初始化重采样后序列自变量
	std::iota(target_x.begin(), target_x.end(), 0);	// 递增序列
	double *x = new double[target_len];	// 重采样后序列自变量数组初始化
	double *y = new double[target_len];	// 重采样后序列因变量数组初始化
	if (!target_x.empty())
	{
		memcpy(x, &target_x[0], target_len * sizeof(double));	// 重采样序列自变量索引
	}
	for (int i = 0; i < target_len; i++)
	{
		x[i] *= resample_stepsize;		// 实际重采样自变量序列
		if (x[i] > x0[source_len - 1])
		{
			x[i] = x0[source_len - 1];
		}
	}
	if (!target_y.empty())
	{
		memcpy(y, &target_y[0], target_len * sizeof(double));
	}

	sp.MultiPointInterp(x, target_len, y);			//插值结果

	vector<double> target_vec (y, y + target_len);

	return target_vec;
}

