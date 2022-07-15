
#pragma once
#include "Unpack_Packet.h"
#include "vector3.h"
#include "math.h"
using namespace std;
/// <summary>
/// Optitrack에서 마커 추적에 의해 패킷 생성된걸 사용자가 원하는 정보의 형태로 가져오게 하려고 만든 클래스. 
/// Optitrack의 Unpack Marker Description을 참조한다. 
/// 1. 마커의 좌표를 가져옴 
/// 2. 마커의 색인을 클래스내에 가지고 있음 (Labeling된 값)
/// </summary>

class Marker {

	public:
		Vector3 pos; // 마커의 위치정보 
		int label_index; // 마커의 라벨링 인덱스 
		Vector3 targetPos; // 특정 위치에 닿았는지 닿지 않았는지를 판단하기 위한 기준위치. 임시변수 

		// 마커의 위치를 리턴해주는 함수 
		void GetMarkerPos(Vector3& pos)
		{
			pos = this->pos;

		}

		// 마커의 위치값을 set 해주는 함수. unpack packet의 호출부에서 지속적으로 Set 해준다.  
		void SetMarkerPos(Vector3& pos) {

			this->pos = pos;
		}

		// 타깃한 곳에 닿았는지 안닿는지를 판단해줌. 임시 함수.  
		bool IsCollide()
		{
			Vector3 mag = pos - targetPos;
			if (abs(mag.GetMagnitude() < 0.01f)) 
				return true;

			return false;

		}
};

