/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����universal.h
// �ļ����������������źŵ�ͨ�ò�������д���ز��������Ʋ��Ρ��Ӵ���֡��
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/21
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// ����汾��VS2015
//----------------------------------------------------------------*/
#pragma once
#include <string>
#include <iomanip>
#include <vector>
#include <numeric>
#include <tuple>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <cstdint>
#include <memory>
#include <sstream>
#include <algorithm>
#include "spline.h"
using namespace std;
using namespace SplineSpace;

typedef char CHAR;
typedef unsigned long DWORD;
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef short SHORT;

const double max_16_bits = 32768;
const double max_8_bits = 128;	//��Ϊ��һ����-1��1

#ifndef _pi_
#define _pi_  3.1415926535898
#endif
#define FOURCC uint32_t	

#define MAKE_FOURCC(a,b,c,d) \
( ((uint32_t)d) | ( ((uint32_t)c) << 8 ) | ( ((uint32_t)b) << 16 ) | ( ((uint32_t)a) << 24 ) )

template <char ch0, char ch1, char ch2, char ch3> struct MakeFOURCC { enum { value = (ch0 << 0) + (ch1 << 8) + (ch2 << 16) + (ch3 << 24) }; };
/*-----------------------------------------------------------------
// ����������wav�ļ�ͷ�ṹ��
// ���ߣ�SeventeenChen
// ���ڣ�2021/11/27
// �޸��ˣ�
// ��¼��
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
struct Wave		// 44�ֽ� �ο���https://docs.fileformat.com/audio/wav/
{
	//RIFF ͷ
	CHAR szRiffID[4];	// 1-4��"RIFF"
						// typedef unsigned long DWORD; 
	DWORD dwRiffSize;	// 5-8������RIFF���Լ��⣬�����ļ��ĳ��ȣ����ֽ��� - 8
	CHAR szRiffFormat[4];	// 9-12���ļ����ͣ��� 'WAVE' / 'AVI' 

							//fmt chunk
	CHAR szFmtID[4];	// 13-16�������ASCIIʶ���֣�'fmt' / 'data'
	DWORD dwFmtSize;	// 17-20�������г��ĸ�ʽ���ݳ��ȣ�һ��Ϊ16
	WORD wFormatTag;	// 21-22�������ʽ��PCM:1, 2�ֽ�int��
	WORD wChannels;		// 23-24��ͨ������2�ֽ�int
	DWORD SampleRate;	// 25-28�������ʣ�32�ֽ�int��44100��CD��/48000��DAT��Hz
	DWORD ByteRate;		// 29-32���ֽ��ʣ�(������ * ����λ�� * ͨ����) / 8
	WORD wBlockAlign;	// 33-34����������ݣ�������λ�� * ͨ������/ 8�� һ֡�ֽ���
	WORD wBitsPerSample;	// 35-36������λ��ÿ���������λ���� e.g. 16

							//data chunk
	CHAR szDataID[4];	// 37-40�����ݿ��ͷ, �������������ʼ
	DWORD dwDataSize;	// 41-44����Ƶ���ݴ�С���ֽڣ����ļ����ֽ��� - 44�� duration = szDataID / BytesRate
};

/*-----------------------------------------------------------------
// ����������Cwave�࣬�����ļ�ͷ����Ƶ���ݶ��󼰻�����Ա����
// ���ߣ�SeventeenChen
// ���ڣ�2021/11/27
// �޸��ˣ�
// ��¼��
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
class CWave
{
public: // �������л�����
	CWave();	// ���캯��
				//DECLARE_SERIAL(CWave)
	CWave(const CWave &wave);	// �������캯����wave��һ���������ã����ڳ�ʼ����һ������
								// ��Ա�����������ͷ���ֵ��ʹ�����õķ�ʽ��������Ϊ�������ã������ɸ�������ֵ
	CWave & operator=(const CWave &wave);	// ��ֵ��Ա����������Ķ�����и�ֵ
	virtual ~CWave();	// ��������
public:		// ���Ա����
	Wave m_wave;	// wav�ļ�ͷ���ṹ�壩
					// vector���ܹ�����������͵Ķ�̬����
	std::vector<double> m_dataArray;	// ��Ƶ����
public:
	void SetWave();		//����.wav�ļ���Ĭ����ʽ
	void CWave::read(string file);	// ���ļ��ж������ݵ��ڴ�		
										
	template<typename DataType>  //ģ������, DataType��ʾ��������
	void Binary2Int(DataType &result, BYTE *ch, int M);	//M��byteת��Ϊresult
	void DisplayHeader();	// ����̨��ʾ����ͷ�ļ�����
	void Normalization();	// ��ֵ��һ��
							// void invNormalization();
};

/*-----------------------------------------------------------------
// ���룺wav�ļ�����string���������ʣ�int�����Ƿ���ʾ�ļ�ͷ��bool��
// �����wav����ͷ����������̨��wav��Ƶ���ݣ���һ������txt�ļ�
// ���������������źŵĶ�ȡ��������Ƶ�����������
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/06
// �޸��ˣ�SeventeenChen
// ��¼����ͬʱ������Ƶ���������Ƶ��
// ���ڣ�2021/12/07
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
std::tuple<vector <double>, int> audioread(string filepath, int fs, bool disp_flag);

std::tuple<vector<double>, int> GetFileData(string WcsTrainDataName, int fs, bool disp_flag);
//��ȡ�ļ����ݣ�������Ƶ���ݺͲ�����

void GetInputData(std::vector<double> &in_dataArray, std::vector<double>&out_dataArray, int flag);
//GetInputData:���ڴ���Ƶ�ļ��л�ȡ���ڴ�������ݣ�in_dataArray�������������ݣ�out_dataArray��������ݡ�
//flag==2ʱ��out_dataArrayΪin_dataArray��ż���������
//flag==1ʱ��out_dataArray=in_dataArray

/*-----------------------------------------------------------------
// ���룺���������ݣ�vector��������ͼƬtitle���ַ����飩
// �����
// ����������openGL���Ʋ���ͼ
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/11
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �汾��
-----------------------------------------------------------------*/
int GLFWPlot(std::vector<double> in_dataArray, const char *title);

