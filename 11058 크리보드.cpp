#include <iostream>
#include <algorithm>

int N;	// N: 버튼을 누르는 횟수

long long answer;	// answer: A 개수의 최댓값

void Solution(){

	std::vector<long long> dp;	// dp[i]: i 번 버튼을 눌렀을 때 A 개수의 최댓값
	dp.assign(101, 0);

	for(int i=1; i<=N; ++i){
		dp[i] = dp[i-1] + 1;	// 3번 동작까지는 A의 개수는 무조건 1개
		for(int j=3; j<i; ++j){
			dp[i] = std::max(dp[i], dp[i-j] * (j - 1));
		}
	}

	answer = dp[N];

	return;
}

void Input(){

	std::cin >> N;

	return;
}

int main(){

	Input();

	Solution();

	std::cout << answer;

	return 0;
}