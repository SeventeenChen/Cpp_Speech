/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：FFT.h
// 文件功能描述：语音信号的快速傅里叶变换
// 创建者：SeventeenChen
// 时间：2021/12/28
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/

#ifndef FFT_h
#define FFT_h

#include "Complex.h"

#ifndef CONST_PI
#define CONST_PI
const double PI = 3.14159265358979;
const double PI_X2 = 2 * PI;
#endif

/* r=log2(N) */
extern void FFT(Complex *TD, Complex *FD, int r);


#endif /* FFT_h */
