// RapidJson 사용을 위한 Testbed
// 여기서 사용한 객체들 (Document, Value, StringBuffer, Writer 등)은 아래의 링크를 참고하면 정보를 얻을 수 있음
// https://rapidjson.org/md_doc_stream.html (RapidJson 공식 도큐먼트) 
// 여기서는 아무것도 없는 곳에서 JSON화 한 String을 만든 후 , 파일을 저장하는 예제를 담고 있음. 
// Step 1. JSON을 읽고 쓰기 위한 document 객체의 선언 
// Step 2. Value를 하나 선언해줌. (array type으로)
// Step 3. Document에 값을 할당하기 위한 allocator 선언
// Step 4. 반복문에서 특정 값을 기준으로 AddMember해줌.  
// Step 5. myArray라는 곳value를 allocator를 통해 넣어줌. 
// Step 6. 파일로 저장.
// Step 7. 저장한 파일을 다시 불러오기. 


#define _CRT_SECURE_NO_WARNINGS
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/filewritestream.h" // 파일을 읽어올 때 필요한 헤더 (FileWriteStream)
#include "rapidjson/filereadstream.h" // 파일을 불러올 때 필요한 헤더 (FileReadStream)
#include "rapidjson/writer.h" // Document에 파일을 Parse할 때 명령내리기 위한 헤더 
#include <fstream> // file 입출력과 관련된 헤더 선언 
#include <cstdio>
#include <vector>



using namespace rapidjson;
using namespace std;

int main(int, char* []) {
    Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
    document.SetObject(); // 빈 JSON 객체를 생성함 
    const char* output;

    Value myArray(kArrayType); // 값을 넣을 value 객체 생성 
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator(); // document 객체에 접근 가능하게 해주는 allocator 객체 행성 
    for (int i = 0; i < 100; i++)
    {
        Value insideArray(kArrayType); // 값을 넣을 value 객체 생성 
        if (i < 30 || i>482) {
            for (int k = 0; k < 100; k++) {

                rapidjson::Value objValue;
                if (k < 30 || k>482)
                    objValue.SetInt(255); // value의 값을 생성 

                else
                    objValue.SetInt(0);
                //색인을 넣고 싶은 경우 objValue.AddMember("playername",i, allocator);
                insideArray.PushBack(objValue, allocator);//allocator를 통해 값을 해당 value 오브젝트에 넣어줌 
            }
        }

        else
        {
            for (int k = 0; k < 512; k++) {
                rapidjson::Value objValue;
                objValue.SetInt(0); // value의 값을 생성 
                //색인을 넣고 싶은 경우 objValue.AddMember("playername",i, allocator);
                insideArray.PushBack(objValue, allocator);//allocator를 통해 값을 해당 value 오브젝트에 넣어줌 
            }

        }


        myArray.PushBack(insideArray, allocator);
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
    char writeBuffer[65436];
    FILE* fp = fopen("output.json", "wb"); // non-Windows use "w"
    FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    Writer<FileWriteStream> writer(os);
    document.Accept(writer);
    fclose(fp);

    // 파일 불러오기 테스트 부분 
    FILE* fp2 = fopen("output.json", "rb"); // non-Windows use "r"
    char readBuffer[65536];
    Document d;
    FileReadStream is(fp2, readBuffer, sizeof(readBuffer));
    d.ParseStream(is);
    fclose(fp);
    // 위의 부분까지는 문제가 없음을 확인함. 
    // 이 부분에서 document -> array로 받아오는 코드가 필요함. 그래야 이제 테스트 시작 가능. 
    const Value& a = d["array"];
    for (SizeType i = 0; i < a.Size(); i++) { // Uses SizeType instead of size_t
        
        for(SizeType k =0; k<a[i].Size(); k++)
        printf("a[%d][%d] = %d\n", i,k, a[i][k].GetInt());

    }
    // WriteBuffer의 크기에 제한이 있는지? 
    return 0;
}