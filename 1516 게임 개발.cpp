#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int N;	// 건물의 종류 수
std::vector<int> buildTime;	// buildTime[i]: i 건물을 짓는데 걸리는 시간
std::vector<std::vector<int>> order;	// order[i][j]: i 건물을 짓기 전에 지어야 하는 j 번째 건물 번호
std::vector<int> inDegree;	// inDegree[i]: i 건물 보다 앞써 지어야 하는 건물의 수
std::vector<int> ansTime;	// ansTime[i]: i 건물이 완성되기까지 걸리는 최소 시간

void solution(){

	ansTime.assign(N+1, 0);

	std::queue<int> q;	// q: 지을 건물 후보

	for(int i=1; i<=N; i++){
		if(!inDegree[i]) {	// 먼저 지어져야 하는 건물이 없는 경우
			ansTime[i] = buildTime[i];	// 건물을 짓는데 걸리는 시간 만큼 소요됨
			q.push(i);
		}
	}

	while(!q.empty()){
		int cur = q.front();	// cur: 지을 건물 번호
		q.pop();

		for(int i=0; i<order[cur].size(); i++){
			int next = order[cur][i];	// next: cur 건물 뒤에 지을 수 있는 건물 번호

			inDegree[next]--;	// cur 건물을 지었으므로 감소
			ansTime[next] = std::max(ansTime[next], ansTime[cur] + buildTime[next]);	// 시간 갱신
			if(!inDegree[next]) q.push(next);
		}
	}

	return;
}

void input(){

	std::cin >> N;

	buildTime.assign(N+1, 0);
	order.assign(N+1, std::vector<int>(0, 0));
	inDegree.assign(N+1, 0);

	for(int i=1; i<=N; i++){
		int cur = i;	// cur: 지을 건물
		int time;	// time: cur 번 건물을 짓는데 걸리는 시간
		int pre;	// pre: cur 건물을 짓기 위해 먼저 지어져야 하는 건물 번호

		std::cin >> time;
		buildTime[cur] = time;

		while(true){
			std::cin >> pre;

			if(pre == -1) break;	// -1 이면 종료

			order[pre].push_back(cur);	// pre 전물을 짓고 cur 건물을 지음
			inDegree[cur]++;
		}
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	for(int i=1; i<=N; i++){
		std::cout << ansTime[i] << '\n';	// 각 건물이 완성되기까지 걸리는 최소 시간 출력
	}

	return 0;
}