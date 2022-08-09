/// Summary 
/// 프로그램을 동작시키면, 이미지의 Outline이 JSON 형태의 파일로 저장됨
/// 이미지의 경로를 바꾸려면, Mat img의 경로를 수정해줄 것 + GREYSCALE로 읽지 않으면 윤곽선 검출이 제대로 되지 않음.
/// RapidJson:  https://github.com/Tencent/rapidjson
/// RapidJson 공식문서: https://rapidjson.org/md_doc_stream.html
/// RapidJson을 통해 사용한 객체 (Stringbuffer, Document, Value, FileWriteStream)은 위의 사이트를 들어가 참고.
/// Summary

#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>     // + Canny 함수를 사용하기 위해 include 해줌. 
#include <iostream>
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/filewritestream.h" // 파일스트림을 통해 파일로 JSON을 저장하려고. 
#include "rapidjson/filereadstream.h" // 파일을 불러올 때 필요한 헤더 (FileReadStream)

#include <cstdio>
#include <vector>
#include <fstream>

using namespace cv;
using namespace std; 
using namespace rapidjson;
int main(int, char*[])
{
    // JSON 객체에서 내가 만든걸 MAT으로 만들어서 출력하는 예제 
    vector<int> jsonfile;
    //iterator<int> it;
    FILE* fp2 = fopen("output.json", "rb"); // non-Windows use "r"
    char readBuffer[65536];
    Document d;
    FileReadStream is(fp2, readBuffer, sizeof(readBuffer));
    d.ParseStream(is);
    const Value& a = d["array"];
    for (SizeType i = 0; i < a.Size(); i++) { // Uses SizeType instead of size_t

        for (SizeType k = 0; k < a[i].Size(); k++) {
            jsonfile.push_back(a[i][k].GetInt());

        }
    }
    
    fclose(fp2);
    cv::Mat test(512,512,CV_8UC1);
    test = Mat(jsonfile).reshape(0, 512);
    test.convertTo(test, CV_8UC1);
    imshow("First OpenCV Application", test);
    moveWindow("First OpenCV Application", 0, 45);
    waitKey(0); // Terminate when you press 0 


    /* 이미지 파일을 불러와서 가공 
    cv::MatIterator_<uint8_t> it, end;
    Mat img = cv::imread("C:/Users/JYPLab/Desktop/Haptin rendering_ Edge Detection/1. CV Code/Example C++/sqaure_test.png", IMREAD_GRAYSCALE); // 이미지를 행렬인 MAT Class로 불러오는 함수.  cv:: imread(이미지 경로)
    Mat img_edge;
    const char* output;
   
    Canny(img, img_edge, 80, 160); // THRESHOLD2 값은 적당히 높을 필요가 있음. 너무 낮으면 지저분한 엣지들이 많이 나옴
    namedWindow("First OpenCV Application", WINDOW_AUTOSIZE); // Create window
    imshow("First OpenCV Application", img); // 이미지를 상단에 띄울 때 매개변수에 따라서 뭐라고 뜨는지가 달라짐. 
    imshow("Second OpenCV Application", img_edge); // 이미지를 상단에 띄울 때 매개변수에 따라서 뭐라고 뜨는지가 달라짐. 
    moveWindow("First OpenCV Application", 0, 45);
    const int img_scale = img_edge.cols * img_edge.rows;
    waitKey(0); // Terminate when you press 0 
    destroyAllWindows();

    
    std::vector<uint8_t> pixels(img.rows, img.cols);
    for (it = img_edge.begin<uint8_t>(), end = img_edge.end<uint8_t>(); it != end; ++it)
    {
        pixels.push_back(*it);
    }

    Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
    document.SetObject(); // 빈 JSON 객체를 생성함 

    Value myArray(kArrayType); 
    Value rowArray(kArrayType);
    rapidjson::Value objValue;
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    int counter = 0;
    for (it = img_edge.begin<uint8_t>(), end = img_edge.end<uint8_t>(); it != end; ++it)
    {
        objValue.SetInt((int)*it);
        //색인을 넣고 싶은 경우 objValue.AddMember("playername",i, allocator);
        rowArray.PushBack(objValue, allocator);
        ++counter;
        if (counter == img_edge.cols) {
            myArray.PushBack(rowArray, allocator);
            rowArray.Clear();
            rowArray.SetArray();
            counter = 0;
        }
    }

    // Buffer의 string 형태로 데이터 옮겨담은 후 , document의 json 형태로 parse
    document.AddMember("array", myArray, allocator); // 새로운 array라는 데이터 추출 
    StringBuffer sb;
    Writer<StringBuffer> writer_1(sb);
    document.Accept(writer_1);
    output = sb.GetString();
    document.Parse(output);

    // 파일 버퍼를 통해 파일로써 이미지를 저장함. 
    char writeBuffer[65536];
    FILE* fp = fopen("output.json", "wb"); // non-Windows use "w"
    FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    Writer<FileWriteStream> writer(os);
    document.Accept(writer);
    fclose(fp);

    
    // 여기에 JSON 파일을 불러오는 코드를 넣어서 테스트 진행해보자 . 

    */
    return 0;
}