/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：universal.cpp
// 文件功能描述：语音信号的通用操作（读写、重采样、绘制波形、加窗分帧）
// 创建者：SeventeenChen
// 时间：2021/12/21
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/

#include "universal.h"
#include "spline.h"
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
void CWave::read(string file)
{
	CHAR buf_byte[4];
	CHAR buf_byte2[2];

	std::ifstream is(file, ios::in | ios::binary);
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
				m_dataArray[i] = temp_short[0] + temp_short[1] * 256;
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
	std::cout << "RIFF ID:\t" << m_wave.szRiffID << endl;
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

/*-----------------------------------------------------------------
// 输入：wav文件名（string），采样率（int），是否显示文件头（bool）
// 输出：在控制台打印wav语音头参数，wav音频数据（归一化）至同名txt文件
// 功能描述：语音信号的读取
// TODO：完善成可读取系统路径
// 作者：SeventeenChen
// 日期：2021/12/06
// 修改人：SeventeenChen
// 记录：可同时返回音频数据与采样频率
// 日期：2021/12/07
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
std::tuple<vector <double>, int> audioread(string filepath, int fs, bool disp_flag)
{

	std::tuple<vector <double>, int> in_data;
	std::vector<double> in_array;

	in_data = GetFileData(filepath, fs, disp_flag);	// 从文件读取音频数据
	in_array = std::get<0>(in_data);
	fs = std::get<1>(in_data);

	std::string filename = filepath.substr(0, filepath.rfind('.'));
	std::string textname = filename + ".txt";

	std::ofstream fout(textname);
	fout << std::setprecision(10);

	for (auto const& x : in_array)
	{
		fout << x << '\n';
	}

	return make_tuple(in_array, fs);
}

/*-----------------------------------------------------------------
// 输入：文件名，采样频率（任意int类型），显示头文件标记（bool型）
// 输出：tuple型（音频数据, 实际采样频率）
// 功能描述：读取wav文件至内存，提取音频数据及采样频率
// 作者：SeventeenChen
// 日期：2021/11/27
// 修改人：SeventeenChen
// 记录：可同时返回音频数据与采样频率
// 日期：2021/12/07
// 修改人：SeventeenChen
// 记录：增加文件不能打开时的抛出异常
// 日期：2021/12/08
// 版本：
-----------------------------------------------------------------*/
std::tuple<vector<double>, int> GetFileData(string file, int fs, bool disp_flag)
{
	CWave wave;
	std::ifstream ifs(file, ios::in | ios::binary);

	if (!ifs)
	{
		throw "File could not be opened";		// 异常处理
		return make_tuple(std::vector<double>(0), 0);
	}
	else
	{
		wave.read(file);	// 读入wav文件
		if (disp_flag)
		{
			std::cout << "wav header: " << endl;
			wave.DisplayHeader();
		}
		ifs.close();
		fs = int(wave.m_wave.SampleRate);	// 读取采样率
		std::vector<double> in_dataArray;	// 读入音频数据
		GetInputData(wave.m_dataArray, in_dataArray, wave.m_wave.wChannels);	// 取单通道
		return make_tuple(in_dataArray, fs);
	}

}

/*-----------------------------------------------------------------
// 输入：读入数据，输出数据（动态数组的引用）；通道数标记flag
// 输出：单通道音频数据
// 功能描述：读取wav文件，如果是双通道音频，只取左声道
// 作者：SeventeenChen
// 日期：2021/11/27
// 修改人：
// 记录：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
void GetInputData(std::vector<double> &in_dataArray, std::vector<double>&out_dataArray, int flag)
{
	int nDataLength = in_dataArray.size();
	int nSampleLength = 0;//样本长度
	if (2 == flag)
	{
		nSampleLength = nDataLength / 2;
		out_dataArray.resize(nSampleLength);
		for (int i = 0; i < nSampleLength; i++)
		{
			out_dataArray[i] = in_dataArray[2 * i];//取左声道
		}
	}

	else
	{
		nSampleLength = nDataLength;
		out_dataArray.resize(nSampleLength);
		out_dataArray = in_dataArray;
	}
}

/*-----------------------------------------------------------------
// 输入：音频数据（vector），图像标题（string）
// 输出：
// 功能描述：利用openGL绘制音频波形
// 作者：SeventeenChen
// 日期：2021/12/08
// 修改人：SeventeenChen
// 记录：添加title标记
// 日期：2021/12/10
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
int GLFWPlot(std::vector<double> in_dataArray, const char *title)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800, 800, title, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		/*your draw*/
		audioplot(in_dataArray);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;

}

