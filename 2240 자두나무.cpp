#include <iostream>
#include <vector>
#include <algorithm>

int T, W;	// T: 자두가 떨어지는 시간, W: 자두가 최대 움직이는 횟수
std::vector<int> Tree;	// Tree[i]: i 초에 자두가 떨어지는 나무 정보

int answer;	// answer: 자두가 받을 수 있는 자두의 최대 개수

void Solution(){

	std::vector<std::vector<std::vector<int>>> dp;	// dp[i][j][k]: i 번 움직여서 j 위치에서 k 시간이 흐름
	dp.assign(W + 1, std::vector<std::vector<int>>(2, std::vector<int>(T + 1, 0)));

	for (int j = 0; j <= W; j++){	// j: 움직인 횟수
		for (int i = 1; i <= T; i++){	// i: 시간
			if (j == 0)	{	// 0번 움직인 초기값 -> 자두는 1번 자두나무 아래 위치
				dp[j][0][i] = dp[j][0][i - 1] + (Tree[i] == 1);
			}
			else{
				dp[j][0][i] = std::max(dp[j][0][i - 1] + (Tree[i] == 1), dp[j - 1][1][i - 1] + (Tree[i] == 1));
				dp[j][1][i] = std::max(dp[j][1][i - 1] + (Tree[i] == 2), dp[j - 1][0][i - 1] + (Tree[i] == 2));
			}
		}
	}

	for (int i = 0; i < 2; i++){
		for (int j = 0; j <= W; j++){
			answer = std::max(answer, dp[j][i][T]);
		}
	}

	return;
}

void Input(){

	std::cin >> T >> W;

	Tree.assign(T + 1, 0);

	for(int i=1; i<=T; ++i) {std::cin >> Tree[i];}

	return;
}

int main(){

	Input();

	Solution();

	std::cout << answer;

	return 0;
}