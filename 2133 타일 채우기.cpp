#include <iostream>
#include <vector>

int N;	// N: 벽의 크기 -> 3 * N 크기의 벽
std::vector<int> dp;	// dp[i]: 3 * i 크기의 벽일 때의 경우의 수
int ans;	// ans: 경우의 수

void solution(){

	if(N % 2) return;	// N이 홀수일 경우는 타일로 채울 수 있음 -> ans = 0

	dp.assign(N+1, 0);

	dp[0] = 1;
	dp[1] = 0;	// N이 1일 경우 불가능 -> 점화식에 사용하기 위하여 값 넣음
	dp[2] = 3;	// N이 2일 경우 (3 * 2의 벽) 3가지 경우 가능

	// dp[N] = (dp[N-2] * dp[2]) + (dp[N-4] * 2) + (dp[N-6] * 2) + (dp[N-8] * 2) + ... + (dp[0] * 2)
	for(int i=4; i<=N; i += 2){
		dp[i] = dp[i-2] * dp[2];
		for(int j=i-4; j>=0; j=j-2){
			dp[i] = dp[i] + (dp[j]*2);
		}
	}

	ans = dp[N];

	return;
}

void input(){

	std::cin >> N;

	return;
}

int main(){

	input();

	solution();

	std::cout << ans;

	return 0;
}