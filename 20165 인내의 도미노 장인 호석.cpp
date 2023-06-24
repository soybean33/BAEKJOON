#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

struct Coordinate{	// 좌표
	int y, x;	// y, x: 좌표
};

struct Round{	// 라운드
	Coordinate attack;	// 공격 위치
	char attackDir;	// 공격 방향 -> E: 동, W: 서, S: 남, N: 북
	Coordinate defence;	// 수비 위치
};

int N, M, R;	// N: 행의 개수, M: 열의 개수, R: 라운드 횟수
int MAP[100][100];	// MAP[i][j]: i 행 j 열의 도미노의 길이
std::vector<Round> rounds;	// rounds[i]: i 번째 라운드 정보
bool state[100][100];	// state[i][j]: i 행 j 열의 도미노 상태 -> true: 서 있는 도미노, false: 넘어진 도미노
int ans;	// ans: 공격수의 점수 -> 넘어뜨린 도미노의 갯수

// 방향 벡터
int dirY[] = {-1, 1, 0, 0};
int dirX[] = {0, 0, -1, 1};

void solution(){

	memset(state, true, sizeof(state));	// 도미노의 상태 모두 서 있도록 초기화

	for(int r=0; r<R; r++){
		Round cur = rounds[r];	// cur: 이번 라운드
		int dir;	// dir: 방향

		// 방향 벡터에 맞도록 방향 계산
		if(cur.attackDir == 'N') dir = 0;
		else if(cur.attackDir == 'S') dir = 1;
		else if(cur.attackDir == 'W') dir = 2;
		else if(cur.attackDir == 'E') dir = 3;

		std::queue<Coordinate> q;	// q: 넘어질 도미노를 담는 큐

		if(!state[cur.attack.y][cur.attack.x]) continue;	// 이미 도미노가 넘어져 있다면 continue
		
		q.push({cur.attack});	// 넘어질 도미노에 넣음

		while(!q.empty()){
			Coordinate curCoordi = q.front();	// curCoordi: 넘어질 도미노의 좌표
			q.pop();

			if(!state[curCoordi.y][curCoordi.x]) continue;	// 이미 도미노가 넘어졌다면 continue

			state[curCoordi.y][curCoordi.x] = false;	// 도미노 넘어짐
			ans++;

			int len =  MAP[curCoordi.y][curCoordi.x] - 1;	// len: 넘어지는 도미노의 길이 -> 연속해서 넘어질 도미노의 갯수

			for(int i = 0; i < len; i++){
				Coordinate nextCoordi = {curCoordi.y + dirY[dir], curCoordi.x + dirX[dir]};	// nextCoordi: 연쇄적으로 넘어질 도미노의 위치
				curCoordi = nextCoordi;

				if(nextCoordi.y < 0 || nextCoordi.x < 0 || nextCoordi.y >= N || nextCoordi.x >= M) continue;	// 범위 벗어나면 continue

				if(!state[nextCoordi.y][nextCoordi.x]) continue;	// 이미 넘어진 도미노는 continue
				
				q.push(nextCoordi);	// 넘어질 도미노에 넣음
			}
		}

		state[cur.defence.y][cur.defence.x] = true;	// 수비
	}

	return;
}

void input(){

	std::cin >> N >> M >> R;

	for(int j=0; j<N; j++){
		for(int i=0; i<M; i++){
			std::cin >> MAP[j][i];	// 도미노의 길이 입력
		}
	}

	rounds.resize(R);

	for(int i=0; i<R; i++){
		int attackY, attackX;	// attackY, attackX: 공격 위치
		char dir;	// dir: 공격 방향
		int defenceY, defenceX;	// defenceY, defenceX: 수비 위치

		std::cin >> attackY >> attackX >> dir;
		std::cin >> defenceY >> defenceX;

		rounds[i] = {{attackY - 1, attackX - 1}, dir, {defenceY - 1, defenceX - 1}};	// 좌표의 값은 1씩 뺌
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	std::cout << ans << '\n';	// 공격수의 점수 출력
	for(int j=0; j<N; j++){
		for(int i=0; i<M; i++){
			if(state[j][i]) std::cout << "S ";	// 넘어지지 않은 도미노
			else std::cout << "F ";	// 넘어진 도미노
		}
		std::cout << '\n';
	}

	return 0;
}