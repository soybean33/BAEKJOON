#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

struct Coordinate{
    int y, x;   // y, x: 좌표
};

struct Edge{
    int a, b, cost; // a, b: 섬 번호, cost: 다리 길이
};

bool cmp(Edge left, Edge right){    // 다리 길이 오름차순
    if(left.cost < right.cost) return true;
    if(left.cost > right.cost) return false;

    return false;
}

int N, M;   // N: 격자의 행의 크기, M: 격자의 열의 크기
int MAP[10][10];    // MAP[i][j]: 격자의 i행 j열의 정보 (0: 바다, 1: 땅)
int island[10][10]; // island[i][j]: 격자의 i행 j열의 섬 번호 (0: 바다, 0보다 큰수는 섬 번호)
int islandNum;  // islandNum: 섬의 수 (1 ~ islandNum)
std::vector<Coordinate> islandLoc[7];   // islandLoc[i]: 섬 i의 모든 땅의 위치
int linked[7][7];   // linked[i][j]: i 섬에서 j 섬까지의 다리 길이 -> 다리의 길이는 2 이상
int parent[7];  // parent[i]: 소속 정보 -> 연결된 섬은 같은 소속을 가짐
int ans;    // ans: 다리 길이의 최소 값

// 우 하 좌 상
int dirY[] = {0, 1, 0, -1};
int dirX[] = {1, 0, -1, 0};

int Find(int now){
    if(now == parent[now]) return now;
    return parent[now] = Find(parent[now]);
}

void Union(int A, int B){
    int pa = Find(A);
    int pb = Find(B);

    if(pa == pb) return;

    parent[pa] = pb;

    return;
}

void makeBridge(){
    std::vector<Edge> v;    // v: 다리 정보 저장

    for(int j=1; j<=islandNum; j++){
        for(int i=1; i<=islandNum; i++){
            if(linked[j][i] == 21e8) continue;  // j 섬과 i 섬을 연결하는 다리가 없는 경우 continue

            v.push_back({j, i, linked[j][i]});  // 다리 정보 추가
        }
    }
    for(int i=1; i<=islandNum; i++){
        parent[i] = i;  // 소속 정보 초기화
    }
    
    std::sort(v.begin(), v.end(), cmp); // 짧은 다리길이 부터 우선적으로 확인하기 위하여 다리 길이 순으로 정렬

    int sum = 0;    // sum: 다리 길이의 총합
    for(int i=0; i<v.size(); i++){
        Edge now = v[i];    // now: 현재 다리 길이

        if(Find(now.a) == Find(now.b)) continue;    // 같은 소속이면 이미 연결되어 있으므로 continue

        sum += now.cost;    // 다리 길이 추가

        Union(now.a, now.b);    // 다리를 연결하였으므로 같은 소속
    }
    for(int i=1; i<=islandNum; i++)
        Find(i);

    for(int i=1; i<=islandNum; i++){
        if(parent[i] != parent[1]){ // 소속이 다른 섬이 있다면
            ans = -1;   // -1 출력
            return;
        }
    }
    ans = sum;  // 모두 연결되어있다면 다리 길이 총합 출력

    return;
}

void linkedIsland(){

    for(int j=1; j<=islandNum; j++){
        for(int i=1; i<=islandNum; i++){
            linked[j][i] = 21e8;    // j 섬에서 i 섬까지의 다리 길이 초기화 -> 최소 길이를 구해야 하므로 최대값으로 초기화 
        }
    }

    for(int i=1; i<=islandNum; i++){    // i: 모든 섬 번호에 대하여
        int size = islandLoc[i].size(); // size: i 섬의 땅 크기
        for(int s=0; s<size; s++){  // s: i 섬의 모든 땅에 대하여
            for(int dir=0; dir<4; dir++){   // 4 방향으로 다리 연결
                Coordinate next = islandLoc[i][s];  // next: 다리 연결할 위치
                int distance = 0;   // distnace: 다리 길이
                int flag = 0;   // flag: 다리를 건설한 적이 있는지 (0: 다리를 건설한 적 없음, 1: 다리를 건설한 적 있음)
                while(true){
                    // dir 방향으로 탐색
                    next.y += dirY[dir];
                    next.x += dirX[dir];

                    if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= M) break;   // 격자 범위 벗어나면 continue
                    
                    if(island[next.y][next.x] == i && flag == 0) continue;   // 아직 같은 섬 내부면 continue

                    if(island[next.y][next.x] == i && flag == 1) break; // 바다로 나갔다가 다시 같은 섬에 들어오면 break;

                    if(island[next.y][next.x] == 0){    // 바다인 경우
                        distance++; // 거리 증가
                        flag = 1;   // 다리 건설 체크
                        continue;
                    }

                    // 다른 섬을 발견한 경우
                    int find = island[next.y][next.x];  // find: 발견한 섬의 번호
                    if(distance >= 2){  // 다리 길이가 2 이상인 경우
                        linked[i][find] = std::min(linked[i][find], distance);  // i 섬과 find 섬의 다리 길이 저장
                    }

                    break;
                }
            }
        }
    }
    
    return;
}

void findIsland(){  // 섬 찾기
    int visited[10][10] = {0, };    // visited[i][j]: i행 j열 방문 체크

    for(int j=0; j<N; j++){
        for(int i=0; i<M; i++){
            if(MAP[j][i] == 0 || visited[j][i] != 0) continue;  // 바다 거나, 방문 했으면 continue

            islandNum++;    // 섬 번호 ++
            std::queue<Coordinate> q;   // q: 연결된 땅
            q.push({j, i});

            islandLoc[islandNum].push_back({j, i}); // 섬 islandNum의 땅 위치 저장
            visited[j][i] = 1;  // 방문 체크

            island[j][i] = islandNum;   // 격자에 섬 번호 표시

            while(!q.empty()){
                Coordinate cur = q.front(); // cur: 현재 땅의 위치
                q.pop();

                for(int dir=0; dir<4; dir++){
                    Coordinate next = {cur.y + dirY[dir], cur.x + dirX[dir]};   // next: 섬인지 검사할 땅의 위치

                    if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= M) continue;    // 격자 범위 벗어나면 continue
                    if(MAP[next.y][next.x] == 0) continue;  // 검사할 땅이 바다면 continue
                    if(visited[next.y][next.x] != 0) continue;  // 이미 검사했던 땅이면 continue

                    islandLoc[islandNum].push_back({next}); // 섬 islandNum의 땅 위치 저장
                    visited[next.y][next.x] = 1;    // 방문 체크

                    island[next.y][next.x] = islandNum; // 격자에 섬 번호 표시

                    q.push(next);   // 다음 땅 탐색에 사용하기 위해 queue에 넣음
                }
            }
        }
    }

    return;
}

void sol(){
    findIsland();
    linkedIsland();
    makeBridge();

    return;
}

void input(){   // 격자 정보 입력
    std::cin >> N >> M;
    for(int j=0; j<N; j++){
        for(int i=0; i<M; i++){
            std::cin >> MAP[j][i];
        }
    }

    return;
}

int main(){
    input();
    sol();

    std::cout << ans;
    return 0;
}