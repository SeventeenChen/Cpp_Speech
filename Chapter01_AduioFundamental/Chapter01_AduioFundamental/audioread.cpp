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
// 输出：wav语音头数据至控制台，wav音频数据（归一化）至同名txt文件
// 功能描述：读取wav文件
// TODO：完善成可读取系统路径
// 作者：SeventeenChen
// 日期：2021/12/06
// 修改人：
// 记录：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
void audioread(string filepath, int fs, bool disp_flag)
{

	std::vector<double> in_dataArray;

	in_dataArray = GetFileData(filepath, fs, disp_flag);	// 从文件读取音频数据

	std::string filename = filepath.substr(0, filepath.rfind('.'));
	std::string textname = filename + ".txt";

	std::ofstream fout(textname);
	fout << std::setprecision(10);

	for (auto const& x : in_dataArray)
	{
		fout << x << '\n';
	}	

}