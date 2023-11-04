#include <iostream>
#include <vector>

int N;	// N: 약의 개수
std::vector<std::vector<long long>> dp;	// dp[i][j]: 한 조각의 개수 i와 쪼갠 반 조각의 개수 j 일때의 경우의 수

long long answer;	// answer: 가능한 문자열의 개수

long long Dfs(int w, int h) {	// w: 한 조각의 개수, h: 반 조각의 개수
	if(h == -1) {return 0;}	// 더 이상 반 조각이 없음
	if(w == 0) {return 1;}	// 더 이상 한 조각이 없음

	long long& ret = dp[w][h];	// ret: 한 조각이 w개, 반 조각이 h개 일 경우의 수
	if(ret) {return dp[w][h];}

	ret = Dfs(w-1, h+1) + Dfs(w, h-1);	// 한 조각을 쪼개서 먹거나, 쪼갠 반 조각을 먹거나

	return ret;
}

void Solution(){
	
	dp.assign(N + 1, std::vector<long long>(N + 1, 0));

	answer = Dfs(N, 0);

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	while(true){
		std::cin >> N;
		if(N == 0) {break;}

		Solution();

		std::cout << answer << '\n';
	}

	return 0;
}