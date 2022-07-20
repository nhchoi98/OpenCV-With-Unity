#include "SerialClass.h"
#include <string>


void Serialize()
{
	printf("Welcome to the serial test app\n");

	Serial* sp = new Serial("\\\\.\\COM3"); // 시리얼 포트 번호 꼭 보고 바꿔줘야함 
	if (sp->IsConnected())
		printf("We're conneted");


	char incomingData[256] = "";
	int dataLength = 255;
	int readResult = 0;

	while (sp->IsConnected()) // 나중에 이 부분 연결 끊기면 연결 대기하는거 넣고싶다. 
	{
		readResult = sp->ReadData(incomingData, dataLength);
		incomingData[readResult] = 0;
		printf("%s", incomingData);


	}
	return;
}