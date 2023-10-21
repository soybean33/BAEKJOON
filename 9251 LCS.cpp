#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string A, B;	// A, B: 두 수열

int answer;	// answer: 두 문자열의 LCS 길이

void Solution(){

	std::vector<std::vector<int>> dp;	// dp[i][j]: A의 i 번째 문자열과 B의 j 번째 문자열 까지의 LCS
	dp.assign(A.length() + 1, std::vector<int>(B.length() + 1, 0));

	for(int i=1; i<=A.length(); ++i){
		for(int j=1; j<=B.length(); ++j){
			if(A[i-1] == B[j-1]) {dp[i][j] = dp[i-1][j-1] + 1;}	// 같을 경우 증가
			else {dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);}	// 다를 경우 더 큰 LCS 값
		}
	}

	answer = dp[A.length()][B.length()];

	return;
}

void Input(){

	std::cin >> A >> B;

	return;
}

int main(){

	Input();

	Solution();

	std::cout << answer;

	return 0;
}