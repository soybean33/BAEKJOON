#include <iostream>
#include <vector>
#include <queue>

struct Turn{	// Turn: 뱀과 사다리 게임 진행 정보
	int turnNum;	// turnNum: 주사위를 굴린 횟수
	int location;	// location: 현재 위치

	static Turn nextTurn(Turn curr, int dice){	// curr: 현재 위치, dice: 주사위를 굴려 나온 값
		return {curr.turnNum + 1, curr.location + dice};	// 다음 위치 return
	}
};

int N, M;	// N: 사다리의 수, M: 뱀의 수
std::vector<int> go;	// go[i]: i 칸에 도착하였을 경우, 사다리나 뱀에 의해 도착하는 칸의 번호
std::vector<bool> visited;	// visited[i]: i 칸 방문 여부 -> 방문 한 적 있으면 turn
int ans;	// ans: 100번 칸에 도착하기 위해 굴려야 하는 최소 주사위 횟수

void solution(){

	std::queue<Turn> q;	// q: 주사
	visited.assign(100 + 1, false);

	q.push({0, 1});
	visited[1] = true;

	while(!q.empty()){
		Turn curr = q.front();	// curr: 현재 게임 정보
		q.pop();

		for(int i=1; i<=6; ++i){
			Turn next = Turn::nextTurn(curr, i);	// 다음 게임 정보

			if(next.location > 100) continue;	// 100 번 칸을 넘어간다면 이동할 수 없음
			if(next.location == 100) {	// 100번 칸에 도착
				ans = next.turnNum;	// 주사위를 굴린 횟수
				return;
			}
			if(visited[next.location]) continue;	// 이미 방문 했던 칸이면 continue

			if(go[next.location]){	// 뱀이나 사다리가 있는 경우
				next = {next.turnNum, go[next.location]};	// next: 다음 칸

				if(visited[next.location]) continue;	// 이미 방문 했던 칸이면 continue

				q.push(next);
				visited[next.location] = true;
			}
			else{
				if(visited[next.location]) continue;	// 이미 방문 했던 칸이면 continue

				q.push(next);
				visited[next.location] = true;
			}
		}
	}

	return;
}

void input(){

	std::cin >> N >> M;

	go.assign(100 + 1, 0);

	for(int i=0; i<N; ++i){
		int from, to;	// from: 사다리 시작 위치, to: 사다리 도착 위치
		
		std::cin >> from >> to;
		go[from] = to;
	}

	for(int i=0; i<M; ++i){
		int from, to;	// from: 뱀 시작 위치, to: 뱀 도착 위치

		std::cin >> from >> to;
		go[from] = to;
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	std::cout << ans;

	return 0;
}