#include "universal.h"	
#include "short_time_energy.h"
#include "short_zero_cross.h"
#include "xcorr.h"

int main()
{
	string filepath = "bluesky3.wav";	// 可以是绝对路径 
	int fs = 16000;
	bool disp_flag = false;
	std::tuple<vector <double>, int> in_data;
	std::vector<double> in_array;

	// 注：项目右键-属性-链接器-系统-子系统-控制台
	in_data = audioread(filepath, fs, disp_flag);	// 语音信号的读取

	in_array = std::get<0>(in_data);	// 音频数据
	fs = std::get<1>(in_data);			// 采样频率


	int win_len = 200;	// set 10 for test
	int frame_shift = 80;
	std::vector<double> hann_window(win_len);	// 汉宁窗
	hann_window = window(win_len, "hanning");
	int frame_num = (in_array.size() - win_len + frame_shift) / frame_shift;

	//// 短时能量测试
	//std::vector<double> En(frame_num);
	//En = energy(in_array, hann_window, frame_shift);	// 短时能量
	//GLFWPlot(En, "Short Time Energy");

	//// 短时平均过零率测试
	//std::vector<double> Zcr(frame_num);
	//Zcr = zero_cross(in_array, hann_window, frame_shift);	// 短时过零率
	//GLFWPlot(Zcr, "Short Time Average Zero Cross Rate");

	// 短时自相关测试
	vector<double> corr(2 * win_len - 1);	// 初始化自相关数组
	vector<vector<double> >frame_signal(frame_num, vector<double>(win_len));	// 分帧后数据
	frame_signal = enframe(in_array, hann_window, frame_shift);
	vector<double> one_frame(win_len);		// 提取一帧数据
	int frame_index = 0;	// 初始化绘制帧数索引
	cout << "请问您想绘制哪一帧信号的自相关？输入数据需 < " << frame_num << endl;
	cin >> frame_index;

	for (int i = 0; i < win_len; i++)
	{
		one_frame[i] = frame_signal[frame_index - 1][i];
	}
	corr = xcorr(one_frame, one_frame);
	GLFWPlot(corr, "Short Time Auto Correlation");
	return 0;
}