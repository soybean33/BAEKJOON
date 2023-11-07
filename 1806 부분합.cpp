#include <iostream>
#include <vector>
#include <algorithm>

constexpr int INF = 21e8;	// INF: 나올수 없는 값

int N, S;	// N: 수열의 길이, S: 목표한 연속된 수들의 부분합
std::vector<int> V;	// V[i]: 수열의 i 번째 수

int answer = INF;	// answer: 구하고자 하는 최소의 길이

void Solution(){

	int left = 0, right = 0;	// left, right: 투 포인터
	int sum = 0;	// sum: 수열의 합

	while(left <= right){
		if(sum >= S){	// 합이 S보다 큰 경우
			answer = std::min(answer, right - left);	// 최소 길이 갱신
			sum -= V[left++];	// 왼쪽 포인터 옮기고 값 빼기
		}
		else if(right == N) {break;}	// 오른쪽 포인터가 더 이상 증가할 수 없는 경우 break
		else{	// 합이 S보다 작은 경우
			sum += V[right++];	// 오른쪽 포인터 옮기고 값 빼기
		}
	}

	return;
}

void Input(){

	std::cin >> N >> S;

	V.assign(N, 0);

	for(int i=0; i<N; ++i){std::cin >> V[i];}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	if(answer == INF) {std::cout << 0;}
	else {std::cout << answer;}

	return 0;
}