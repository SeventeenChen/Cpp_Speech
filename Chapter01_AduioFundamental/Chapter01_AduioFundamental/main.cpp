//----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����main.cpp
// �ļ����������������źŻ�����������������
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/06
// �޸��ˣ�SeventeenChen
// ʱ�䣺2021/12/06
// �޸�˵����ʵ�������źŵĶ�ȡ
// ����汾��VS2015
//----------------------------------------------------------------
#include "audioread.h"

int main()
{
	string filepath = "bluesky3.wav";
	int fs = 16000;
	bool disp_flag = true;
	// ע����Ŀ�Ҽ�-����-ϵͳ-��ϵͳ-����̨
	audioread(filepath, fs, disp_flag);	// �����źŵĶ�ȡ

	return 0;
}

