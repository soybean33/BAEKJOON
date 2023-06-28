#include <iostream>
#include <vector>
#include <queue>

int N, M;	// N: 가수의 수, M: 보조 PD의 수
std::vector<std::vector<int>> order;	// order[i][j]: 보조 PD마다 i 번째 가수의 앞 순서에 존재하는 j 번째 가수 번호
std::vector<int> inDegree;	// inDegree[i]: 보조 PD마다 i 번 가수의 앞에 가수가 있다면 +1
std::vector<int> ans;	// ans[i]: i 번째 가수

void solution(){

	std::queue<int> q;	// q[i]: 더 이상 앞에 출연하는 가수가 없다면 큐에 넣음

	for(int i=1; i<=N; i++){
		if(!inDegree[i]) q.push(i);	// 앞에 출연해야 하는 가수가 없는 가수 큐에 넣음
	}

	while(!q.empty()){
		int cur = q.front();	// cur: 출연 가수
		q.pop();

		ans.push_back(cur);	// 출연

		for(int i=0; i<order[cur].size(); i++){
			int next = order[cur][i];	// 출연 가수 다음 순서인 가수 번호
			inDegree[next]--;	// 앞의 가수가 출연 하였으므로 -1
			if(!inDegree[next]) q.push(next);	// next 가수의 앞에 더 이상 출연 가수가 없다면 출연 대기열 넣음
		}
	}

	return;
}

void input(){

	std::cin >> N >> M;

	order.assign(N + 1, std::vector<int>(0, 0));
	inDegree.assign(N + 1, 0);

	for(int j=0; j<M; j++){
		int teamNum;	// teamNum: 가수 번호
		int cur, next;	// cur: 현재 가수 번호, next: cur 가수 다음 순서 가수 번호

		std::cin >> teamNum;
		std::cin >> cur;
		for(int i=1; i<teamNum; i++){
			std::cin >> next;
			order[cur].push_back(next);	// cur 가수 뒤에 next 가수 출연
			inDegree[next]++;	// next 가수 앞에 가수가 있으므로 +1
			cur = next;
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

	if(ans.size() != N) std::cout << "0";	// 사이클이 있다면 0
	else{
		for(int i=0; i<N; i++) std::cout << ans[i] << '\n';	// 순서대로 출력
	}

	return 0;
}