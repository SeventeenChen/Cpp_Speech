#include "enframe.h"

/*-----------------------------------------------------------------
// ���룺�����ź�in_array��������win��֡��frame_shift
// �������֡�����飬֡�� x ֡��
// ������������֡
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/09
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
std::vector<vector<double> > enframe(vector<double> in_array, vector<double> win, int frame_shift)
{
	int len_x, len_win, frame_num;
	
	len_x = in_array.size();	// ���ݳ���
	len_win = win.size();		// ������֡����
	if (frame_shift == 0)
	{
		frame_shift = len_win;		// ��δ����֡�ƣ���֡��=֡��
	}
	frame_num = (len_x - len_win + frame_shift) / frame_shift;	// ֡��
	// ��ʼ����֡�����飺֡�� x ֡��
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
// ���룺������int���������ͣ�����"default"/����"hamming"/����"hanning" 
// �������������vector��
// ������������������ֵ
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/09
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// �汾��
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