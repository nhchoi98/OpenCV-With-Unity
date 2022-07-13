#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main()
{
    //Step 1. 이미지를 불러옴 
    Mat img = cv::imread("C:/Users/JYPLab/Desktop/1234.jpg", IMREAD_GRAYSCALE); // 이미지를 행렬인 MAT Class로 불러오는 함수.  cv:: imread(이미지 경로)
    Mat img_edge;

    //Step 2. Canny 알고리즘을 이용하여 경계선을 검출해냄. 
    Canny(img, img_edge, 100, 150); // THRESHOLD2 값은 적당히 높을 필요가 있음. 너무 낮으면 지저분한 엣지들이 많이 나옴

    //Step 3. UI상에 표시해줌 
    namedWindow("First OpenCV Application", WINDOW_AUTOSIZE); // Create window
    imshow("First OpenCV Application", img_edge); // 이미지를 상단에 띄울 때 매개변수에 따라서 뭐라고 뜨는지가 달라짐. 
    imshow("Second OpenCV Application", img); // 이미지를 상단에 띄울 때 매개변수에 따라서 뭐라고 뜨는지가 달라짐. 
    moveWindow("First OpenCV Application", 0, 45);
    waitKey(0); // Terminate when you press 0 
    destroyAllWindows();
    // Q. 파일 형태로 저장한 후 어떤 FLAG를 조정할 수는 없을까? 
    return 0;
}