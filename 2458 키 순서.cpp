#include <iostream>
#include <vector>
#include <algorithm>

constexpr int INF = 10e8;	// INF: 나올 수 없는 값

int N, M;	// N: 학생들의 수, M: 두 학생 키를 비교한 횟수
std::vector<std::vector<int>> V;	// V[i][j]: i 학생과 j 학생키 비교

int answer;	// answer: 자신의 키가 몇 번째인지 알 수 있는 학생의 수

void Solution(){

	// 플로이드-워셜
	for(int t=1; t<=N; ++t){
		for(int i=1; i<=N; ++i){
			for(int j=1; j<=N; ++j){
				V[i][j] = std::min(V[i][j], V[i][t] + V[t][j]);
			}
		}
	}

	for(int i=1; i<=N; ++i){
		int cnt = 0;	// cnt: i 학생과 키 비교가 가능한 학생 수
		for(int j=1; j<=N; ++j){
			if(V[i][j] != INF || V[j][i] != INF) {++cnt;}	// 키 비교가 가능하다면 +1
		}
		if(cnt == N - 1) {++answer;}	// N-1 명의 학생에 대하여 키 비교 가능
	}

	return;
}

void Input(){

	std::cin >> N >> M;

	V.assign(N+1, std::vector<int>(N+1, INF));

	for(int i=0; i<M; ++i){
		int A, B;	// A, B: 키 비교를 하는 두 학생 번호
		std::cin >> A >> B;
		V[A][B] = 1;
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