//#include "universal.h"	
//#include "ste.h"
//#include "stzcr.h"
//#include "xcorr.h"
//#include "stamd.h"
#include "fftw3.h"		// ���ã�https://blog.csdn.net/Aubrey_yt/article/details/102974019
						//		����dll�ļ�Ҳ��Ҫ�ƶ�������Ŀ¼��
#include <windows.h>
int main()
{
	fftw_complex *in, *out;
	fftw_plan p;
	int N = 8;
	int i;
	int j;
	in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * N);
	for (i = 0; i < N; i++)
	{
		in[i][0] = 1.0;
		in[i][1] = 0.0;
		printf("%6.2f ", in[i][0]);
	}
	printf("\n");
	p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p); /* repeat as needed*/
	for (j = 0; j < N; j++)
	{
		printf("%6.2f ", out[j][0]);
	}
	printf("\n");
	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);
	system("pause");
	return 0;
}

//int main()
//{
	//string filepath = "bluesky3.wav";	// �����Ǿ���·�� 
	//int fs = 16000;
	//bool disp_flag = false;
	//std::tuple<vector <double>, int> in_data;
	//std::vector<double> in_array;

	//// ע����Ŀ�Ҽ�-����-������-ϵͳ-��ϵͳ-����̨
	//in_data = audioread(filepath, fs, disp_flag);	// �����źŵĶ�ȡ

	//in_array = std::get<0>(in_data);	// ��Ƶ����
	//fs = std::get<1>(in_data);			// ����Ƶ��


	//int win_len = 200;	// set 10 for test
	//int frame_shift = 80;
	//std::vector<double> hann_window(win_len);	// ������
	//hann_window = window(win_len, "hanning");
	//int frame_num = (in_array.size() - win_len + frame_shift) / frame_shift;

	////// ��ʱ��������
	////std::vector<double> En(frame_num);
	////En = energy(in_array, hann_window, frame_shift);	// ��ʱ����
	////GLFWPlot(En, "Short Time Energy");

	////// ��ʱƽ�������ʲ���
	////std::vector<double> Zcr(frame_num);
	////Zcr = zero_cross(in_array, hann_window, frame_shift);	// ��ʱ������
	////GLFWPlot(Zcr, "Short Time Average Zero Cross Rate");

	////// ��ʱ����ز���
	////vector<double> corr(2 * win_len - 1);	// ��ʼ�����������
	////vector<vector<double> >frame_signal(frame_num, vector<double>(win_len));	// ��֡������
	////frame_signal = enframe(in_array, hann_window, frame_shift);
	////vector<double> one_frame(win_len);		// ��ȡһ֡����
	////int frame_index = 0;	// ��ʼ������֡������
	////cout << "�������������һ֡�źŵ�����أ����������� < " << frame_num << endl;
	////cin >> frame_index;

	////for (int i = 0; i < win_len; i++)
	////{
	////	one_frame[i] = frame_signal[frame_index - 1][i];
	////}
	////corr = xcorr(one_frame, one_frame);
	////GLFWPlot(corr, "Short Time Auto Correlation");

	//// ��ʱƽ�����Ȳ����
	//vector<double> amd(win_len);	// ��ʼ�����������
	//vector<vector<double> >frame_signal(frame_num, vector<double>(win_len));	// ��֡������
	//frame_signal = enframe(in_array, hann_window, frame_shift);
	//vector<double> one_frame(win_len);		// ��ȡһ֡����
	//int frame_index = 0;	// ��ʼ������֡������
	//cout << "�������������һ֡�źŵĶ�ʱƽ�����Ȳ���������� < " << frame_num << endl;
	//cin >> frame_index;

	//for (int i = 0; i < win_len; i++)
	//{
	//	one_frame[i] = frame_signal[frame_index - 1][i];
	//}
	//amd = amdf(one_frame);
	//GLFWPlot(amd, "Short Time Average Magnitude Difference");
//	return 0;
//}