///*Summary 
/// - 손의 회전정도와, 대강적인 위치 파악을 위해 만든 클래스
/// - 회전정도는 Quternion의 형태로 리턴
/// - 손목의 위치는 Vector3 Type으로 리턴 
/// - 이를 위한 Getter, Setter 제공 
///
#pragma once
#include "Vector3.h"

using namespace std;

class Quternion
{
public:

	Quternion()
	{
		qx = 0;
		qy = 0;
		qz = 0;
		qw = 0;
	}


	Quternion(float _qx, float _qy, float _qz, float _qw)
	{
		qx = _qx;
		qy = _qy;
		qz = _qz;
		qw = -qw;
	}

	float qx;
	float qy;
	float qz;
	float qw;
	/*
		private:
			float qx;
			float qy;
			float qz;
			float qw;
			*/


};


class Wrist {

	public:
		Vector3 pos;
		Quternion orientation;

		Wrist()
		{
			
		}


		Wrist(Vector3& pos, Quternion& ori)
		{
			this->pos = pos;
			this->orientation = ori; // 새로운 쿼터니언 값을 할당함 
		}

		/// <summary>
		/// Set Orientation and position info of it
		/// </summary>
		void SetWristInfo(Vector3& pos, Quternion& orientation)
		{
			this->pos = pos;
			this->orientation = orientation;
			//printf("    pos: [%3.2f,%3.2f,%3.2f]\n", this->pos.x, pos->y, pos->z);
			printf("    ori: [%3.2f,%3.2f,%3.2f,%3.2f]\n", this->orientation.qx, this->orientation.qy, this->orientation.qz, this->orientation.qw);
		}


		/// <summary>
		/// 포인터를 넘겨받으면, 여기에 값을 할당해줌 
		/// </summary>
		void GetWristInfo(Vector3& pos, Quternion& orientation)
		{
			pos = this->pos;
			orientation = this->orientation;
		}


};



