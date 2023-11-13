#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int N, M;	// N: 배열의 세로 크기, M: 배열의 가로 크기
std::vector<std::vector<bool>> MAP;	// MAP[i][j]: i 행 j 열의 1 여부

int answer;	// answer: 가장 큰 정사각형의 넓이

void Solution(){

	std::vector<std::vector<int>> dp;
	dp.assign(N+1, std::vector<int>(M+1, 0));

	int max_len = 0;	// max_len: 가장 긴 한 변의 길이
	for(int y=1; y<=N; ++y){
		for(int x=1; x<=M; ++x){
			if(MAP[y-1][x-1] == false) {continue;}	// 0인 경우 continue

			if(MAP[y-1][x-1] == true) {dp[y][x] = 1;}	// 1인 경우 1의 값을 갖음

			dp[y][x] = std::min(dp[y-1][x-1], std::min(dp[y-1][x], dp[y][x-1])) + 1;	// 3 방향 중 가장 작은 값 + 1
			max_len = std::max(max_len, dp[y][x]);
		}
	}

	answer = max_len * max_len;	// 넓이

	return;
}

void Input(){

	std::cin >> N >> M;

	MAP.assign(N, std::vector<bool>(M, false));

	for(int y=0; y<N; ++y){
		std::string S;	// S: 한 행 정보
		std::cin >> S;
		for(int x=0; x<M; ++x){
			if(S[x] == '0') {MAP[y][x] = false;}
			else {MAP[y][x] = true;}
		}
	}

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