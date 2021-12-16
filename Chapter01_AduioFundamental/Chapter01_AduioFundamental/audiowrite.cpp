//----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����audiowrite.cpp
// �ļ����������������źŵ�д��
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/16
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// ����汾��VS2015
//----------------------------------------------------------------
#include "audiowrite.h"

/*-----------------------------------------------------------------
// ���룺�����ź�y��������fs���洢��ַfilepath
// �����filepath.wav�ļ�
// ���������������źŵ�д��洢
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/16
// TODO���ֽ�֧��16λ�洢�����Ż�������λ������8/32�ȣ�
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
void audiowrite(vector<double> y, int fs, string filepath)
{
	// Write WAv�ļ�	
	int channel_num = 1, bitrate = 16;
	Wave_header header(channel_num, fs, bitrate);	//e.g. Wave_header header(1, 48000, 16);
	uint32_t len_arr = y.size();				// ���鳤��
	uint32_t length = len_arr * bitrate / 8;	// �ֽ���
	vector<int> int_array(len_arr);
	int16_t *data = new int16_t[length];
	
	for (int i = 0; i < len_arr; i++)
	{
		int_array[i] = y[i] * 32678;	// ���� -32768 ~ 32768	
		data[i] = int_array[i];			// data��ÿ������ռ�������ֽڣ�16λ��
	}
	CWaveFile::write(filepath, header, data, length);

}