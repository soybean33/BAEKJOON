#include <iostream>
#include <algorithm>

int N, K;	// N: 센서의 개수, K: 집중국의 개수
std::vector<int> A;	// A[i]: i 번째 집중국의 좌표

int answer;	// answer: 최대 K개의 집중국의 수신 가능 영역의 길이의 합의 최솟값

void Solution(){

	std::vector<int> B;	// B[i]: i 번째 집중국의 거리 차이
	B.assign(N-1, 0);

	std::sort(A.begin(), A.end());	// 오름 차순 정렬

	for(int i=1; i<N; ++i) {B[i-1] = A[i] - A[i-1];}	// 차이 구하기

	std::sort(B.begin(), B.end(), std::greater<int>());	// 내림차순 정렬

	for(int i=K-1; i<N-1; ++i) {
		answer += B[i];	// K - 1개를 제외한 길이 더하기
	}

	return;
}

void Input(){

	std::cin >> N >> K;

	A.assign(N, 0);

	for(int i=0; i<N; ++i) {std::cin >> A[i];}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	std::cout << answer;

	return 0;
}