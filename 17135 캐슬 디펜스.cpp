#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

struct Coordinate {
    int y, x;	// 좌표
};

struct Enemy {
    int distance;	// distance: 적과 궁수와의 거리
    int y, x;	// y, x: 적의 위치

    bool operator < (Enemy next) const {
		// 거리 오름차순
        if (distance < next.distance) return false;
        if (distance > next.distance) return true;

		// x 좌표 오름차순
        if (x < next.x) return false;
        if (x > next.x) return true;

        return false;
    }
};

int N, M, D;    // N: 행의 수, M: 열의 수, D: 궁수의 공격 거리 제한
int enemyCnt;    // enemyCnt: 적의 수
int MAP[20][20];    // MAP[j][i]: j행 i열 정보
int visited[20];    // visited[i]: 궁수의 위치 i
int ans = 0;	// ans: 궁수의 공격으로 제거할 수 있는 적의 최대 수

// 방향 벡터
int dirY[] = { -1, 0, 1, 0 };
int dirX[] = { 0, 1, 0, -1 };

int play() {
    int tmpMAP[20][20];	// tmpMAP[i][j]: i행 j열의 적
    int kill = enemyCnt;	// kill: 남아있는 적의 수
    int cnt = 0;	// cnt: 궁수에 의해 제거한 적
    memcpy(tmpMAP, MAP, sizeof(tmpMAP));	// 	MAP의 tmpMAP에 복사

    while (kill > 0) {
        // 궁수가 제거 할 수 있는 적 제거
        int killMark[20][20];	// killMark[i][j]: i행 j열에서 제거된 적
        memset(killMark, 0, sizeof(killMark));

        for (int i = 0; i < M; i++) {
            if (visited[i] == 0) continue;	// 궁수가 없으면 continue

            int visitedMAP[20][20];	// visitedMAP[i][j]: 적을 찾기 위해 방문했던 i행 j열
            std::priority_queue<Enemy> pq;	// pq: 적을 찾는 위치
            memset(visitedMAP, 0, sizeof(visitedMAP));

            pq.push({ 0, N, i });
            visitedMAP[N][i] = 1;

            while (!pq.empty()) {
				int curD = pq.top().distance;	// curD: 궁수에서 현재까지 거리
                int curY = pq.top().y;	// y: 현재 위치
                int curX = pq.top().x;	// x: 현재 위치
                pq.pop();

                if (tmpMAP[curY][curX] == 1) {	// 현재 위치에 적이 있다면 break
                    killMark[curY][curX] = 1;
                    break;
                }

                for (int dir = 0; dir < 4; dir++) {
					int newD = curD + 1;	// newD: 다음 위치
                    int newY = curY + dirY[dir];	// newY: 다음 좌표
                    int newX = curX + dirX[dir];	// newX: 다음 좌표

                    if (newY < 0 || newX < 0 || newX >= M || newY >= N) continue;	// 범위 벗어나면 continue
                    if (newD > D) continue;	// 거리 벗어나면 continue

                    if (visitedMAP[newY][newX] == 1) continue;	// 이미 방문한 곳이면 continue

                    visitedMAP[newY][newX] = 1;	// 방문 체크
                    pq.push({ newD, newY, newX });	// pq에 넣기
                }
            }
            
        }
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < M; i++) {
                if (killMark[j][i] == 0) continue;	// 적이 제거된 위치 아니면 continue
                kill--;	// 적 제거
                cnt++;	// 적 제거
                tmpMAP[j][i] = 0;	// 제거된 적의 위치 0
            }
        }
        for (int i = 0; i < M; i++) {
            if (tmpMAP[N - 1][i] == 1) {
                kill--;
            }
        }

		// 적 아래로 한 칸 이동
        for (int j = N-2; j >= 0; j--) {
            for (int i = 0; i < M; i++) {
                tmpMAP[j+1][i] = tmpMAP[j][i];                
            }
        }
		// 윗 부분 0으로 채우기
		for(int i=0; i<M; i++){
			tmpMAP[0][i] = 0;
		}
    }

    return cnt;
}

void DFS(int now, int depth) {

    if (depth == 3) {
        ans = std::max(ans, play());	// 제거된 적의 수 갱신

        return;
    }

    for (int i = now+1; i < M; i++) {
        
        visited[i] = 1;
        DFS(i, depth + 1);
        visited[i] = 0;
    }
}

void sol() {
    DFS(-1, 0);

    return;
}

void input() {
    std::cin >> N >> M >> D;
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < M; i++) {
            std::cin >> MAP[j][i];
            if (MAP[j][i] == 1)
                enemyCnt++;
        }
    }

    return;
}

void reset() {
    memset(MAP, -1, sizeof(MAP));

    return;
}

int main() {
    reset();
    input();
    sol();
    std::cout << ans;

    return 0;
}
