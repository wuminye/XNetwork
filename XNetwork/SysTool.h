#ifndef SysTool_h
#define SysTool_h

#include "Header.h"


namespace SysTool
{
	using namespace cv;
	//时间统计，测时间
	class TimeConter
	{
		long long rec;
	public:
		//开始计时
		void tic()
		{
			rec = getTickCount();
		}
		//输出时间间隔，单位：秒
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