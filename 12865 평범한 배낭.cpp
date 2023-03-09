#include <iostream>
#include <algorithm>

int N, K;	// N: 물건의 개수, K: 버틸 수 있는 무게
int W[101];	// W[i]: i 물건의 무게
int V[101];	// V[i]: i 물건의 가치
int DP[101][100001];	// DP[i][j]: j 무게에서 i 물건을 사용하였을 때 최대 가치

int main() {

	std::cin >> N >> K;
	for (int i = 1; i <= N; i++)
		std::cin >> W[i] >> V[i];

	for (int i = 1; i <= N; i++) {	// i 물건
		for (int j = 1; j <= K; j++) {	// j 무게
			if (j - W[i] >= 0) DP[i][j] = std::max(DP[i - 1][j], DP[i - 1][j - W[i]] + V[i]);	// i 물건을 넣지 않았을 때 최대 무게와 i 물건을 넣었을 때 최대 무게
			else DP[i][j] = DP[i - 1][j];	// i 물건을 넣을 수 없으면 직전 까지 최대 가치 복사
		}
	
	}

	std::cout << DP[N][K];
	return 0;
}