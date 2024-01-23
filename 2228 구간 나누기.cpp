#include <iostream>
#include <vector>
#include <algorithm>

constexpr int INF = -10e8;	// INF: 에러 처리

int N, M;	// N: 1차원 배열의 크기, M: 구간의 개수
std::vector<int> V;	// V[i]: 주어진 배열

std::vector<std::vector<int>> dp;	// dp[i][j]: 1 ~ i 인덱스까지 1차원 배열에서 j 개의 구간 선택시 합의 최대

int answer;	// answer: 구간에 속한 수들의 총 합의 최댓값

int Dfs(int n, int m) {
	if(m == 0) {return 0;}	// 구간을 하나도 선택하지 않을 때
	if(n <= 0) {return INF;}	// 에러 처리
	if(dp[n][m] != -1) {return dp[n][m];}	// 이미 최댓값을 구한 경우

	int sum = 0;	// sum: 구간의 합
	dp[n][m] = Dfs(n-1, m);
	for(int i=n; i>0; --i) {
		sum += V[i];
		int tmp = Dfs(i-2, m-1) + sum;
		dp[n][m] = std::max(dp[n][m], tmp);
	}

	return dp[n][m];
}

void Solution() {

	dp.assign(N+1, std::vector<int>(M+1, -1));	// -1 값으로 초가화

	answer = Dfs(N, M);

	return;
}

void Input(){

	std::cin >> N >> M;

	V.assign(N+1, 0);

	for(int i=1; i<=N; ++i) {std::cin >> V[i];}

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