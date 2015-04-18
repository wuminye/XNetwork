#ifndef DataTool_h
#define DataTool_h

#include "Header.h"

namespace DataTool
{
	using namespace cv;

	// ��ȡͼ�񣬲�ת���ɻҶ�ͼ��
	// ��ֵ��׼����0~1.0������ΪCV_64FC1
	Mat LoadImage(std::string  filename)
	{
		Mat img = cv::imread(filename);
		Mat gray;
		cvtColor(img, gray, CV_BGR2GRAY);
		gray.convertTo(gray, CV_64FC1, 1.0 / 255);
		return gray;
	}

	// ��ӡ��ά������ֵ����Ļ
	// ����CV_64FC1���͵ľ���
	void ShowMatrix(const Mat data)
	{
		if (data.type() != CV_64FC1)
		{
			std::cout << "Error: Matrix type error, not type double." << std::endl;
			exit(-1);
		}
		std::cout << std::endl;
		std::cout << "Matrix[rows, cols]:" << data.rows << " " << data.cols << std::endl;
		std::cout << "------------------------------"<<std::endl;
		for (int x = 0; x < data.rows; ++x)
		{
			const double* dr = data.ptr<double>(x);
			for (int y = 0; y < data.cols; ++y)
			{
				std::cout << dr[y] << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << "------------------------------" << std::endl;
	}

	// �����������Ԫ��Ϊvalue
	// ����CV_64FC1���͵ľ���
	void FillMatrix(Mat &data,double value)
	{
		if (data.type() != CV_64FC1)
		{
			std::cout << "Error: Matrix type error, not type double." << std::endl;
			exit(-1);
		}
		for (int x = 0; x < data.rows; ++x)
		{
			double* dr = data.ptr<double>(x);
			for (int y = 0; y < data.cols; ++y)
			{
				dr[y] = value;
			}
		}
	}

	//���ȫ0���� < CV_64FC1 >
	//r����  c����
	Mat zeros(int r, int c)
	{
		Mat res(r, c, CV_64FC1);
		FillMatrix(res, 0);
		return res;
	}

	//���ȫ1���� < CV_64FC1 >
	//r����  c����
	Mat ones(int r, int c)
	{
		Mat res(r, c, CV_64FC1);
		FillMatrix(res, 1);
		return res;
	}

	//���������� < CV_64FC1 >
	//r����  c����  a�½�  b�Ͻ� [a,b)
	Mat rand(int r, int c, double a=-1.0,double b=1)
	{
		Mat res(r, c, CV_64FC1);
		RNG gen(getTickCount());
		for (int x = 0; x < res.rows; ++x)
		{
			double* dr = res.ptr<double>(x);
			for (int y = 0; y < res.cols; ++y)
			{
				dr[y] = gen.uniform(a,b);
			}
		}
		return res;
	}



};




#endif