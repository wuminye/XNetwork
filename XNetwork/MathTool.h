#ifndef  MathTool_h
#define MathTool_h

#include "Header.h"

namespace MathTool
{
	using namespace cv;

	enum Econvtype
	{
		full,
		same,
		valid
	};
    // 二维卷积
	// 目前只支持分辨率不变
	Mat conv2(Mat x, Mat w, Econvtype type = same)
	{
		if (x.type() != CV_64FC1)
		{
			x.convertTo(x, CV_64FC1);
		}
		if (w.type() != CV_64FC1)
		{
			w.convertTo(w, CV_64FC1);
		}
		Mat res;
		filter2D(x, res,-1, w);
		return res;
	}

	Mat speedy_convolution(
		const Mat _A,//size:M1 * N1  
		const Mat _B //size : M2 * N2  
		   //size:(M1+M2-1) * (N1+N2-1)  
		)
	{
		CvMat __A = _A;
		CvMat __B = _B;
		CvMat * A = &__A;
		CvMat * B = &__B;


		int dft_M = cvGetOptimalDFTSize(A->rows + B->rows - 1);
		int dft_N = cvGetOptimalDFTSize(A->cols + B->cols - 1);

		CvMat *dft_A = cvCreateMat(dft_M, dft_N, A->type);
		CvMat *dft_B = cvCreateMat(dft_M, dft_N, B->type);
		CvMat tmp;

		//copy A TO dft_A and pad dft_A with zeros  
		cvGetSubRect(dft_A, &tmp, cvRect(0, 0, A->cols, A->rows));
		cvCopy(A, &tmp);
		cvGetSubRect(dft_A, &tmp, cvRect(A->cols, 0, dft_A->cols - A->cols, A->rows));
		cvZero(&tmp);

		//no need to pad bottom part of dft_A with zeros because of   
		//use nonzero_rows parameter in cvDFT() call below  
		cvDFT(dft_A, dft_A, CV_DXT_FORWARD, A->rows);

		//repeat the same with the second array  
		cvGetSubRect(dft_B, &tmp, cvRect(0, 0, B->cols, B->rows));
		cvCopy(B, &tmp);
		cvGetSubRect(dft_B, &tmp, cvRect(B->cols, 0, dft_B->cols - B->cols, B->rows));
		cvZero(&tmp);

		//no need to pad bottom part of dft_B with zeros because of   
		//use nonzero-rows parameter in cvDFT() call below  
		cvDFT(dft_B, dft_B, CV_DXT_FORWARD, B->rows);

		//or CV_DXT_MUL_CONJ to get correlation rather than convolution   
		cvMulSpectrums(dft_A, dft_B, dft_A, 0);

		//calculate only the top part  
		cvDFT(dft_A, dft_A, CV_DXT_INV_SCALE, A->rows + B->rows - 1);
		cvGetSubRect(dft_A, &tmp, cvRect(0, 0, A->cols + B->cols - 1, A->rows + B->rows - 1));
		//cvCopy(&tmp, C);
		cvReleaseMat(&dft_A);
		cvReleaseMat(&dft_B);
		return Mat(&tmp);
	}

};






#endif