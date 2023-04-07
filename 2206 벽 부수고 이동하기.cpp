#include <iostream>
#include <string>
#include <queue>

struct Coordinate{
        int y, x;       // y, x: 좌표
        int wall;       // wall: 부순 벽의 개수
};

int N, M;       // N: 맵의 행의 크기, M: 맵의 열의 크기
int MAP[1001][1001];    // MAP[i][j]: i행 j열의 맵 정보 -> 0: 이동할 수 있는 곳, 1: 벽이 있는 곳
int visited[1001][1001][2];     // visited[i][j][k]: i행 j열의 칸까지 벽을 k개 부수고 이동하였을 경우의 경로 길이
int ans = -1;   // ans: 최단 경로

// 방향 벡터
int dirY[] = {0, 1, 0, -1};
int dirX[] = {1, 0, -1, 0};

void sol(){
        std::queue<Coordinate> q;       // q: 위치와 부순 벽의 개수 저장하는 큐
        q.push({0, 0, 0});      // 시작 지점 입력
        visited[0][0][0] = 1;   // 시작 방문 체크

        while(!q.empty()){
                Coordinate cur = q.front();     // cur: 현재 좌표와 부순 벽의 개수
                q.pop();

                if(cur.y == N -1 && cur.x == M - 1){    // 현재 좌표가 목적지이면
                        ans = visited[cur.y][cur.x][cur.wall];  // 최단 경로
                        return;
                }

                for(int dir=0; dir<4; dir++){
                        Coordinate next = {cur.y + dirY[dir], cur.x + dirX[dir], cur.wall};     // next: 다음에 갈 곳의 좌표와 부순 벽의 개수 -> 벽의 개수는 아직 계산 안함

                        if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= M) continue;    // 맵의 범위 벗어나면 continue

                        if(MAP[next.y][next.x] == 1 && cur.wall == 1) continue; // 다음에 이동한 좌표에 벽이 있는데 더이상 벽을 부술수 없으면 continue

                        if(MAP[next.y][next.x] == 1) next.wall++;       // 벽 부숨

                        if(visited[next.y][next.x][next.wall] != 0) continue;   // 이미 BFS를 사용하여 방문 하였다면 continue

                        visited[next.y][next.x][next.wall] = visited[cur.y][cur.x][cur.wall] + 1;       // 경로 추가

                        q.push({next.y, next.x, next.wall});
                }
        }

        return;
}

void input(){
        std::cin >> N >> M;
        for(int j=0; j<N; j++){
                std::string s;
                std::cin >> s;
                for(int i=0; i<M; i++){
                        MAP[j][i] = s[i] - '0';
                }
        }

        return;
}

int main(){
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
        std::cout.tie(NULL);

        input();
        sol();

        std::cout << ans;
        return 0;
}