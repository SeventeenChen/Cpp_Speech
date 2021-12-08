/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：Fundamental.cpp
// 文件功能描述：语音信号的基本操作
// 创建者：SeventeenChen
// 时间：2021/11/28
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/
#include "Fundamental.h"

/*-----------------------------------------------------------------
// 输入：文件名，采样频率（任意int类型），显示头文件标记（bool型）
// 输出：tuple型（音频数据, 实际采样频率）
// 功能描述：读取wav文件至内存，提取音频数据及采样频率
// 作者：SeventeenChen
// 日期：2021/11/27
// 修改人：SeventeenChen
// 记录：可同时返回音频数据与采样频率
// 日期：2021/12/07
// 修改人：SeventeenChen
// 记录：增加文件不能打开时的抛出异常
// 日期：2021/12/08
// 版本：
-----------------------------------------------------------------*/
std::tuple<vector<double>, int> GetFileData(string file, int fs, bool disp_flag)
{
	CWave wave;	
	std::ifstream ifs (file, ios::in | ios::binary);

	if (!ifs)
	{
		throw "File could not be opened";		// 异常处理
		return make_tuple(std::vector<double>(0), 0);
	}
	else 
	{
		wave.audioread(file);	// 读入wav文件
		if (disp_flag)
		{
			std::cout << "wav header: " << endl;
			wave.DisplayHeader();
		}
		ifs.close();
		fs = int(wave.m_wave.SampleRate);	// 读取采样率
		std::vector<double> in_dataArray;	// 读入音频数据
		GetInputData(wave.m_dataArray, in_dataArray, wave.m_wave.wChannels);	// 取单通道
		return make_tuple(in_dataArray, fs);
	}
	
}

/*-----------------------------------------------------------------
// 输入：读入数据，输出数据（动态数组的引用）；通道数标记flag
// 输出：单通道音频数据
// 功能描述：读取wav文件，如果是双通道音频，只取左声道
// 作者：SeventeenChen
// 日期：2021/11/27
// 修改人：
// 记录：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
void GetInputData(std::vector<double> &in_dataArray, std::vector<double>&out_dataArray, int flag)
{
	int nDataLength = in_dataArray.size();
	int nSampleLength = 0;//样本长度
	if (2 == flag)
	{
		nSampleLength = nDataLength / 2;
		out_dataArray.resize(nSampleLength);
		for (int i = 0; i < nSampleLength; i++)
		{
			out_dataArray[i] = in_dataArray[2 * i];//取左声道
		}
	}

	else
	{
		nSampleLength = nDataLength;
		out_dataArray.resize(nSampleLength);
		out_dataArray = in_dataArray;
	}
}
