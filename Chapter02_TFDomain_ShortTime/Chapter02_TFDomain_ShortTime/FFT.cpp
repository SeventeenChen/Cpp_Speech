/*----------------------------------------------------------------
// Copyright (C) SeventeenChen
// License:MIT
// 文件名：FFT.cpp
// 文件功能描述：语音信号的快速傅里叶变换
// 创建者：SeventeenChen
// 时间：2021/12/28
// 修改人：
// 时间：
// 修改说明：
// 软件版本：VS2015
//----------------------------------------------------------------*/

#include "FFT.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

/* r=log2(N) */
void FFT(Complex *TD, Complex *FD, int r)
{
    const int count = 1 << r;	// 左移r位，即count=2^r
    int csz = sizeof(Complex)*count;
    Complex* W = (Complex*)malloc(csz / 2);
    Complex* X1 = (Complex*)malloc(csz);
    Complex* X2 = (Complex*)malloc(csz);
    Complex* X = NULL;

    int  i, j, k;
    int  dist, p;
    double f = PI_X2 / count;
    double a = 0;
    for (i = 0; i < count / 2; ++i)
    {
        W[i] = Complex(cos(a), -sin(a));
        a += f;
    }

    for (i = 0; i < count; ++i)
    {
        X1[i] = TD[i];
    }

    for (k = 0; k < r; ++k)
    {
        for (j = 0; j < (1 << k); ++j)
        {
            dist = 1 << (r - k);
            for (i = 0; i < dist / 2; ++i)
            {
                p = j * dist;
                X2[i + p] = X1[i + p] + X1[i + p + dist / 2];
                X2[i + p + dist / 2] = (X1[i + p] - X1[i + p + dist / 2])* W[i * (1 << k)];
            }
        }
        X = X1;
        X1 = X2;
        X2 = X;
    }
    
    for (j = 0; j < count; ++j)
    {
        p = 0;
        for (i = 0; i < r; ++i)
        {
            if (j&(1 << i))
            {
                p += 1 << (r - i - 1);
            }
        }
        FD[j] = X1[p];
    }

        free(W);
        free(X1);
        free(X2);

        
    for (int j=0; j<r; j++) {
        if (TD[j].real<0.1) {
            FD[j].real=TD[j].real+0.001;
        }else if (TD[j].real>1.0){
            FD[j].real=1.0;
        }else{
            FD[j].real=TD[j].real;
        }
    }
}
