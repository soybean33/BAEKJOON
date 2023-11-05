#include <iostream>
#include <vector>
#include <algorithm>

int X;	// X: 구멍의 너비 1<=X<=20 -> X의 단위는 센티미터
int N;	// N: 물리 실험실에 있는 레고 조각의 수 0<=N<=1'000'000
std::vector<int> legos;	// legos[i]: i 번째 레고 조각의 길이 -> 단위는 나노미터 1<=legos[i]<=100'000'000

void Solution(){

	std::sort(legos.begin(), legos.end());	// 오름차순 정렬

	int left = 0, right = N - 1;	// left, right: 조합해볼 레고의 인덱스

	bool flag = false;	// flag: 구멍을 완벽하게 막을 수 있는 두 조각이 유무

	while(left < right) {
		int sum = legos[left] + legos[right];	// sum: 두 조각의 길이의 합

		if(sum == X) {	// 구멍을 완전히 막을 수 있음
			flag = true;
			break;	// 가장 처음 발견되는 조각들의 차이가 가장 큼
		}
		else if(sum < X) {++left;}	// 더 긴 조각이 필요함
		else {--right;}	// 더 짧은 조각이 필요함
	}

	if(flag == false) {std::cout << "danger\n";}
	else {std::cout << "yes " << legos[left] << ' ' << legos[right] << '\n';}

	return;
}

void Input(){

	X *= 10'000'000;	// 센치미터 단위를 나노미터로 변경

	std::cin >> N;

	legos.assign(N, 0);

	for(int i=0; i<N; ++i){std::cin >> legos[i];}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	while(std::cin >> X) {	// X가 들어오지 않을 때 까지 반복	

		Input();

		Solution();
	}

	return 0;
}