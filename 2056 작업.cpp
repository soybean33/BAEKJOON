#include <iostream>
#include <vector>
#include <algorithm>

int N;	// N: 수행해야 할 작업의 개수
std::vector<int> dp;	// dp[i]: i 작업을 완료하는데 소요되는 최소 시간
int ans;	// ans: 모든 작업을 완료하기 위한 최소 시간

void inputSolution(){

	std::cin >> N;

	dp.resize(N + 1);	// 1 부터 시작하는 작업 번호에 맞게 N + 1 개의 공간 할당

	for(int i=1; i<=N; i++){
		int workTime;	// workTime: i 번 작업에 걸리는 시간

		std::cin >> workTime;

		dp[i] = workTime;	// 초기 작업이 없다고 가정하고 i 번 작업은 최소 자신의 작업시간 만큼 소요

		int K;	// K: 선행 관계에 있는 작업의 개수
		std::cin >> K;

		for(int j=0; j<K; j++){
			int workNum;	// workNum: 선행 작업 번호
			std::cin >> workNum;

			dp[i] = std::max(dp[i], dp[workNum] + workTime);	// 선행 작업과 관련하여 현재 작업의 최소 작업 시간 갱신
		}
	}

	for(int i=1; i<=N; i++)
		ans = std::max(ans, dp[i]);	// 모든 작업을 완료하기 위한 최소 시간

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	inputSolution();

	std::cout << ans;

	return 0;
}