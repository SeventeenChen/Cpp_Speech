/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：universal.h
// 文件功能描述：语音信号的通用操作（读写、重采样、绘制波形、加窗分帧）
// 创建者：SeventeenChen
// 时间：2021/12/21
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
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
const double max_8_bits = 128;	//因为归一化到-1到1

#ifndef _pi_
#define _pi_  3.1415926535898
#endif
#define FOURCC uint32_t	

#define MAKE_FOURCC(a,b,c,d) \
( ((uint32_t)d) | ( ((uint32_t)c) << 8 ) | ( ((uint32_t)b) << 16 ) | ( ((uint32_t)a) << 24 ) )

template <char ch0, char ch1, char ch2, char ch3> struct MakeFOURCC { enum { value = (ch0 << 0) + (ch1 << 8) + (ch2 << 16) + (ch3 << 24) }; };
/*-----------------------------------------------------------------
// 功能描述：wav文件头结构体
// 作者：SeventeenChen
// 日期：2021/11/27
// 修改人：
// 记录：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
struct Wave		// 44字节 参考：https://docs.fileformat.com/audio/wav/
{
	//RIFF 头
	CHAR szRiffID[4];	// 1-4："RIFF"
						// typedef unsigned long DWORD; 
	DWORD dwRiffSize;	// 5-8：除了RIFF及自己外，整个文件的长度，总字节数 - 8
	CHAR szRiffFormat[4];	// 9-12：文件类型，如 'WAVE' / 'AVI' 

							//fmt chunk
	CHAR szFmtID[4];	// 13-16：区块的ASCII识别字，'fmt' / 'data'
	DWORD dwFmtSize;	// 17-20：上述列出的格式数据长度，一般为16
	WORD wFormatTag;	// 21-22：编码格式（PCM:1, 2字节int）
	WORD wChannels;		// 23-24：通道数，2字节int
	DWORD SampleRate;	// 25-28：采样率，32字节int，44100（CD）/48000（DAT）Hz
	DWORD ByteRate;		// 29-32：字节率：(采样率 * 采样位宽 * 通道数) / 8
	WORD wBlockAlign;	// 33-34：块对齐内容：（采样位宽 * 通道数）/ 8； 一帧字节数
	WORD wBitsPerSample;	// 35-36：采样位宽（每个样本点的位数） e.g. 16

							//data chunk
	CHAR szDataID[4];	// 37-40：数据块的头, 标记数据区的起始
	DWORD dwDataSize;	// 41-44：音频数据大小（字节），文件总字节数 - 44； duration = szDataID / BytesRate
};

/*-----------------------------------------------------------------
// 功能描述：Cwave类，包括文件头，音频数据对象及基本成员函数
// 作者：SeventeenChen
// 日期：2021/11/27
// 修改人：
// 记录：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
class CWave
{
public: // 仅从序列化创建
	CWave();	// 构造函数
				//DECLARE_SERIAL(CWave)
	CWave(const CWave &wave);	// 拷贝构造函数，wave是一个对象引用，用于初始化另一个对象
								// 成员函数，参数和返回值都使用引用的方式，且输入为常量引用，即不可更改其数值
	CWave & operator=(const CWave &wave);	// 赋值成员函数，对类的对象进行赋值
	virtual ~CWave();	// 析构函数
public:		// 类成员函数
	Wave m_wave;	// wav文件头（结构体）
					// vector：能够存放任意类型的动态数组
	std::vector<double> m_dataArray;	// 音频数据
public:
	void SetWave();		//设置.wav文件的默认形式
	void CWave::read(string file);	// 从文件中读入内容到内存		
										
	template<typename DataType>  //模板声明, DataType表示数据类型
	void Binary2Int(DataType &result, BYTE *ch, int M);	//M个byte转换为result
	void DisplayHeader();	// 控制台显示解析头文件参数
	void Normalization();	// 数值归一化
							// void invNormalization();
};

/*-----------------------------------------------------------------
// 输入：wav文件名（string），采样率（int），是否显示文件头（bool）
// 输出：wav语音头数据至控制台，wav音频数据（归一化）至txt文件
// 功能描述：语音信号的读取，返回音频数据与采样率
// 作者：SeventeenChen
// 日期：2021/12/06
// 修改人：SeventeenChen
// 记录：可同时返回音频数据与采样频率
// 日期：2021/12/07
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
std::tuple<vector <double>, int> audioread(string filepath, int fs, bool disp_flag);

std::tuple<vector<double>, int> GetFileData(string WcsTrainDataName, int fs, bool disp_flag);
//读取文件内容，返回音频数据和采样率

void GetInputData(std::vector<double> &in_dataArray, std::vector<double>&out_dataArray, int flag);
//GetInputData:用于从音频文件中获取用于处理的数据，in_dataArray是输入语音数据，out_dataArray是输出数据。
//flag==2时，out_dataArray为in_dataArray的偶数序号数；
//flag==1时，out_dataArray=in_dataArray

/*-----------------------------------------------------------------
// 输入：待绘制数据（vector），绘制图片title（字符数组）
// 输出：
// 功能描述：openGL绘制波形图
// 作者：SeventeenChen
// 日期：2021/12/11
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 日期：
// 版本：
-----------------------------------------------------------------*/
int GLFWPlot(std::vector<double> in_dataArray, const char *title);

