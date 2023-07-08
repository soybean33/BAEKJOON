#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<int> a;	// a[i]: 수열의 i 번째 숫자
int stepsCnt;	// stepsCnt: 수열의 길이
std::vector<std::vector<std::vector<int>>> dp;	// dp[i][j][k]: i 번째의 왼쪽 발 위치 j 와 오른쪽 발 위치 k 일 때의 최소 힘

int cal(int a, int b){
	if(!a || !b) return 2;	// 발이 가운데에 있거나, 밟아야하는 칸이 0번 칸인 경우

	int diff = std::abs(a-b);	// 발과 밟아야하는 곳의 차이
	if(!diff) return 1;	// 같은 곳 밟음
	else if(diff == 1 || diff == 3) return 3;	// 다른 곳 밟음
	else if(diff == 2) return 4;	// 반대편을 밟음

	return 0;
}

int dfs(int idx, int left, int right){	// idx: 명령의 순서, left: 왼쪽 발의 위치, right: 오른쪽 발의 위치
	if(idx == stepsCnt) return 0;	// 모든 명령 수행 완료
	if(dp[idx][left][right] != -1) return dp[idx][left][right];	// 이미 방문한 적이 있다면 값 그대로 return
	int tmpLeft = dfs(idx + 1, a[idx], right) + cal(a[idx], left);	// tmpLeft: 왼쪽 발을 움직인 경우의 힘
	int tmpRight = dfs(idx + 1, left, a[idx]) + cal(a[idx], right);	// tmpRight: 오른쪽 발을 움직인 경우의 힘

	return dp[idx][left][right] = std::min(tmpLeft, tmpRight);	// 왼쪽 발과 오른쪽 발 중 더 적은 힘으로 움직인 경우로 dp에 기록
}

void solution(){

	stepsCnt = a.size();	// 수열 길이 저장
	dp.assign(stepsCnt, std::vector(5, std::vector(5, -1)));	// dp 공간 할당

	std::cout << dfs(0, 0, 0);

	return;
}

void input(){

	while(true){
		int n;	// n: 수열의 숫자
		std::cin >> n;
		if(!n) break;	// 수열의 마지막은 0
		a.push_back(n);
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	return 0;
}