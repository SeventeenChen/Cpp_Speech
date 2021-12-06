//----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：audio.h
// 文件功能描述：语音(wav)文件解析存储类
// 创建者：SeventeenChen
// 时间：2021/11/27
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------
#pragma once
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

typedef char CHAR;
typedef unsigned long DWORD;
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef short SHORT;

const double max_16_bits = 32768;
const double max_8_bits = 128;	//因为归一化到-1到1

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
		void CWave::audioread(string file);	// 从文件中读入内容到内存		
		// void audiowrite(CFile &file);
		template<typename DataType>  //模板声明, DataType表示数据类型
		void Binary2Int(DataType &result, BYTE *ch, int M);	//M个byte转换为result
		void DisplayHeader();	// 控制台显示解析头文件参数
		void Normalization();	// 数值归一化
		// void invNormalization();
};
