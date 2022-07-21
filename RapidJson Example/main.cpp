#define _CRT_SECURE_NO_WARNINGS
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
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

    Value myArray(kArrayType); // 값을 넣을 value 객체 생성 
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator(); // document 객체에 접근 가능하게 해주는 allocator 객체 행성 
    for (int i=0; i<5; i++)
    {
        rapidjson::Value objValue;
        objValue.SetInt(i); // value의 값을 생성 
        //색인을 넣고 싶은 경우 objValue.AddMember("playername",i, allocator);
        myArray.PushBack(objValue, allocator);//allocator를 통해 값을 해당 value 오브젝트에 넣어줌 
    }

    document.AddMember("array", myArray, allocator); // 도큐먼트에 멤버를 추가해줌 


    printf("\nModified JSON with reformatting:\n");
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    document.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
    puts(sb.GetString());
    
    return 0;
}