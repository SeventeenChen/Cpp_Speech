//----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：main.cpp
// 文件功能描述：语音信号基本操作测试主函数
// 创建者：SeventeenChen
// 时间：2021/12/06
// 修改人：SeventeenChen
// 时间：2021/12/06
// 修改说明：实现语音信号的读取
// 软件版本：VS2015
//----------------------------------------------------------------
#include "audioread.h"

int main()
{
	string filepath = "bluesky3.wav";
	int fs = 16000;
	bool disp_flag = true;
	// 注：项目右键-属性-系统-子系统-控制台
	audioread(filepath, fs, disp_flag);	// 语音信号的读取

	return 0;
}

