#include <iostream>
#include <vector>
#include <algorithm>

int K, N;	// K: 오영식이 이미 가지고 있는 랜선의 개수, N: 필요한 랜선의 개수
std::vector<int> L;	// L[i]: i 번째 랜선의 길이
int max;	// max: 가지고 있는 랜선 중 가장 긴 랜선의 길이

long long Solution(){

	long long answer = 0;	// answer: N개를 만들 수 있는 랜선의 최대 길이

	long long left = 1, right = max;	// left: 이분 탐색 왼쪽, right: 이분 탐색 오른쪽

	while(left <= right) {
		long long mid = right - (right - left) / 2;	// mid: 탐색 값

		long long num = 0;	// num: 만들 수 있는 랜선의 개수

		for(int i=0; i<K; ++i) {num += L[i] / mid;}	// 랜선 개수 계산

		if(num >= N) {	// 더 많이 만듦
			left = mid + 1;	// 더 크게 잘라보기
			answer = answer < mid ? mid : answer;
		}
		else if(num < N) {	// 너무 적게 만듦
			right = mid - 1;	// 더 작게 잘라보기
		}
	}

	return answer;

}

void Input(){

	std::cin >> K >> N;

	L.assign(K, 0);

	for(int i=0; i<K; ++i) {
		std::cin >> L[i];
		max = max < L[i] ? L[i] : max;	// 가지고 있는 랜선 중 최대 길이 구해서 이분탐색의 최댓값으로 사용
	}

	return;
}

int main(){

	Input();

	std::cout << Solution();

	return 0;
}