#include <iostream>
#include <vector>

constexpr int INF = 10e8;	// INF: 나올 수 없는 값

int N, M;	// N: 집하장의 개수, M: 집하장간 경로의 개수
std::vector<std::vector<int>> MAP;	// MAP[i][j]: i, j 집하장 간의 경로의 소요시간

std::vector<std::vector<int>> answer;	// answer[i][j]: 경로표

void Solution(){

	// 플로이드-워셜
	for(int k=1; k<=N; ++k){
		for(int i=1; i<=N; ++i){
			for(int j=1; j<=N; ++j){
				if(MAP[i][j] > MAP[i][k] + MAP[k][j]){
					MAP[i][j] = MAP[i][k] + MAP[k][j];
					answer[i][j] = answer[i][k];	// 경로 갱신
				}
			}
		}
	}

	return;
}

void Input(){

	std::cin >> N >> M;

	MAP.assign(N+1, std::vector<int>(N+1, INF));
	answer.assign(N+1, std::vector<int>(N+1, 0));

	for(int j=1; j<=N; ++j){
		for(int i=1; i<=N; ++i){
			if(i==j) {MAP[j][i] = 0;}
		}
	}

	for(int i=0; i<M; ++i){
		int from, to, distance;
		std::cin >> from >> to >> distance;

		MAP[from][to] = distance;
		MAP[to][from] = distance;	// 양방향

		answer[from][to] = to;
		answer[to][from] = from;	// 경로 양방향
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N;j++) {
			if (answer[i][j] == 0) {std::cout << "- ";}
			else {std::cout << answer[i][j]<< ' ' ;}			
		}
		std::cout << '\n';
	}


	return 0;
}