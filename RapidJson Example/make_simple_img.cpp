// RapidJson ����� ���� Testbed
// ���⼭ ����� ��ü�� (Document, Value, StringBuffer, Writer ��)�� �Ʒ��� ��ũ�� �����ϸ� ������ ���� �� ����
// https://rapidjson.org/md_doc_stream.html (RapidJson ���� ��ť��Ʈ) 
// ���⼭�� �ƹ��͵� ���� ������ JSONȭ �� String�� ���� �� , ������ �����ϴ� ������ ��� ����. 
// Step 1. JSON�� �а� ���� ���� document ��ü�� ���� 
// Step 2. Value�� �ϳ� ��������. (array type����)
// Step 3. Document�� ���� �Ҵ��ϱ� ���� allocator ����
// Step 4. �ݺ������� Ư�� ���� �������� AddMember����.  
// Step 5. myArray��� ��value�� allocator�� ���� �־���. 
// Step 6. ���Ϸ� ����.
// Step 7. ������ ������ �ٽ� �ҷ�����. 


#define _CRT_SECURE_NO_WARNINGS
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/prettywriter.h" // for stringify JSON
#include "rapidjson/filewritestream.h" // ������ �о�� �� �ʿ��� ��� (FileWriteStream)
#include "rapidjson/filereadstream.h" // ������ �ҷ��� �� �ʿ��� ��� (FileReadStream)
#include "rapidjson/writer.h" // Document�� ������ Parse�� �� ��ɳ����� ���� ��� 
#include <fstream> // file ����°� ���õ� ��� ���� 
#include <cstdio>
#include <vector>



using namespace rapidjson;
using namespace std;

int main(int, char* []) {
    Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.
    document.SetObject(); // �� JSON ��ü�� ������ 
    const char* output;

    Value myArray(kArrayType); // ���� ���� value ��ü ���� 
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator(); // document ��ü�� ���� �����ϰ� ���ִ� allocator ��ü �༺ 
    for (int i = 0; i < 100; i++)
    {
        Value insideArray(kArrayType); // ���� ���� value ��ü ���� 
        if (i < 30 || i>482) {
            for (int k = 0; k < 100; k++) {

                rapidjson::Value objValue;
                if (k < 30 || k>482)
                    objValue.SetInt(255); // value�� ���� ���� 

                else
                    objValue.SetInt(0);
                //������ �ְ� ���� ��� objValue.AddMember("playername",i, allocator);
                insideArray.PushBack(objValue, allocator);//allocator�� ���� ���� �ش� value ������Ʈ�� �־��� 
            }
        }

        else
        {
            for (int k = 0; k < 512; k++) {
                rapidjson::Value objValue;
                objValue.SetInt(0); // value�� ���� ���� 
                //������ �ְ� ���� ��� objValue.AddMember("playername",i, allocator);
                insideArray.PushBack(objValue, allocator);//allocator�� ���� ���� �ش� value ������Ʈ�� �־��� 
            }

        }


        myArray.PushBack(insideArray, allocator);
    }

    document.AddMember("array", myArray, allocator); // ��ť��Ʈ�� ����� �߰����� 

    /* �� �κ��� ���� �ƴϰ� ���α׷� ������ ����� �������� ������� ��ºκ�. ���� ������� �ٸ��� �����ؾ���!
    printf("\nModified JSON with reformatting:\n");
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
    document.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
    puts(sb.GetString());
    */

    // json�� string ���·� �ٲ��ִ� �κ�
    StringBuffer sb;
    Writer<StringBuffer> writer_1(sb);
    document.Accept(writer_1);
    output = sb.GetString();
    document.Parse(output);

    // ���Ͻ�Ʈ���� ���� ���������� JSON ��ü�� �ؽ�Ʈ ���� ���Ϸ� �����ϰԲ� �ϴ� �κ� 
    char writeBuffer[65436];
    FILE* fp = fopen("output.json", "wb"); // non-Windows use "w"
    FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    Writer<FileWriteStream> writer(os);
    document.Accept(writer);
    fclose(fp);

    // ���� �ҷ����� �׽�Ʈ �κ� 
    FILE* fp2 = fopen("output.json", "rb"); // non-Windows use "r"
    char readBuffer[65536];
    Document d;
    FileReadStream is(fp2, readBuffer, sizeof(readBuffer));
    d.ParseStream(is);
    fclose(fp);
    // ���� �κб����� ������ ������ Ȯ����. 
    // �� �κп��� document -> array�� �޾ƿ��� �ڵ尡 �ʿ���. �׷��� ���� �׽�Ʈ ���� ����. 
    const Value& a = d["array"];
    for (SizeType i = 0; i < a.Size(); i++) { // Uses SizeType instead of size_t
        
        for(SizeType k =0; k<a[i].Size(); k++)
        printf("a[%d][%d] = %d\n", i,k, a[i][k].GetInt());

    }
    // WriteBuffer�� ũ�⿡ ������ �ִ���? 
    return 0;
}