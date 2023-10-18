#include <iostream>
#include <cmath>

int T;	// T: 테스트 케이스의 수
long long X, Y;	// X: 현재 위치, Y: 목표 위치
int answer;	// answer: 최소한의 공간이동 장치 작동 횟수

void Solution(){

	double distance = Y - X;	// distance: 두 지점 사이의 거리
	double distancePow = std::sqrt(distance);	// 거리의 제곱근
	int pow = std::round(std::sqrt(distance)); // pow: 거리의 제곱근을 반올림
		
	answer = distancePow <= pow ? pow * 2 - 1 : pow * 2;

	return;
}

void Input(){
	std::cin >> X >> Y;

	return;
}

int main(){
	
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> T;

	while(T--){
		Input();
		Solution();

		std::cout << answer << '\n';
	}
		
	return 0;
}
