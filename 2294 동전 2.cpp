#include <iostream>
#include <vector>
#include <algorithm>

constexpr int INF = 21e8;	// INF: 나올 수 없는 값

int N, K;	// N: 동전의 종류의 개수, K: 가치의 합
std::vector<int> coins;	// coins[i]: 동전의 종류

int answer;	// answer: 동전의 개수가 최소가 되도록 -> 될 수 없는 경우는 -1

void Solution(){

	std::vector<int> dp;	// dp[i]: i 가치를 만드는 동전의 수의 최솟값

	dp.assign(K+1, INF);	// 나올 수 없는 값으로 초기화
	dp[0] = 0;	// 0원을 만드는 경우는 0

	for(int i=0; i<N; ++i) {
		for(int j=coins[i]; j<=K; ++j){
			dp[j] = std::min(dp[j], dp[j-coins[i]] + 1);
		}
	}

	answer = dp[K] == INF ? -1 : dp[K];	// 나올수 없는 값이라면 -1

	return;
}

void Input(){

	std::cin >> N >> K;

	coins.assign(N, 0);

	for(int i=0; i<N; ++i) {std::cin >> coins[i];}

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