/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����stfms.cpp
// �ļ����������������źŵĶ�ʱ����Ҷ�任
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/25
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// ����汾��VS2015
//----------------------------------------------------------------*/

#include "stftms.h"

/*-----------------------------------------------------------------
// ���룺��Ҫ���ж�ʱ����Ҷ�任���ź�in_array��������win���������˱任����nfft(>=����������)��֡��inc
// �������ʱ����Ҷ�任�����ʵ�����鲿��(nfft/2+1) x ֡��
// ���������������źŵĶ�ʱ��ʱ����Ҷ�任
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/25
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
vector<vector <complex<double> > >stftms(vector<double>in_array, vector<double>win, int nfft, int inc)
{
	int inlen = 0, wlen = 0, frame_num = 0; // �����źų���, ���������ȣ�֡����ʼ��
	int i = 0, j = 0, k = 0;	// ��ʼ��ѭ������
	inlen = in_array.size();	// �����źų���
	wlen = win.size();			// ����������
	frame_num = 1 + (inlen-wlen)/inc;	// ֡��
	vector<vector<double> >frame_signal(frame_num, vector<double>(wlen));	// ��ʼ����֡������
	vector<vector <complex<double> > >d(frame_num, vector<complex<double> >((1 + nfft / 2)));	// ��ʼ���������
	frame_signal = enframe(in_array, win, inc);	// ��֡������
	fftw_complex *in, *out;
	fftw_plan p;
	in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nfft);
	out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * nfft);
	for (k = 0; k < frame_num; k++)
	{
		for (i = 0; i < nfft; i++)
		{
			if (i < wlen)
			{
				in[i][0] = frame_signal[k][i];
				in[i][1] = 0.0;
			}
			else
			{
				in[i][0] = 0.0;
				in[i][1] = 0.0;
			}
		}
		p = fftw_plan_dft_1d(nfft, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
		fftw_execute(p); // repeat as needed
		for (j = 0; j < 1 + nfft / 2; j++)
		{
			d[k][j] = complex<double>(out[j][0], out[j][1]);
		}
	}
	fftw_destroy_plan(p);
	fftw_free(in);
	fftw_free(out);

	return d;
}

