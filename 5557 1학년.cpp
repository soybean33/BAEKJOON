#include <iostream>
#include <vector>

int N;	// N: 숫자의 개수 -> 3<=N<=100
std::vector<int>  v;	// v[i]: i 번째 숫자, 0<=v[i]<=9

long long answer;	// answer: 상근이가 만들 수 있는 올마른 등식의 개수, answer<=2^63 -1

void Solution(){

	std::vector<std::vector<long long>> dp;	// dp[i][j]: i 번째 수로 j 값을 만들 수 있는 개수
	dp.assign(N, std::vector<long long>(21, 0));	// 0으로 초기화

	dp[0][v[0]] = 1;	// 첫 번째 값은 아무런 연산을 하지 않고 1개의 경우

	for(int i=1; i<N-1; ++i){	// N개의 수에 대하여
		for(int j=0; j<=20; ++j){	// 0 ~ 20 사이의 값에 대하여
			if(dp[i-1][j] == 0) {continue;}	// 해당 값이 없다면 continue

			if(j + v[i] <= 20) {dp[i][j+v[i]] += dp[i-1][j];}	// 덧셈 연산의 값이 20 이하러면 -> 이전 연산의 개수를 더함
			if(j - v[i] >= 0) {dp[i][j-v[i]] += dp[i-1][j];}	// 뺄셈 연산의 값이 0 이상이라면 -> 이전 연산의 개수를 더함
		}
	}

	answer = dp[N-2][v[N-1]];	// 마지막 연산까지 가능한 것의 개수

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

	Input();

	Solution();

	std::cout << answer;

	return 0;
}