/*-----------------------------------------------------------------
// 输入：待绘制数据（vector）
// 输出：
// 功能描述：绘制波形图
// 作者：SeventeenChen
// 日期：2021/12/11
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 日期：
// 版本：
-----------------------------------------------------------------*/
void audioplot(std::vector<double> in_dataArray);

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
std::vector<vector<double> > enframe(vector<double> in_array, vector<double> win, int frame_shift);

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
std::vector<double> window(int window_length, string window_type);

/*-----------------------------------------------------------------
// 输入：待重采样信号（一维数组 vector），目标采样率，原始采样率
// 输出：重采样后信号（一维数组 vector）
// 功能描述：一维信号的重采样
// 作者：SeventeenChen
// 日期：2021/12/11
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 日期：
// 版本：
-----------------------------------------------------------------*/
std::vector<double> resample(vector<double> in_array, int target_fs, int source_fs);

// Format chunk data field
struct Wave_format {

	uint16_t format_tag;      // WAVE的数据格式，PCM数据该值为1
	uint16_t channels;        // 声道数
	uint32_t sample_per_sec;  // 采样率
	uint32_t bytes_per_sec;   // 码率，channels * sample_per_sec * bits_per_sample / 8
	uint16_t block_align;     // 音频数据块，每次采样处理的数据大小，channels * bits_per_sample / 8
	uint16_t bits_per_sample; // 量化位数，8、16、32等
	uint16_t ex_size;         // 扩展块的大小，附加块的大小

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
		bytes_per_sec = channels * sample_per_sec * bits_per_sample / 8; // 码率
		block_align = channels * bits_per_sample / 8;
		ex_size = 0;                                               // don't use extension field
	}
};

// The basic chunk of RIFF file format
struct Base_chunk {

	FOURCC fcc;    // FourCC id
	uint32_t cb_size; // 数据域的大小

	Base_chunk(FOURCC fourcc)
		: fcc(fourcc)
	{
		cb_size = 0;
	}
};

/*

数据格式为PCM的WAV文件的基本结构
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

数据格式为PCM的WAV文件头
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

		// PCM 数据相对文件头位置的偏移量， +8（RIFF fourcc +4，size + 4）
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

		if (fourcc != MakeFOURCC<'R', 'I', 'F', 'F'>::value) // 判断是不是RIFF
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
// 输入：语音信号y，采样率fs，存储地址filepath
// 输出：filepath.wav文件
// 功能描述：语音信号的写入存储
// 作者：SeventeenChen
// 日期：2021/12/16
// TODO：现仅支持16位存储，待优化至其他位数（如8/32等）
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
void audiowrite(vector<double> y, int fs, string filepath);