// #include "short_time_energy.h"
#include "../../Chapter01_AduioFundamental/Chapter01_AduioFundamental/audioread.h"	// ���� -> C/C++ -> ���� -> ���Ӱ���Ŀ¼ 
// #include "../../Chapter01_AduioFundamental/Chapter01_AduioFundamental/audioplot.h"

int main()
{
	string filepath = "bluesky3.wav";	// �����Ǿ���·�� 
	int fs = 16000;
	bool disp_flag = true;
	std::tuple<vector <double>, int> in_data;
	std::vector<double> in_array;

	// ע����Ŀ�Ҽ�-����-������-ϵͳ-��ϵͳ-����̨
	in_data = audioread(filepath, fs, disp_flag);	// �����źŵĶ�ȡ

	in_array = std::get<0>(in_data);	// ��Ƶ����
	fs = std::get<1>(in_data);			// ����Ƶ��

	
	//int win_len = 200;	// set 10 for test
	//int frame_shift = 80;
	//std::vector<double> hann_window(win_len);	// ������
	//hann_window = window(win_len, "hanning");
	//int frame_num = (in_array.size() - win_len + frame_shift) / frame_shift;
	//std::vector<double> En(frame_num);
	//En = energy(in_array, hann_window, frame_shift);
	//GLFWPlot(En, "Short Time Energy");
	return 0;
}