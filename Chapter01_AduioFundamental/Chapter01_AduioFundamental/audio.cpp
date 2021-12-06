//----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：audio.cpp
// 文件功能描述：语音（wav）文件解析
// 创建者：SeventeenChen
// 时间：2021/11/27
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------
#include "audio.h"

/*-----------------------------------------------------------------
// 输入：
// 输出：
// 功能描述：类的构造函数
// 作者：SeventeenChen
// 日期：2021/11/27
// 修改人：
// 记录：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
CWave::CWave()	//构造函数
{	
	SetWave();
}

/*-----------------------------------------------------------------
// 输入：类的常量引用
// 输出：
// 功能描述：类的拷贝构造函数
// 作者：SeventeenChen
// 日期：2021/11/27
// 修改人：
// 记录：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
CWave::CWave(const CWave &wave)	//拷贝构造函数
{
	for (int i = 0; i < 4; i++)
	{
		m_wave.szRiffID[i] = wave.m_wave.szRiffID[i];
		m_wave.szRiffFormat[i] = wave.m_wave.szRiffFormat[i];
		m_wave.szFmtID[i] = wave.m_wave.szFmtID[i];
		m_wave.szDataID[i] = wave.m_wave.szDataID[i];
	}
	m_wave.dwRiffSize = wave.m_wave.dwRiffSize;
	m_wave.dwFmtSize = wave.m_wave.dwFmtSize;
	m_wave.wFormatTag = wave.m_wave.wFormatTag;	// WAVE_FORMAT_PCM;//音频格式 .wav
	m_wave.wChannels = wave.m_wave.wChannels;
	m_wave.SampleRate = wave.m_wave.SampleRate;
	m_wave.ByteRate = wave.m_wave.ByteRate;
	m_wave.wBlockAlign = wave.m_wave.wBlockAlign;
	m_wave.wBitsPerSample = wave.m_wave.wBitsPerSample;

	//data chunk
	m_wave.dwDataSize = wave.m_wave.dwDataSize;

	m_dataArray.resize(m_wave.dwDataSize / (m_wave.wBitsPerSample / 8));
	for (int i = 0; i < int(m_wave.dwDataSize /
		(m_wave.wBitsPerSample / 8)); i++)
	{
		m_dataArray[i] = wave.m_dataArray[i];  //实际数据存放区 为指正， 数量为dwDataSize
	}

}

/*-----------------------------------------------------------------
// 输入：类的常量引用
// 输出：
// 功能描述：运算符重载
// 作者：SeventeenChen
// 日期：2021/11/27
// 修改人：
// 记录：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
CWave & CWave::operator=(const CWave &wave)
{
	if (this == &wave)//避免自我赋值，释放内存将错误
		return *this;
	//delete[] m_dataArray;//释放内存
	for (int i = 0; i < 4; i++)
	{
		m_wave.szRiffID[i] = wave.m_wave.szRiffID[i];
		m_wave.szRiffFormat[i] = wave.m_wave.szRiffFormat[i];
		m_wave.szFmtID[i] = wave.m_wave.szFmtID[i];
		m_wave.szDataID[i] = wave.m_wave.szDataID[i];
	}
	m_wave.dwRiffSize = wave.m_wave.dwRiffSize;
	m_wave.dwFmtSize = wave.m_wave.dwFmtSize;
	m_wave.wFormatTag = wave.m_wave.wFormatTag;// WAVE_FORMAT_PCM;//音频格式 .wav
	m_wave.wChannels = wave.m_wave.wChannels;
	m_wave.SampleRate = wave.m_wave.SampleRate;
	m_wave.ByteRate = wave.m_wave.ByteRate;
	m_wave.wBlockAlign = wave.m_wave.wBlockAlign;
	m_wave.wBitsPerSample = wave.m_wave.wBitsPerSample;

	//data chunk
	m_wave.dwDataSize = wave.m_wave.dwDataSize;
	m_dataArray.resize(m_wave.dwDataSize / (m_wave.wBitsPerSample / 8));
	for (int i = 0; i < int(m_wave.dwDataSize /
		(m_wave.wBitsPerSample / 8)); i++)
	{
		m_dataArray[i] = wave.m_dataArray[i];  //实际数据存放区 为指正， 数量为dwDataSize
	}
	return *this;
}

/*-----------------------------------------------------------------
// 输入：
// 输出：
// 功能描述：析构函数
// 作者：SeventeenChen
// 日期：2021/11/27
// 修改人：
// 记录：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
CWave::~CWave()
{
	return;
}

/*-----------------------------------------------------------------
// 输入：对ifstream类型变量file的引用
// 输出：
// 功能描述：读取语音文件到内存，分为文件头和音频数据，对音频数据进行最值归一化
// 作者：SeventeenChen
// 日期：2021/11/27
// 修改人：
// 记录：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
void CWave::audioread(string file)
{
	CHAR buf_byte[4];
	CHAR buf_byte2[2];

	std::ifstream is (file, ios::in | ios::binary);
	if (is)
	{
		is.seekg(0, is.end);
		int length = is.tellg();
		is.seekg(0, is.beg);

		is.read(m_wave.szRiffID, 4 * sizeof(CHAR));

		is.read(buf_byte, 4 * sizeof(CHAR));
		Binary2Int(m_wave.dwRiffSize, reinterpret_cast<unsigned char*>(&buf_byte), 4);
		memset(buf_byte, '\0', sizeof(buf_byte));

		is.read(m_wave.szRiffFormat, 4 * sizeof(CHAR));
		is.read(m_wave.szFmtID, 4 * sizeof(CHAR));

		is.read(buf_byte, 4 * sizeof(CHAR));
		Binary2Int(m_wave.dwFmtSize, reinterpret_cast<unsigned char*>(&buf_byte), 4);
		memset(buf_byte, '\0', sizeof(buf_byte));

		is.read(buf_byte2, 2 * sizeof(CHAR));
		Binary2Int(m_wave.wFormatTag, reinterpret_cast<unsigned char*>(&buf_byte2), 2);
		memset(buf_byte2, '\0', sizeof(buf_byte2));

		is.read(buf_byte2, 2 * sizeof(CHAR));
		Binary2Int(m_wave.wChannels, reinterpret_cast<unsigned char*>(&buf_byte2), 2);

		is.read(buf_byte, 4 * sizeof(CHAR));
		Binary2Int(m_wave.SampleRate, reinterpret_cast<unsigned char*>(&buf_byte), 4);
		memset(buf_byte, '\0', sizeof(buf_byte));

		is.read(buf_byte, 4 * sizeof(CHAR));
		Binary2Int(m_wave.ByteRate, reinterpret_cast<unsigned char*>(&buf_byte), 4);
		memset(buf_byte, '\0', sizeof(buf_byte));

		is.read(buf_byte2, 2 * sizeof(CHAR));
		Binary2Int(m_wave.wBlockAlign, reinterpret_cast<unsigned char*>(&buf_byte2), 2);
		memset(buf_byte2, '\0', sizeof(buf_byte2));

		is.read(buf_byte2, 2 * sizeof(CHAR));
		Binary2Int(m_wave.wBitsPerSample, reinterpret_cast<unsigned char*>(&buf_byte2), 2);
		memset(buf_byte2, '\0', sizeof(buf_byte2));

		char szDataId[5];
		is.read(szDataId, 4 * sizeof(CHAR));
		szDataId[4] = '\0';
		char temp[5] = "data";

		while (strcmp(szDataId, temp) != 0)
		{
			is.read(szDataId, 4 * sizeof(CHAR));

		} 

		is.read(buf_byte, 4 * sizeof(CHAR));
		Binary2Int(m_wave.dwDataSize, reinterpret_cast<unsigned char*>(&buf_byte), 4);
		memset(buf_byte, '\0', sizeof(buf_byte));

		//数据区写
		int ndata = m_wave.dwDataSize / (m_wave.wBitsPerSample / 8);	// 采样点数
		m_dataArray.resize(ndata);
		CHAR temp_byte[1];	
		CHAR temp_short[2];
		for (int i = 0; i < ndata; i++)
		{
			if (m_wave.wBitsPerSample == 16)
			{

				is.read(temp_short, 2 * sizeof(CHAR));
				m_dataArray[i] = temp_short[0]  + temp_short[1] * 256;
				memset(temp_short, '\0', sizeof(temp_short));
			}
			else
			{

				is.read(temp_byte, sizeof(CHAR));
				m_dataArray[i] = temp_byte[0];
				memset(temp_byte, '\0', sizeof(temp_byte));
			}
		}

		is.close();

	}

	Normalization();//归一化为-1~1

}
/*-----------------------------------------------------------------
// 输入：
// 输出：
// 功能描述：构造函数的定义
// 作者：SeventeenChen
// 日期：2021/11/27
// 修改人：
// 记录：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
void CWave::SetWave()		// 定义识别字
{
	m_wave.szRiffID[0] = 'R'; m_wave.szRiffID[1] = 'I';
	m_wave.szRiffID[2] = 'F'; m_wave.szRiffID[3] = 'F';
	
	//dwRiffSize;
	m_wave.szRiffFormat[0] = 'W'; m_wave.szRiffFormat[1] = 'A';
	m_wave.szRiffFormat[2] = 'V'; m_wave.szRiffFormat[3] = 'E';

	//fmt chunk
	m_wave.szFmtID[0] = 'f'; m_wave.szFmtID[1] = 'm';
	m_wave.szFmtID[2] = 't'; m_wave.szFmtID[3] = ' ';

	//dwFmtSize;
	m_wave.wFormatTag = 1;	// WAVE_FORMAT_PCM
	m_wave.wChannels = 1;	//默认为单通道

	//data chunk
	m_wave.szDataID[0] = 'd'; m_wave.szDataID[1] = 'a';
	m_wave.szDataID[2] = 't'; m_wave.szDataID[3] = 'a';

	//DWORD dwDataSize;
	m_dataArray.resize(0);
}

/*-----------------------------------------------------------------
// 输入：转换结果result的引用，输入字节指针ch，字节位数M
// 输出：
// 功能描述：2进制ch转int类型变量result
// 作者：SeventeenChen
// 日期：2021/11/27
// 修改人：
// 记录：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
template<typename DataType>  //模板声明，其中T为类型参数
void CWave::Binary2Int(DataType &result, BYTE *ch, int M)
{
	result = 0;
	DataType temp = 0;
	for (int i = 0; i < M; i++)
	{
		temp = DataType(ch[i]);
		result += DataType(temp*exp2(8 * i));
	}
}

/*-----------------------------------------------------------------
// 输入：
// 输出：
// 功能描述：音频数据的最值归一化
// 作者：SeventeenChen
// 日期：2021/11/27
// 修改人：
// 记录：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
void CWave::Normalization()
{
	int ndata = m_wave.dwDataSize / (m_wave.wBitsPerSample / 8);	// 采样点数
	if (m_wave.wBitsPerSample == 16)		// 16位存储
	{
		for (int i = 0; i < ndata; i++)
		{
			m_dataArray[i] = m_dataArray[i] / max_16_bits;
		}
	}
	else    // 8位存储   
	{
		for (int i = 0; i < ndata; i++)
		{
			m_dataArray[i] = m_dataArray[i] / max_8_bits;
		}
	}

}

/*-----------------------------------------------------------------
// 输入：
// 输出：wav文件头中相关参数
// 功能描述：控制台显示wav文件头数据
// 作者：SeventeenChen
// 日期：2021/11/27
// 修改人：
// 记录：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
void CWave::DisplayHeader()
{
	std::cout << "RIFF ID:\t" << m_wave.szRiffID <<endl;
	std::cout << "RIFF Size:\t" << m_wave.dwRiffSize << endl;
	std::cout << "FMT ID:\t" << m_wave.szFmtID << endl;
	std::cout << "FMT Size:\t" << m_wave.dwFmtSize << endl;
	std::cout << "Format Tag:\t" << m_wave.wFormatTag << endl;
	std::cout << "Channels Number:\t" << m_wave.wChannels << endl;
	std::cout << "Sample Rate:\t" << m_wave.SampleRate << endl;
	std::cout << "Byte Rate:\t" << m_wave.ByteRate << endl;
	std::cout << "Block Align:\t" << m_wave.wBlockAlign << endl;
	std::cout << "Bit Rate:\t" << m_wave.wBitsPerSample << endl;
	std::cout << "Data Size:\t" << m_wave.dwDataSize << endl;
}