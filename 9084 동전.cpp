#include <iostream>
#include <vector>

int T;	// T: 테스트 케이스의 개수
int N;	// N: 동전의 가지 수
std::vector<int> coins;	// coins[i]: i 번째 코인의 금액
int M;	// M: N가지 동전으로 만들어야 할 금액
std::vector<int> dp;	// dp[i]: i 번째 금액이 만들어지는 가지 수

int answer;	// answer: N 가지 동전으로 금액 M을 만드는 모든 방법의 수

void Solution(){

	dp.assign(M+1, 0);
	dp[0] = 1;	// 0 원을 만드는 경우의 수는 1 가지 -> 모든 동전을 사용하지 않음

	for(const int coin : coins){	// coin: 이번에 탐색할 동전의 금액
		for(int i=coin; i<=M; ++i) {	// M 원까지 반복
			dp[i] += dp[i - coin];	// i - coin의 가지수를 더함
		}
	}

	answer = dp[M];	// M 원을 만드는 모든 방법의 수

	return;
}

void Input(){

	std::cin >> N;
	coins.assign(N, 0);

	for(int i=0; i<N; ++i){
		std::cin >> coins[i];
	}

	std::cin >> M;

	return;
}

int main(){

	std::cin >> T;

	for(int tc=0; tc<T; ++tc){
		Input();
		Solution();

		std::cout << answer << '\n';
	}

	return 0;
}