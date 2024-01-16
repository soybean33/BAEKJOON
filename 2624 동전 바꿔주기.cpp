#include <iostream>
#include <vector>

struct Coin{	// Coin: 동전 정보
	int p, n;	// p: 동전 하나의 금액, n: 동전의 개수
};

int T, K;	// T: 지폐의 금액, K: 동전의 가지 수
std::vector<Coin> coins;	// coins[i]: i 번째 동전 정보

int answer;	// answer: 동전 교환 방법의 가지 수

void Solution(){

	std::vector<int> dp;	// dp[i]: i 가치의 동전 교환 방법의 가지 수
	dp.assign(T+1, 0);

	dp[0] = 1;	// 가치가 0인 경우는 1가지

	for(int i=0; i<K; ++i){	// K개의 동전에 대하여
		for(int j=T; j>=1; --j){	// 지폐의 금액에 대하여
			int sum = 0;	// sum: 가격
			for(int k=0; k<coins[i].n; ++k){
				sum += coins[i].p;
				if(j-sum >= 0 && dp[j-sum] > 0) {dp[j] += dp[j-sum];}
			}
		}
	}

	answer = dp[T];

	return;
}

void Input(){

	std::cin >> T;
	std::cin >> K;

	coins.assign(K, {0, 0});

	for(int i=0; i<K; ++i) {std::cin >> coins[i].p >> coins[i].n;}

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