#include <iostream>
#include <vector>
#include <algorithm>

int N;	// N: 카드의 개수
std::vector<int> v;	// v[i]: 왼쪽으로부터 i 번째 있는 카드의 번호
std::vector<std::vector<int>> dp;	// dp[i][j]: i 번째부터 j 번째 카드가 있을 때 근우가 얻을 수 있는 최대 점수

int answer;	// answer: 근우와 명우가 최선의 전략으로 임할 때 근우가 얻게되는 점수

int Dfs(int left, int right, int turn){
	if(left > right) {return 0;}	// 모든 탐색이 끝난 경우
	if(dp[left][right]) {return dp[left][right];}	// 이미 탐색한 경우

	if (turn % 2) {return dp[left][right] = std::max(v[left] + Dfs(left + 1, right, turn + 1), v[right] + Dfs(left, right - 1, turn + 1));}	// 근우의 차례
	else {return dp[left][right] = std::min(Dfs(left + 1, right, turn + 1), Dfs(left, right - 1, turn + 1));}	// 명우의 차례

	return 0;
}

void Solution(){

	dp.assign(N, std::vector<int>(N, 0));

	Dfs(0, N-1, 1);

	answer = dp[0][N-1];

	return;
}

void Input(){

	std::cin >> N;

	v.assign(N, 0);

	for(int i=0; i<N; ++i) {std::cin >> v[i];}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T;	// T:테스트케이스의 수
	std::cin >> T;

	for(int tc=0; tc<T; ++tc){
		Input();

		Solution();

		std::cout << answer << '\n';
	}

	return 0;
}