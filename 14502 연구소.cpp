#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>

struct Coordinate{
    int y, x;
};

int N, M;   // N: 세로 크기, M: 가로 크기 -> 직사각형임에 주의
int MAP[9][9];  // MAP[j][i]: j행 i열의 상태
int visited[9][9];  // visited[j][i]: j행 i열의 안전 구역 확인용
std::vector<Coordinate> v;  // v: 초기 바이러스의 위치
int ans = 0;    // ans: 가장 많은 안전 구역 저장

// 방향 벡터
int dirY[] = {0,1,0,-1};
int dirX[] = {1,0,-1,0};

// BFS를 사용하여 바이러스 퍼트리기
void BFS(){
    // MAP을 직접사용하지말고 visited에 복사하고 퍼트림 -> 데이터 보호
    for(int j=0; j<N; j++){
        for(int i=0; i<M; i++){
            visited[j][i] = MAP[j][i];
        }
    }

    std::queue<Coordinate> q;
    for(int i=0; i<v.size(); i++){  // 초기 바이러스 위치 저장 및 visited 표시
        q.push(v[i]);
        visited[v[i].y][v[i].x] = 2;
    }

    while(!q.empty()){
        Coordinate next = q.front();
        q.pop();

        for(int dir=0; dir<4; dir++){
            int nextY = next.y + dirY[dir];
            int nextX = next.x + dirX[dir];

            if(nextY < 0 || nextX < 0 || nextY >= N || nextX >= M) continue;    // 범위 벗어나면 continue
            if(visited[nextY][nextX] != 0) continue;    // 갈 수 있는 곳 아니면 continue -> 벽이거나 이미 바이러스 퍼진 곳

            visited[nextY][nextX] = 2;  // 바이러스 퍼트리고
            q.push({nextY, nextX}); // queue에 넣기

        }
    }
    int safe = 0;   // safe: 안전 구역의 수
    for(int j=0; j<N; j++){
        for(int i=0; i<M; i++){
            if(visited[j][i] == 0)  // visited가 0이면 안전구역
                safe++;
        }
    }
    ans = std::max(ans, safe);  // 최댓값 갱신
}

// 벽 3개 세우기 -> DFS를 사용하여 완전 탐색
void DFS(int cnt){

    if(cnt == 3){   // 벽 3개 세움    
        BFS();
        return;
    }

    for(int j=0; j<N; j++){
        for(int i=0; i<M; i++){
            if(MAP[j][i] != 0) continue;    // 이미 벽이 새워져있거나, 초기 바이러스 위치라면 continue

            MAP[j][i] = 1;  // 방문 표시
            DFS(cnt+1);
            MAP[j][i] = 0;  // 방문 해제
        }
    }
}

void sol(){
    DFS(0);
}

// 입력
void input(){
    std::cin >> N >> M;
    for(int j=0; j<N; j++){
        for(int i=0; i<M; i++){
            std::cin >> MAP[j][i];
            if(MAP[j][i]==2)
                v.push_back({j, i});
        }
    }
}

// 초기화
void reset(){
    memset(visited, 0, sizeof(visited));
    memset(MAP, 0, sizeof(MAP));
}

int main(){
    reset();
    input();
    sol();
    std::cout << ans;
    return 0;
}