/*-----------------------------------------------------------------
// ���룺���������ݣ�vector��
// �����
// �������������Ʋ���ͼ
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/11
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �汾��
-----------------------------------------------------------------*/
void audioplot(std::vector<double> in_dataArray);

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
std::vector<vector<double> > enframe(vector<double> in_array, vector<double> win, int frame_shift);

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
std::vector<double> window(int window_length, string window_type);

/*-----------------------------------------------------------------
// ���룺���ز����źţ�һά���� vector����Ŀ������ʣ�ԭʼ������
// ������ز������źţ�һά���� vector��
// ����������һά�źŵ��ز���
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/11
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �汾��
-----------------------------------------------------------------*/
std::vector<double> resample(vector<double> in_array, int target_fs, int source_fs);

// Format chunk data field
struct Wave_format {

	uint16_t format_tag;      // WAVE�����ݸ�ʽ��PCM���ݸ�ֵΪ1
	uint16_t channels;        // ������
	uint32_t sample_per_sec;  // ������
	uint32_t bytes_per_sec;   // ���ʣ�channels * sample_per_sec * bits_per_sample / 8
	uint16_t block_align;     // ��Ƶ���ݿ飬ÿ�β�����������ݴ�С��channels * bits_per_sample / 8
	uint16_t bits_per_sample; // ����λ����8��16��32��
	uint16_t ex_size;         // ��չ��Ĵ�С�����ӿ�Ĵ�С

	Wave_format()
	{
		format_tag = 1; // PCM format data
		ex_size = 0; // don't use extesion field

		channels = 0;
		sample_per_sec = 0;
		bytes_per_sec = 0;
		block_align = 0;
		bits_per_sample = 0;
	}

	Wave_format(uint16_t nb_channel, uint32_t sample_rate, uint16_t sample_bits)
		:channels(nb_channel), sample_per_sec(sample_rate), bits_per_sample(sample_bits)
	{
		format_tag = 0x01;                                           // PCM format data
		bytes_per_sec = channels * sample_per_sec * bits_per_sample / 8; // ����
		block_align = channels * bits_per_sample / 8;
		ex_size = 0;                                               // don't use extension field
	}
};

// The basic chunk of RIFF file format
struct Base_chunk {

	FOURCC fcc;    // FourCC id
	uint32_t cb_size; // ������Ĵ�С

	Base_chunk(FOURCC fourcc)
		: fcc(fourcc)
	{
		cb_size = 0;
	}
};

/*

���ݸ�ʽΪPCM��WAV�ļ��Ļ����ṹ
--------------------------------
| Base_chunk | RIFF	|
---------------------
|	WAVE            |
---------------------
| Base_chunk | fmt  |	Header
---------------------
| Wave_format|      |
---------------------
| Base_chunk | data |
---------------------------------
|    PCM data                   |
---------------------------------
*/

/*

���ݸ�ʽΪPCM��WAV�ļ�ͷ
--------------------------------
| Base_chunk | RIFF	|
---------------------
|	WAVE            |
---------------------
| Base_chunk | fmt  |	Header
---------------------
| Wave_format|      |
---------------------
| Base_chunk | data |
--------------------------------
*/
struct Wave_header {

	shared_ptr<Base_chunk> riff;
	FOURCC wave_fcc;
	shared_ptr<Base_chunk> fmt;
	shared_ptr<Wave_format>  fmt_data;
	shared_ptr<Base_chunk> data;

