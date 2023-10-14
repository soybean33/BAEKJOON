#include <iostream>
#include <vector>

int N, K;	// N: 동전의 종류의 개수, K: 가치의 합
std::vector<int> coins;	// coins[i]: 동전의 종류

int answer;	// answer: 경우의 수

void Solution(){

	std::vector<int> dp;	// dp[i]: i 가치를 만드는 경우의 수

	dp.assign(K+1, 0);

	dp[0] = 1;	// 아무것도 선택하지 않는 것도 한 가지 경우
	for(int i=0; i<N; ++i){	// N개의 동전의 종류에 대하여
		for(int j=coins[i]; j<=K; ++j){	// K 원 만들기
			dp[j] += dp[j - coins[i]];	// coins[i]를 빼 봄
		}
	}

	answer = dp[K];

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