#include <iostream>
#include <string>
#include <queue>

struct Coordinate{
    int y, x;   // y, x: 좌표
};

struct Node{
    Coordinate loc; // loc: 좌표
    int breakCnt;   // breakCnt: 부순 벽의 수
    int distance;   // distance: 이동한 거리
};

int N, M, K;    // N: 지도의 행의 크기, M: 지도의 열의 크기, K: 부술 수 있는 벽의 수
int MAP[1001][1001];    // MAP[i][j]: i행 j열의 정보 -> 0: 이동할 수 있는 곳 1: 벽
int visited[1001][1001][11];    // visited[i][j][k]: i행 j열까지 k개의 벽을 부수고 이동 체크

// 방향 벡터
int dirY[] = {0, 1, 0, -1};
int dirX[] = {-1, 0, 1, 0};

int sol(){

    std::queue<Node> q; // q: 방문할 곳에 대한 정보

    q.push({{0, 0}, 0, 1}); // (0, 0) 칸은 항상 0, 시작하는 칸도 거리에 포함
    visited[0][0][0] = 1;   // 방문 체크

    while(!q.empty()){
        Node cur = q.front();   // cur: 현재 상태 정보
        q.pop();

        if(cur.loc.y == N - 1 && cur.loc.x == M - 1){ // 목적지 도착 -> BFS 이므로 첫 번째로 목적지에 도착하면 최단 경로
            return cur.distance;    // 거리
        }

        for(int dir=0; dir<4; dir++){
            Coordinate next = {cur.loc.y + dirY[dir], cur.loc.x + dirX[dir]};   // next: 다음 방문할 칸의 좌표

            if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= M) continue;    // 범위 벗어나면 continue         

            if(MAP[next.y][next.x] != 0){   // 다음에 갈 곳이 벽인 경우
                if(cur.breakCnt + 1 > K) continue;  // 벽을 더 이상 부술수 없으면 continue
                if(visited[next.y][next.x][cur.breakCnt + 1] != 0) continue;    // 이미 더 짧은 거리로 방문 했으면 continue
                visited[next.y][next.x][cur.breakCnt + 1] = 1;  // 방문 체크
                q.push({next, cur.breakCnt + 1, cur.distance + 1}); // 다음 좌표, 부순 벽 수 증가, 거리 증가
            }
            else{   // 다음에 갈 곳이 빈 공간인 경우
                if(visited[next.y][next.x][cur.breakCnt] != 0) continue;    // 이미 더 짧은 거리로 방문 했으면 continue
                visited[next.y][next.x][cur.breakCnt] = 1;  // 방문 체크
                q.push({next, cur.breakCnt, cur.distance + 1}); // 다음 좌표, 부순 벽 수 유지, 거리 증가
            }
        }
    }

    return -1;  // 불가능한 경우 -1
}

void input(){
    std::cin >> N >> M >> K;
    for(int j=0; j<N; j++){
        std::string s;  // s: 한 행의 정보
        std::cin >> s;
        for(int i=0; i<M; i++){
            MAP[j][i] = s[i] - '0';
        }
    }

    return;
}

int main(){
    input();
    std::cout << sol();

    return 0;
}