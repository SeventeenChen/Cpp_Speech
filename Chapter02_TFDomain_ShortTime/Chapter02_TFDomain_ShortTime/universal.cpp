/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// �ļ�����universal.cpp
// �ļ����������������źŵ�ͨ�ò�������д���ز��������Ʋ��Ρ��Ӵ���֡��
// �����ߣ�SeventeenChen
// ʱ�䣺2021/12/21
// �޸��ˣ�
// ʱ�䣺
// �޸�˵����
// ����汾��VS2015
//----------------------------------------------------------------*/

#include "universal.h"
#include "spline.h"
/*-----------------------------------------------------------------
// ���룺
// �����
// ������������Ĺ��캯��
// ���ߣ�SeventeenChen
// ���ڣ�2021/11/27
// �޸��ˣ�
// ��¼��
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
CWave::CWave()	//���캯��
{
	SetWave();
}

/*-----------------------------------------------------------------
// ���룺��ĳ�������
// �����
// ������������Ŀ������캯��
// ���ߣ�SeventeenChen
// ���ڣ�2021/11/27
// �޸��ˣ�
// ��¼��
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
CWave::CWave(const CWave &wave)	//�������캯��
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
	m_wave.wFormatTag = wave.m_wave.wFormatTag;	// WAVE_FORMAT_PCM;//��Ƶ��ʽ .wav
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
		m_dataArray[i] = wave.m_dataArray[i];  //ʵ�����ݴ���� Ϊָ���� ����ΪdwDataSize
	}

}

/*-----------------------------------------------------------------
// ���룺��ĳ�������
// �����
// �������������������
// ���ߣ�SeventeenChen
// ���ڣ�2021/11/27
// �޸��ˣ�
// ��¼��
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
CWave & CWave::operator=(const CWave &wave)
{
	if (this == &wave)//�������Ҹ�ֵ���ͷ��ڴ潫����
		return *this;
	//delete[] m_dataArray;//�ͷ��ڴ�
	for (int i = 0; i < 4; i++)
	{
		m_wave.szRiffID[i] = wave.m_wave.szRiffID[i];
		m_wave.szRiffFormat[i] = wave.m_wave.szRiffFormat[i];
		m_wave.szFmtID[i] = wave.m_wave.szFmtID[i];
		m_wave.szDataID[i] = wave.m_wave.szDataID[i];
	}
	m_wave.dwRiffSize = wave.m_wave.dwRiffSize;
	m_wave.dwFmtSize = wave.m_wave.dwFmtSize;
	m_wave.wFormatTag = wave.m_wave.wFormatTag;// WAVE_FORMAT_PCM;//��Ƶ��ʽ .wav
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
		m_dataArray[i] = wave.m_dataArray[i];  //ʵ�����ݴ���� Ϊָ���� ����ΪdwDataSize
	}
	return *this;
}

/*-----------------------------------------------------------------
// ���룺
// �����
// ������������������
// ���ߣ�SeventeenChen
// ���ڣ�2021/11/27
// �޸��ˣ�
// ��¼��
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
CWave::~CWave()
{
	return;
}

/*-----------------------------------------------------------------
// ���룺��ifstream���ͱ���file������
// �����
// ������������ȡ�����ļ����ڴ棬��Ϊ�ļ�ͷ����Ƶ���ݣ�����Ƶ���ݽ�����ֵ��һ��
// ���ߣ�SeventeenChen
// ���ڣ�2021/11/27
// �޸��ˣ�
// ��¼��
// �޸��ˣ�
// ��¼��
// �汾��
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

		//������д
		int ndata = m_wave.dwDataSize / (m_wave.wBitsPerSample / 8);	// ��������
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

	Normalization();//��һ��Ϊ-1~1

}
/*-----------------------------------------------------------------
// ���룺
// �����
// �������������캯���Ķ���
// ���ߣ�SeventeenChen
// ���ڣ�2021/11/27
// �޸��ˣ�
// ��¼��
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
void CWave::SetWave()		// ����ʶ����
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
	m_wave.wChannels = 1;	//Ĭ��Ϊ��ͨ��

							//data chunk
	m_wave.szDataID[0] = 'd'; m_wave.szDataID[1] = 'a';
	m_wave.szDataID[2] = 't'; m_wave.szDataID[3] = 'a';

	//DWORD dwDataSize;
	m_dataArray.resize(0);
}

/*-----------------------------------------------------------------
// ���룺ת�����result�����ã������ֽ�ָ��ch���ֽ�λ��M
// �����
// ����������2����chתint���ͱ���result
// ���ߣ�SeventeenChen
// ���ڣ�2021/11/27
// �޸��ˣ�
// ��¼��
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
template<typename DataType>  //ģ������������TΪ���Ͳ���
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
// ���룺
// �����
// ������������Ƶ���ݵ���ֵ��һ��
// ���ߣ�SeventeenChen
// ���ڣ�2021/11/27
// �޸��ˣ�
// ��¼��
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
void CWave::Normalization()
{
	int ndata = m_wave.dwDataSize / (m_wave.wBitsPerSample / 8);	// ��������
	if (m_wave.wBitsPerSample == 16)		// 16λ�洢
	{
		for (int i = 0; i < ndata; i++)
		{
			m_dataArray[i] = m_dataArray[i] / max_16_bits;
		}
	}
	else    // 8λ�洢   
	{
		for (int i = 0; i < ndata; i++)
		{
			m_dataArray[i] = m_dataArray[i] / max_8_bits;
		}
	}

}

/*-----------------------------------------------------------------
// ���룺
// �����wav�ļ�ͷ����ز���
// ��������������̨��ʾwav�ļ�ͷ����
// ���ߣ�SeventeenChen
// ���ڣ�2021/11/27
// �޸��ˣ�
// ��¼��
// �޸��ˣ�
// ��¼��
// �汾��
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
// ���룺wav�ļ�����string���������ʣ�int�����Ƿ���ʾ�ļ�ͷ��bool��
// ������ڿ���̨��ӡwav����ͷ������wav��Ƶ���ݣ���һ������ͬ��txt�ļ�
// ���������������źŵĶ�ȡ
// TODO�����Ƴɿɶ�ȡϵͳ·��
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/06
// �޸��ˣ�SeventeenChen
// ��¼����ͬʱ������Ƶ���������Ƶ��
// ���ڣ�2021/12/07
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
std::tuple<vector <double>, int> audioread(string filepath, int fs, bool disp_flag)
{

	std::tuple<vector <double>, int> in_data;
	std::vector<double> in_array;

	in_data = GetFileData(filepath, fs, disp_flag);	// ���ļ���ȡ��Ƶ����
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
// ���룺�ļ���������Ƶ�ʣ�����int���ͣ�����ʾͷ�ļ���ǣ�bool�ͣ�
// �����tuple�ͣ���Ƶ����, ʵ�ʲ���Ƶ�ʣ�
// ������������ȡwav�ļ����ڴ棬��ȡ��Ƶ���ݼ�����Ƶ��
// ���ߣ�SeventeenChen
// ���ڣ�2021/11/27
// �޸��ˣ�SeventeenChen
// ��¼����ͬʱ������Ƶ���������Ƶ��
// ���ڣ�2021/12/07
// �޸��ˣ�SeventeenChen
// ��¼�������ļ����ܴ�ʱ���׳��쳣
// ���ڣ�2021/12/08
// �汾��
-----------------------------------------------------------------*/
std::tuple<vector<double>, int> GetFileData(string file, int fs, bool disp_flag)
{
	CWave wave;
	std::ifstream ifs(file, ios::in | ios::binary);

	if (!ifs)
	{
		throw "File could not be opened";		// �쳣����
		return make_tuple(std::vector<double>(0), 0);
	}
	else
	{
		wave.read(file);	// ����wav�ļ�
		if (disp_flag)
		{
			std::cout << "wav header: " << endl;
			wave.DisplayHeader();
		}
		ifs.close();
		fs = int(wave.m_wave.SampleRate);	// ��ȡ������
		std::vector<double> in_dataArray;	// ������Ƶ����
		GetInputData(wave.m_dataArray, in_dataArray, wave.m_wave.wChannels);	// ȡ��ͨ��
		return make_tuple(in_dataArray, fs);
	}

}