	Wave_header(uint16_t nb_channel, uint32_t sample_rate, uint16_t sample_bits)
	{
		riff = make_shared<Base_chunk>(MakeFOURCC<'R', 'I', 'F', 'F'>::value);
		fmt = make_shared<Base_chunk>(MakeFOURCC<'f', 'm', 't', ' '>::value);
		fmt->cb_size = 18;

		fmt_data = make_shared<Wave_format>(nb_channel, sample_rate, sample_bits);
		data = make_shared<Base_chunk>(MakeFOURCC<'d', 'a', 't', 'a'>::value);

		wave_fcc = MakeFOURCC<'W', 'A', 'V', 'E'>::value;
	}

	Wave_header()
	{
		riff = nullptr;
		fmt = nullptr;

		fmt_data = nullptr;
		data = nullptr;

		wave_fcc = 0;
	}
};

class  CWaveFile
{

public:

	CWaveFile()
	{
		header = nullptr;
		data = nullptr;
	}

	// Write wav file
	bool static write(const string& filename, const Wave_header &header, void *data, uint32_t length)
	{
		ofstream ofs(filename, ofstream::binary);
		if (!ofs)
			return false;

		// Calculate size of RIFF chunk data
		header.data->cb_size = ((length + 1) / 2) * 2;
		header.riff->cb_size = 4 + 4 + header.fmt->cb_size + 4 + 4 + header.data->cb_size + 4;

		// Write header

		// Write RIFF
		char *chunk = (char*)header.riff.get();
		ofs.write(chunk, sizeof(Base_chunk));

		// Write WAVE fourcc
		ofs.write((char*)&(header.wave_fcc), 4);

		// Write fmt
		chunk = (char*)header.fmt.get();
		ofs.write(chunk, sizeof(Base_chunk));

		// Write fmt_data
		chunk = (char*)header.fmt_data.get();
		ofs.write(chunk, header.fmt->cb_size);

		// Write data
		chunk = (char*)header.data.get();
		ofs.write(chunk, sizeof(Base_chunk));

		// Write data
		ofs.write((char*)data, length);

		ofs.close();
		return true;
	}

	bool read(const string &filename)
	{
		if (!read_header(filename))
			return false;

		// PCM ��������ļ�ͷλ�õ�ƫ������ +8��RIFF fourcc +4��size + 4��
		uint32_t offset = header->riff->cb_size - header->data->cb_size + 8;
		data = unique_ptr<uint8_t[]>(new uint8_t[header->data->cb_size]);

		ifstream ifs(filename, ifstream::binary);
		if (!ifs)
			return false;

		ifs.seekg(offset);

		ifs.read((char*)(data.get()), header->data->cb_size);

		return true;
	}

private:

	// Read wav file header
	bool read_header(const string &filename)
	{
		ifstream ifs(filename, ifstream::binary);
		if (!ifs)
			return false;

		header = make_unique<Wave_header>();

		// Read RIFF chunk
		FOURCC fourcc;
		ifs.read((char*)&fourcc, sizeof(FOURCC));

		if (fourcc != MakeFOURCC<'R', 'I', 'F', 'F'>::value) // �ж��ǲ���RIFF
			return false;
		Base_chunk riff_chunk(fourcc);
		ifs.read((char*)&riff_chunk.cb_size, sizeof(uint32_t));

		header->riff = make_shared<Base_chunk>(riff_chunk);

		// Read WAVE FOURCC
		ifs.read((char*)&fourcc, sizeof(FOURCC));
		if (fourcc != MakeFOURCC<'W', 'A', 'V', 'E'>::value)
			return false;
		header->wave_fcc = fourcc;

		// Read format chunk
		ifs.read((char*)&fourcc, sizeof(FOURCC));
		if (fourcc != MakeFOURCC<'f', 'm', 't', ' '>::value)
			return false;

		Base_chunk fmt_chunk(fourcc);
		ifs.read((char*)&fmt_chunk.cb_size, sizeof(uint32_t));

		header->fmt = make_shared<Base_chunk>(fmt_chunk);

		// Read format data
		Wave_format format;
		ifs.read((char*)&format, fmt_chunk.cb_size);

		// Read data chunk
		ifs.read((char*)&fourcc, sizeof(fourcc));
		if (fourcc != MakeFOURCC<'d', 'a', 't', 'a'>::value)
			return false;

		Base_chunk data_chunk(fourcc);
		ifs.read((char*)&data_chunk.cb_size, sizeof(uint32_t));

		header->data = make_shared<Base_chunk>(data_chunk);

		ifs.close();

		return true;
	}

public:
	shared_ptr<Wave_header> header;
	unique_ptr<uint8_t[]> data;
};

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
void audiowrite(vector<double> y, int fs, string filepath);