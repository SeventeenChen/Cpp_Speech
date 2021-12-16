//----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：audiowrite.cpp
// 文件功能描述：语音信号的写入
// 创建者：SeventeenChen
// 时间：2021/12/16
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------
#include "audiowrite.h"

/*-----------------------------------------------------------------
// 输入：语音信号y，采样率fs，存储地址filepath
// 输出：filepath.wav文件
// 功能描述：语音信号的写入存储
// 作者：SeventeenChen
// 日期：2021/12/16
// TODO：现仅支持16位存储，待优化至其他位数（如8/32等）
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
void audiowrite(vector<double> y, int fs, string filepath)
{
	// Write WAv文件	
	int channel_num = 1, bitrate = 16;
	Wave_header header(channel_num, fs, bitrate);	//e.g. Wave_header header(1, 48000, 16);
	uint32_t len_arr = y.size();				// 数组长度
	uint32_t length = len_arr * bitrate / 8;	// 字节数
	vector<int> int_array(len_arr);
	int16_t *data = new int16_t[length];
	
	for (int i = 0; i < len_arr; i++)
	{
		int_array[i] = y[i] * 32678;	// 量化 -32768 ~ 32768	
		data[i] = int_array[i];			// data中每个数据占据两个字节（16位）
	}
	CWaveFile::write(filepath, header, data, length);

}