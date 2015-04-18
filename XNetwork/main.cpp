#include "NetUtil.h"

int main(int argc, char **argv)
{
	SysTool::TimeConter cnt;

	
	auto dst = DataTool::LoadImage("test.jpg");
	
	cv::Mat a = DataTool::rand(32, 36);
	cv::Mat w = DataTool::rand(4, 4);



	cnt.tic();
	auto res = MathTool::speedy_convolution(dst, w);
	int p = 100;
	while (p--)
	{
		res = MathTool::speedy_convolution(dst, w);
	}
	cnt.toc();


	double ww;
	cv::minMaxIdx(res, NULL, &ww);


	std::cout << ww << std::endl;


	cv::namedWindow("src");
	cv::imshow("src", res);

	DataTool::ShowMatrix(w);
	
	cv::waitKey();
	return 0;
}