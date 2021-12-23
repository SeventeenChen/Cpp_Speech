#include "universal.h"	
#include "short_time_energy.h"
#include "short_zero_cross.h"
#include "xcorr.h"

int main()
{
	string filepath = "bluesky3.wav";	// �����Ǿ���·�� 
	int fs = 16000;
	bool disp_flag = false;
	std::tuple<vector <double>, int> in_data;
	std::vector<double> in_array;

	// ע����Ŀ�Ҽ�-����-������-ϵͳ-��ϵͳ-����̨
	in_data = audioread(filepath, fs, disp_flag);	// �����źŵĶ�ȡ

	in_array = std::get<0>(in_data);	// ��Ƶ����
	fs = std::get<1>(in_data);			// ����Ƶ��


	int win_len = 200;	// set 10 for test
	int frame_shift = 80;
	std::vector<double> hann_window(win_len);	// ������
	hann_window = window(win_len, "hanning");
	int frame_num = (in_array.size() - win_len + frame_shift) / frame_shift;

	//// ��ʱ��������
	//std::vector<double> En(frame_num);
	//En = energy(in_array, hann_window, frame_shift);	// ��ʱ����
	//GLFWPlot(En, "Short Time Energy");

	//// ��ʱƽ�������ʲ���
	//std::vector<double> Zcr(frame_num);
	//Zcr = zero_cross(in_array, hann_window, frame_shift);	// ��ʱ������
	//GLFWPlot(Zcr, "Short Time Average Zero Cross Rate");

	// ��ʱ����ز���
	vector<double> corr(2 * win_len - 1);	// ��ʼ�����������
	vector<vector<double> >frame_signal(frame_num, vector<double>(win_len));	// ��֡������
	frame_signal = enframe(in_array, hann_window, frame_shift);
	vector<double> one_frame(win_len);		// ��ȡһ֡����
	int frame_index = 0;	// ��ʼ������֡������
	cout << "�������������һ֡�źŵ�����أ����������� < " << frame_num << endl;
	cin >> frame_index;

	for (int i = 0; i < win_len; i++)
	{
		one_frame[i] = frame_signal[frame_index - 1][i];
	}
	corr = xcorr(one_frame, one_frame);
	GLFWPlot(corr, "Short Time Auto Correlation");
	return 0;
}