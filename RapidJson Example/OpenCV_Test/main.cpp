/// Summary 
/// ���α׷��� ���۽�Ű��, �̹����� Outline�� JSON ������ ���Ϸ� �����
/// �̹����� ��θ� �ٲٷ���, Mat img�� ��θ� �������� �� + GREYSCALE�� ���� ������ ������ ������ ����� ���� ����.
/// RapidJson:  https://github.com/Tencent/rapidjson
/// RapidJson ���Ĺ���: https://rapidjson.org/md_doc_stream.html
/// RapidJson�� ���� ����� ��ü (Stringbuffer, Document, Value, FileWriteStream)�� ���� ����Ʈ�� �� ����.
/// Summary

#define _CRT_SECURE_NO_WARNINGS
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>     // + Canny �Լ��� ����ϱ� ���� include ����. 
#include <iostream>
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/filewritestream.h" // ���Ͻ�Ʈ���� ���� ���Ϸ� JSON�� �����Ϸ���. 
#include "rapidjson/filereadstream.h" // ������ �ҷ��� �� �ʿ��� ��� (FileReadStream)

#include <cstdio>
#include <vector>
#include <fstream>

using namespace cv;
using namespace std; 
using namespace rapidjson;
int main(int, char*[])
{
    // JSON ��ü���� ���� ����� MAT���� ���� ����ϴ� ���� 
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


    /* �̹��� ������ �ҷ��ͼ� ���� 
    cv::MatIterator_<uint8_t> it, end;
    Mat img = cv::imread("C:/Users/JYPLab/Desktop/Haptin rendering_ Edge Detection/1. CV Code/Example C++/sqaure_test.png", IMREAD_GRAYSCALE); // �̹����� ����� MAT Class�� �ҷ����� �Լ�.  cv:: imread(�̹��� ���)
    Mat img_edge;
    const char* output;
   
    Canny(img, img_edge, 80, 160); // THRESHOLD2 ���� ������ ���� �ʿ䰡 ����. �ʹ� ������ �������� �������� ���� ����
    namedWindow("First OpenCV Application", WINDOW_AUTOSIZE); // Create window
    imshow("First OpenCV Application", img); // �̹����� ��ܿ� ��� �� �Ű������� ���� ����� �ߴ����� �޶���. 
    imshow("Second OpenCV Application", img_edge); // �̹����� ��ܿ� ��� �� �Ű������� ���� ����� �ߴ����� �޶���. 
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
    document.SetObject(); // �� JSON ��ü�� ������ 

    Value myArray(kArrayType); 
    Value rowArray(kArrayType);
    rapidjson::Value objValue;
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    int counter = 0;
    for (it = img_edge.begin<uint8_t>(), end = img_edge.end<uint8_t>(); it != end; ++it)
    {
        objValue.SetInt((int)*it);
        //������ �ְ� ���� ��� objValue.AddMember("playername",i, allocator);
        rowArray.PushBack(objValue, allocator);
        ++counter;
        if (counter == img_edge.cols) {
            myArray.PushBack(rowArray, allocator);
            rowArray.Clear();
            rowArray.SetArray();
            counter = 0;
        }
    }

    // Buffer�� string ���·� ������ �Űܴ��� �� , document�� json ���·� parse
    document.AddMember("array", myArray, allocator); // ���ο� array��� ������ ���� 
    StringBuffer sb;
    Writer<StringBuffer> writer_1(sb);
    document.Accept(writer_1);
    output = sb.GetString();
    document.Parse(output);

    // ���� ���۸� ���� ���Ϸν� �̹����� ������. 
    char writeBuffer[65536];
    FILE* fp = fopen("output.json", "wb"); // non-Windows use "w"
    FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    Writer<FileWriteStream> writer(os);
    document.Accept(writer);
    fclose(fp);

    
    // ���⿡ JSON ������ �ҷ����� �ڵ带 �־ �׽�Ʈ �����غ��� . 

    */
    return 0;
}