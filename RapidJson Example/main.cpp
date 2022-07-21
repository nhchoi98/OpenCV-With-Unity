#define _CRT_SECURE_NO_WARNINGS
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/filewritestream.h"
#include <rapidjson/writer.h>
#include <fstream> // file 입출력과 관련된 헤더 선언 
#include <cstdio>
#include <vector>

// RapidJson 사용을 위한 Testbed
// 여기서는 아무것도 없는 곳에서 JSON화 한 String을 만든 후 , 파일을 저장하는 예제를 담고 있음. 
// Step 1. JSON을 읽고 쓰기 위한 document 객체의 선언 
// Step 2. Value를 하나 선언해줌. (array type으로)
// Step 3. Document에 값을 할당하기 위한 allocator 선언
// Step 4. 반복문에서 특정 값을 기준으로 AddMember해줌.  
// Step 5. myArray라는 곳value를 allocator를 통해 넣어줌. 
// Step 6. 파일로 저장.  (미완) 

using namespace rapidjson;
using namespace std;

int main(int, char* []) {
	Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
    document.SetObject(); // 빈 JSON 객체를 생성함 
    const char* output;
    Value myArray(kArrayType); // 값을 넣을 value 객체 생성 
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator(); // document 객체에 접근 가능하게 해주는 allocator 객체 행성 
    for (int i=0; i<80000; i++)
    {
        rapidjson::Value objValue;
        objValue.SetInt(i); // value의 값을 생성 
        //색인을 넣고 싶은 경우 objValue.AddMember("playername",i, allocator);
        myArray.PushBack(objValue, allocator);//allocator를 통해 값을 해당 value 오브젝트에 넣어줌 
    }

    document.AddMember("array", myArray, allocator); // 도큐먼트에 멤버를 추가해줌 

    /* 이 부분은 파일 아니고 프로그램 내에서 출력을 보기위해 만들어진 출력부분. 파일 입출력은 다르게 구현해야함! 
    printf("\nModified JSON with reformatting:\n");
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    document.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
    puts(sb.GetString());
    */

    // json을 string 형태로 바꿔주는 부분
    StringBuffer sb;
    Writer<StringBuffer> writer_1(sb);
    document.Accept(writer_1);
    output = sb.GetString();
    document.Parse(output);

    // 파일스트림을 통해 실질적으로 JSON 객체를 텍스트 형태 파일로 저장하게끔 하는 부분 
    char writeBuffer[80000];
    FILE* fp = fopen("output.json", "wb"); // non-Windows use "w"
    FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    Writer<FileWriteStream> writer(os);
    document.Accept(writer);
    fclose(fp);

    // WriteBuffer의 크기에 제한이 있는지? 
    return 0;
}