/*-----------------------------------------------------------------
// 输入：音频数据
// 输出：
// 功能描述：利用openGL绘制音频波形
// 作者：SeventeenChen
// 日期：2021/12/08
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
void audioplot(std::vector<double> in_dataArray)
{
	glClearColor(0.8, 0.8, 0.8, 0.8);	// 窗口底色
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(2);		//设置线段宽度
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);	// 线段颜色

	int i = 0;
	float xstart = -1.0;
	float ystart = 0.0;
	float xend = 0.0;
	float yend = 0.0;
	float temp = 0.0;

	int wav_length = in_dataArray.size();
	float x_stepsize;
	x_stepsize = 2.0 / wav_length;	// 根据数据长度计算步长，使得绘制数据水平铺满（-1~1）
	for (i; i < wav_length; i++)
	{
		xstart = xstart + x_stepsize;
		ystart = temp;
		xend = xstart + x_stepsize;

		yend = in_dataArray[i];

		glVertex2f(xstart, ystart);	// 折线起点
		glVertex2f(xend, yend);		// 折现终点

		temp = yend;    //终点作为下一次的起点
	}

	glEnd();
}

/*-----------------------------------------------------------------
// 输入：语音信号in_array，窗函数win，帧移frame_shift
// 输出：分帧后数组，帧数 x 帧长
// 功能描述：加窗分帧
// 作者：SeventeenChen
// 日期：2021/12/09
// 修改人：
// 记录：
// 日期：
// 修改人：
// 记录：
// 版本：
-----------------------------------------------------------------*/
std::vector<vector<double> > enframe(vector<double> in_array, vector<double> win, int frame_shift)
{
	int len_x, len_win, frame_num;

	len_x = in_array.size();	// 数据长度
	len_win = win.size();		// 窗长（帧长）
	if (frame_shift == 0)
	{
		frame_shift = len_win;		// 若未设置帧移，则帧移=帧长
	}
	frame_num = (len_x - len_win + frame_shift) / frame_shift;	// 帧数
																// 初始化分帧后数组：帧数 x 帧长
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
std::vector<double> resample(vector<double> in_array, int target_fs, int source_fs)
{
	int source_len, target_len;
	double duration;	// 序列时长初始化（秒）
	double resample_stepsize = (double)source_fs / target_fs;	// 重采样序列自变量步长
	double leftBound = 0, rightBound = 0;	//边界导数

	source_len = in_array.size();		// 已知序列长度
	std::vector<double> source_x(source_len);	// 已知序列自变量初始化
	std::iota(source_x.begin(), source_x.end(), 0);	// 递增序列
													// vector ---> array
	double *x0 = new double[source_len];	// 已知序列自变量数组初始化
	if (!source_x.empty())
	{
		memcpy(x0, &source_x[0], source_len * sizeof(double));	// 赋值
	}
	double *y0 = new double[source_len];	// 已知序列因变量数组初始化
	if (!in_array.empty())
	{
		memcpy(y0, &in_array[0], source_len * sizeof(double));
	}
	Spline sp(x0, y0, source_len, GivenSecondOrder, leftBound, rightBound);
	duration = double(source_len) / source_fs;
	target_len = floor(duration * target_fs);	// 重采样后序列长度
	std::vector<double> target_x(target_len);	// 初始化重采样后序列自变量
	std::vector<double> target_y(target_len);	// 初始化重采样后序列自变量
	std::iota(target_x.begin(), target_x.end(), 0);	// 递增序列
	double *x = new double[target_len];	// 重采样后序列自变量数组初始化
	double *y = new double[target_len];	// 重采样后序列因变量数组初始化
	if (!target_x.empty())
	{
		memcpy(x, &target_x[0], target_len * sizeof(double));	// 重采样序列自变量索引
	}
	for (int i = 0; i < target_len; i++)
	{
		x[i] *= resample_stepsize;		// 实际重采样自变量序列
		if (x[i] > x0[source_len - 1])
		{
			x[i] = x0[source_len - 1];
		}
	}
	if (!target_y.empty())
	{
		memcpy(y, &target_y[0], target_len * sizeof(double));
	}

	sp.MultiPointInterp(x, target_len, y);			//插值结果

	vector<double> target_vec(y, y + target_len);

	return target_vec;
}

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
void audiowrite(vector<double> y, int fs, string filepath)
{
	// Write WAv文件	
	int channel_num = 1, bitrate = 16;
	Wave_header header(channel_num, fs, bitrate);	//e.g. Wave_header header(1, 48000, 16);
	uint32_t len_arr = y.size();				// 数组长度
	uint32_t length = len_arr * bitrate / 8;	// 字节数
	vector<int> int_array(len_arr);
	int16_t *data = new int16_t[length];

	for (int i = 0; i < len_arr; i++)
	{
		int_array[i] = y[i] * 32678;	// 量化 -32768 ~ 32768	
		data[i] = int_array[i];			// data中每个数据占据两个字节（16位）
	}
	CWaveFile::write(filepath, header, data, length);

}

/*-----------------------------------------------------------------
// 输入：音频数据（vector）
// 输出：消除直流分量后音频数据（vector）
// 功能描述：对音频数据统一消除直流偏置
// 作者：SeventeenChen
// 日期：2021/12/22
// 修改人：
// 记录：
// 日期：
// 记录：
// 版本：
-----------------------------------------------------------------*/
std::vector<double> dc_removal(vector<double> in_array)
{
	double average = 0;			// 平均数
	int n = in_array.size();	// 数组大小
	std::vector<double> out_array(n);
	for (int i = 0; i < n; i++)
	{
		average += in_array[i];
	}
	average /= n;
	for (int i = 0; i < n; i++)
	{
		out_array[i] = in_array[i] - average;
	}
	return out_array;
}