/*-----------------------------------------------------------------
// ���룺�������ݣ�������ݣ���̬��������ã���ͨ�������flag
// �������ͨ����Ƶ����
// ������������ȡwav�ļ��������˫ͨ����Ƶ��ֻȡ������
// ���ߣ�SeventeenChen
// ���ڣ�2021/11/27
// �޸��ˣ�
// ��¼��
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
void GetInputData(std::vector<double> &in_dataArray, std::vector<double>&out_dataArray, int flag)
{
	int nDataLength = in_dataArray.size();
	int nSampleLength = 0;//��������
	if (2 == flag)
	{
		nSampleLength = nDataLength / 2;
		out_dataArray.resize(nSampleLength);
		for (int i = 0; i < nSampleLength; i++)
		{
			out_dataArray[i] = in_dataArray[2 * i];//ȡ������
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
// ���룺��Ƶ���ݣ�vector����ͼ����⣨string��
// �����
// ��������������openGL������Ƶ����
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/08
// �޸��ˣ�SeventeenChen
// ��¼�����title���
// ���ڣ�2021/12/10
// �޸��ˣ�
// ��¼��
// �汾��
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
// ���룺��Ƶ����
// �����
// ��������������openGL������Ƶ����
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/08
// �޸��ˣ�
// ��¼��
// ���ڣ�
// �޸��ˣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
void audioplot(std::vector<double> in_dataArray)
{
	glClearColor(0.8, 0.8, 0.8, 0.8);	// ���ڵ�ɫ
	glClear(GL_COLOR_BUFFER_BIT);

	glLineWidth(2);		//�����߶ο��
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);	// �߶���ɫ

	int i = 0;
	float xstart = -1.0;
	float ystart = 0.0;
	float xend = 0.0;
	float yend = 0.0;
	float temp = 0.0;

	int wav_length = in_dataArray.size();
	float x_stepsize;
	x_stepsize = 2.0 / wav_length;	// �������ݳ��ȼ��㲽����ʹ�û�������ˮƽ������-1~1��
	for (i; i < wav_length; i++)
	{
		xstart = xstart + x_stepsize;
		ystart = temp;
		xend = xstart + x_stepsize;

		yend = in_dataArray[i];

		glVertex2f(xstart, ystart);	// �������
		glVertex2f(xend, yend);		// �����յ�

		temp = yend;    //�յ���Ϊ��һ�ε����
	}

	glEnd();
}

/*-----------------------------------------------------------------
// ���룺�����ź�in_array��������win��֡��frame_shift
// �������֡�����飬֡�� x ֡��
// �����������Ӵ���֡
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
std::vector<double> resample(vector<double> in_array, int target_fs, int source_fs)
{
	int source_len, target_len;
	double duration;	// ����ʱ����ʼ�����룩
	double resample_stepsize = (double)source_fs / target_fs;	// �ز��������Ա�������
	double leftBound = 0, rightBound = 0;	//�߽絼��

	source_len = in_array.size();		// ��֪���г���
	std::vector<double> source_x(source_len);	// ��֪�����Ա�����ʼ��
	std::iota(source_x.begin(), source_x.end(), 0);	// ��������
													// vector ---> array
	double *x0 = new double[source_len];	// ��֪�����Ա��������ʼ��
	if (!source_x.empty())
	{
		memcpy(x0, &source_x[0], source_len * sizeof(double));	// ��ֵ
	}
	double *y0 = new double[source_len];	// ��֪��������������ʼ��
	if (!in_array.empty())
	{
		memcpy(y0, &in_array[0], source_len * sizeof(double));
	}
	Spline sp(x0, y0, source_len, GivenSecondOrder, leftBound, rightBound);
	duration = double(source_len) / source_fs;
	target_len = floor(duration * target_fs);	// �ز��������г���
	std::vector<double> target_x(target_len);	// ��ʼ���ز����������Ա���
	std::vector<double> target_y(target_len);	// ��ʼ���ز����������Ա���
	std::iota(target_x.begin(), target_x.end(), 0);	// ��������
	double *x = new double[target_len];	// �ز����������Ա��������ʼ��
	double *y = new double[target_len];	// �ز�������������������ʼ��
	if (!target_x.empty())
	{
		memcpy(x, &target_x[0], target_len * sizeof(double));	// �ز��������Ա�������
	}
	for (int i = 0; i < target_len; i++)
	{
		x[i] *= resample_stepsize;		// ʵ���ز����Ա�������
		if (x[i] > x0[source_len - 1])
		{
			x[i] = x0[source_len - 1];
		}
	}
	if (!target_y.empty())
	{
		memcpy(y, &target_y[0], target_len * sizeof(double));
	}

	sp.MultiPointInterp(x, target_len, y);			//��ֵ���

	vector<double> target_vec(y, y + target_len);

	return target_vec;
}

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

/*-----------------------------------------------------------------
// ���룺��Ƶ���ݣ�vector��
// ���������ֱ����������Ƶ���ݣ�vector��
// ��������������Ƶ����ͳһ����ֱ��ƫ��
// ���ߣ�SeventeenChen
// ���ڣ�2021/12/22
// �޸��ˣ�
// ��¼��
// ���ڣ�
// ��¼��
// �汾��
-----------------------------------------------------------------*/
std::vector<double> dc_removal(vector<double> in_array)
{
	double average = 0;			// ƽ����
	int n = in_array.size();	// �����С
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