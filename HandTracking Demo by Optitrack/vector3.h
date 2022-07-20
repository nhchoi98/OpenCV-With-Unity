#pragma once
#include <math.h>
#include <iostream>
using namespace std;

/// <summary>
/// 특정 마커의 포인트를 나타내기 위해 사용하는 Vector3 클래스.
/// x,y,z point의 좌표를 제공해준다. 
/// </summary>

class Vector3 {

	public:
		Vector3() // 기본 생성자 
		{
			x = 0;
			y = 0;
			z = 0;
		}

		Vector3(const float x, const float y, const float z) // X,Y,Z 값을 다 알 때의 생성자 
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		float GetMagnitude()
		{
			auto magnitude = sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
			return magnitude;
		}

		// 값을 가지고 오면 이를 다른 곳에 저장시켜줌 
		void Set_Vector(Vector3& vector)
		{
			vector.x = this->x;
			vector.y = this->y;
			vector.z = this->z;

		}

		friend Vector3 operator+(const Vector3& a, const Vector3& b)
		{
			float Vx = a.x + b.x;
			float Vy = a.y + b.y;
			float Vz = a.z + b.z;

			return Vector3(Vx, Vy, Vz);
		}

		friend Vector3 operator-(const Vector3& a, const Vector3& b)
		{
			float Vx = a.x - b.x;
			float Vy = a.y - b.y;
			float Vz = a.z - b.z;

			return Vector3(Vx, Vy, Vz);
		}

		friend Vector3 operator*(const Vector3& a, const Vector3& b)
		{
			float Vx = a.x * b.x;
			float Vy = a.y * b.y;
			float Vz = a.z * b.z;

			return Vector3(Vx, Vy, Vz);
		}

		friend ostream& operator << (ostream& ost, Vector3& pos)
		{
			ost << pos.x << " " << pos.y << " " << pos.z << "\n";
			return ost;
		}

		bool operator ==(Vector3 b) {
			if (x == b.x && y == b.y && z == b.z)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	private:
		float x;
		float y;
		float z;
};
