# OpenCV-With-Unity + Single Finger Tracking
OpenCV를 활용한 프로그램과, Unity의 UI를 사용하는 프로그램. 


# 1. 프로그램의 요구사항 
- OpenCV를 이용해, 이미지를 입력하면 Edge를 검출하여 이 결과를 출력하게 한다.
- 유니티를 이용해 이미지를 넣게 되면, OpenCV가 포함된 프로그램이 실행되어 이를 유니티 UI에 출력하게 한다. (목표) 


# 2. 이미지 처리 후 Vision 적인 방법의 처리
- 이미지를 Canny 알고리즘을 이용 해 처리 후, 해당 픽셀들의 값을 사이즈가 규격화된 배열을 통해 JSON 형태로 저장 (RapidJson 사용)
- 이후에 손을 Tracking 하는 프로그램이 JSON을 불러오게 되면, 이 값을 다시 좌표값으로 변환하여 손가락이 해당 위치에 도달했는지를 감지
- 카메라가 사용자의 손에 직교하는 것이 아니므로, Perspective distortion Occur -> 처음에 Affine transformation 의 각 계수들을 구해준 후 프로그램이 실행되어야함. 
