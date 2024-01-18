#include <iostream>
#include <vector>

int N, M;	// N: 수의 개수, M: 나누는 수
std::vector<long long> v;	// v[i]: M으로 나누어 떨어지는 구간의 개수

long long answer;	// 연속된 부분 구간의 합이 M으로 나누어 떨어지는 구간의 개수

void Solution(){

	for(int i=0; i<M; ++i){	// 구간의 개수
		answer += v[i] * (v[i] - 1) / 2;
	}

	answer += v[0];

	return;
}

void Input(){

	std::cin >> N >> M;

	long long sum = 0;

	v.assign(M, 0);

	for(int i=0; i<N; ++i){
		int a;	// a: 수
		std::cin >> a;
		sum += a;
		++v[sum % M];	// 나누어 떨어지는 수 증가
	}

	return;
}

int main(){

	Input();

	Solution();

	std::cout << answer;

	return 0;
}