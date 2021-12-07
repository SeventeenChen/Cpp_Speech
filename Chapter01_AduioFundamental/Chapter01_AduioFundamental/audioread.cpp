/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：audioread.cpp
// 文件功能描述：语音信号的读取
// 创建者：SeventeenChen
// 时间：2021/12/06
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/

#include "audioread.h"

/*-----------------------------------------------------------------
// 输入：wav文件名（string），采样率（int），是否显示文件头（bool）
// 输出：在控制台打印wav语音头参数，wav音频数据（归一化）至同名txt文件
// 功能描述：语音信号的读取
// TODO：完善成可读取系统路径
// 作者：SeventeenChen
// 日期：2021/12/06
// 修改人：SeventeenChen
// 记录：可同时返回音频数据与采样频率
// 日期：2021/12/07
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
std::tuple<vector <double>, int> audioread(string filepath, int fs, bool disp_flag)
{

	std::tuple<vector <double>, int> in_data;
	std::vector<double> in_array;

	in_data = GetFileData(filepath, fs, disp_flag);	// 从文件读取音频数据
	in_array = std::get<0>(in_data);
	fs = std::get<1>(in_data);

	std::string filename = filepath.substr(0, filepath.rfind('.'));
	std::string textname = filename + ".txt";

	std::ofstream fout(textname);
	fout << std::setprecision(10);

	for (auto const& x : in_array)
	{
		fout << x << '\n';
	}	

	return make_tuple(in_array, fs);
}