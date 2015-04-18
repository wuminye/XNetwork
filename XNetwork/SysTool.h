#ifndef SysTool_h
#define SysTool_h

#include "Header.h"


namespace SysTool
{
	using namespace cv;
	//ʱ��ͳ�ƣ���ʱ��
	class TimeConter
	{
		long long rec;
	public:
		//��ʼ��ʱ
		void tic()
		{
			rec = getTickCount();
		}
		//���ʱ��������λ����
		double toc(int ctrl = 0)
		{
			double t = (double)(getTickCount() - rec) / getTickFrequency();
			rec = getTickCount();
			if (ctrl == 0)
			{
				std::cout << "Elapsed time :" << t << " seconds." << std::endl;
			}
			return t;
		}
	};

};




#endif