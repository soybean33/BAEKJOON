#include <iostream>
#include <vector>

int T;	// T: 테스트 케이스의 개수
int N;	// N: 만들어야 하는 수

int answer;	// answer: N을 1, 2, 3의 합으로 나타내는 방법의 수

void Solution() {

	std::vector<std::vector<int>> dp;	// dp[i][j]: 수 i 를 j 를 사용해서 나타냄
	
	dp.assign(N + 1, std::vector<int>(4, 0));

	dp[0][1] = 1;	// 숫자 0을 1을 사용해서 만드는 방법의 수
	dp[1][1] = 1;	// 숫자 1을 1을 사용해서 만드는 방법의 수

	// 숫자는 오름차순만 사용
	for (int i = 2; i <= N; ++i) {
		dp[i][1] = dp[i - 1][1];	// 1 전에는 1만 사용 하였음
		dp[i][2] = dp[i - 2][1] + dp[i - 2][2];	// 2 전에는 1과 2만 사용하였음
		if (i >= 3)
			dp[i][3] = dp[i - 3][1] + dp[i - 3][2] + dp[i - 3][3];	// 3 전에는 1과 2와 3을 사용하였음
	}

	answer = dp[N][1] + dp[N][2] + dp[N][3];	// 숫자 N을 만드는 방법의 수

	return;
}

void Input() {

	std::cin >> N;

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> T;

	for (int tc = 0; tc < T; ++tc) {

		Input();

		Solution();

		std::cout << answer << '\n';
	}

	return 0;
}