#include "audiowrite.h"

void audiowrite(vector<double> y, int fs, string filepath)
{
	// Write WAv文件	
	int channel_num = 1, bitrate = 16;
	Wave_header header(channel_num, fs, bitrate);	//e.g. Wave_header header(1, 48000, 16);
	uint32_t len_arr = y.size();
	uint32_t length = len_arr * bitrate / 8;
	vector<int> int_array(len_arr);
	char *data = new char[length];
	string out;
	stringstream ss;

	
	for (int i = 0; i < len_arr; i++)
	{
		int_array[i] = y[i] * 32678;	// 量化 -32768 ~ 32768
		
		ss << std::hex << int_array[i] / 256;		// 高8位	
		ss >> out;
		std::transform(out.begin(), out.end(), out.begin(), ::toupper);
		data[i * 2] = char(out.c_str());
		out.clear();
		ss.clear();
		ss.str(" ");
		
		ss << std::hex << int_array[i] % 256;		// 低8位
		ss >> out;
		std::transform(out.begin(), out.end(), out.begin(), ::toupper);
		data[i * 2 + 1] = char(out.c_str());
		out.clear();
		ss.clear();
		ss.str(" ");
	}

	CWaveFile::write(filepath, header, data, length);

}