#include "enframe.h"

/*-----------------------------------------------------------------
// 输入：语音信号in_array，窗函数win，帧移frame_shift
// 输出：分帧后数组，帧数 x 帧长
// 功能描述：分帧
// 作者：SeventeenChen
// 日期：2021/12/09
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
std::vector<vector<double> > enframe(vector<double> in_array, vector<double> win, int frame_shift)
{
	int len_x, len_win, frame_num;
	
	len_x = in_array.size();	// 数据长度
	len_win = win.size();		// 窗长（帧长）
	if (frame_shift == 0)
	{
		frame_shift = len_win;		// 若未设置帧移，则帧移=帧长
	}
	frame_num = (len_x - len_win + frame_shift) / frame_shift;	// 帧数
	// 初始化分帧后数组：帧数 x 帧长
	vector<vector<double> >f(frame_num, vector<double>(len_win));	
	for (int i = 0; i < frame_num; i++)
	{
		for (int j = 0; j < len_win; j++)
		{
			f[i][j] = in_array[i * frame_shift + j] * win[j];
		}
	}

	return f;
}

/*-----------------------------------------------------------------
// 输入：窗长（int），窗类型：矩形"default"/汉明"hamming"/汉宁"hanning" 
// 输出：窗函数（vector）
// 功能描述：窗函数赋值
// 作者：SeventeenChen
// 日期：2021/12/09
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
std::vector<double> window(int window_length, string window_type)
{
	std::vector<double> out_window_func(window_length);
	for (int i = 0; i < window_length; i++)
	{
		if (window_type == "hanning")
		{
			out_window_func[i] = 0.5 - 0.5*cos((2 * double(i) / (window_length - 1))*_pi_);
		}
		else if (window_type == "hamming")
		{
			out_window_func[i] = 0.54 - 0.46*cos((2 * double(i) / (window_length - 1))*_pi_);
		}
		else
		{
			out_window_func[i] = 1;
		}
	}

	return out_window_func;
}