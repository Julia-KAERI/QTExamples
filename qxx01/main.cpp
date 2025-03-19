#include <iostream>

#include "opencv2/opencv.hpp"


// #include "opencv2/imgproc.hpp"
// #include "opencv2/imgcodecs.hpp"
// #include "opencv2/highgui.hpp"

using namespace std;
// using namespace cv;


int main(int, char**){
    cv::Mat img = cv::imread("Lenna.png");

    if (img.empty()) {
        cerr << "Image laod failed!" << endl;
        return -1;
    }

    cv::namedWindow("image");
    cv::imshow("image", img);
    cv::waitKey();
    cv::destroyAllWindows();

    return 0;
}
// #include <opencv2/opencv.hpp>
// #include "cvplot/cvplot.h"

// int main(){
// 	cvplot::figure("myplot").series("myline").addValue({1., 3., 2., 5., 4.});
// 	cvplot::figure("myplot").show();
// 	return 0;
// }
