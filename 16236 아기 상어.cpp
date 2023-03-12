#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

struct Shark{   // 상어 정보
    int y, x;   // y, x: 위치
    int size;   // size: 크기
    int exp;    // exp: 경험치 -> size와 같게된다면 0으로 바뀌고 size++;
};

struct Coordinate{
    int y, x;   // y, x: 위치
};

struct C{   // 상어로부터 잡을 수 있는 물고기 정보
    int y, x, dis;  // y, x, dis: 위치와 거리
};

int N;  // N: 한 변의 길이
int M = 0;  // M: 물고기 수
int ans = 0;   // time: 아기 상어 시간
int MAP[21][21];    // MAP[j][i]: j행 i열의 정보, 0: 빈칸, 1~6: 물고기 크기, 9: 아기 상어
Shark shark;    // shark: 아기 상어의 정보

// 방향 벡터 -> 상 좌 우 하
int dirY[] = {-1, 0, 0, 1};
int dirX[] = {0, -1, 1, 0};

bool cmp(C left, C right){  // 잡은 물고기 오름차순 정렬 -> 1. 거리 2. y축 3. xcnr
    if(left.dis < right.dis) return true;
    if(left.dis > right.dis) return false;

    if(left.y < right.y) return true;
    if(left.y > right.y) return false;

    if(left.x < right.x) return true;
    if(left.x > right.x) return false;

    return false;
}

void sol(){

    while(M!=0){    // 물고기가 없을 때 까지 반복
        int flag = 0;   // flag: 잡을 수 있는 물고기가 있다면 1
        std::queue<Coordinate> q;   // q: 아기 상어로 부터의 거리
        std::vector<C> v;   // v: 잡을 수 있는 물고기

        int visited[21][21] = {0, };

        q.push({shark.y, shark.x});
        visited[shark.y][shark.x] = 1;
        
        while(!q.empty()){            
            Coordinate cur = q.front();
            q.pop();            

            for(int dir=0; dir<4; dir++){   // 4방향으로 탐색
                int nextY = cur.y + dirY[dir];
                int nextX = cur.x + dirX[dir];

                if(nextY < 0 || nextX < 0 || nextY >= N || nextX >=N) continue; // 범위 벗어나면 continue
                if(visited[nextY][nextX] != 0) continue;    // 이미 갔던 곳이면 continue
                if(MAP[nextY][nextX] > shark.size) continue;    // 더 큰 물고기는 지나갈 수 없으므로 continue

                visited[nextY][nextX] = visited[cur.y][cur.x] + 1; 

                if(MAP[nextY][nextX] < shark.size && MAP[nextY][nextX] !=0){ // 아기 상어 보다 크기가 작은 물고기 -> 반킨에 주의
                    flag = 1;   // 잡을 수 있는 물고기가 있음
                    v.push_back({nextY, nextX, visited[nextY][nextX]});
                }             
                q.push({nextY, nextX});
            }
        }
        if(flag == 1){
            std::sort(v.begin(), v.end(), cmp); // 정렬
            MAP[v[0].y][v[0].x] = 0;  // 물고기 먹었으므로 0으로 표시
            M--;    // 남은 물고기 감소
            shark.exp++;    // 상어 경험치 증가
            if(shark.exp == shark.size){    // 경험치가 자신의 크기와 같으면
                shark.size++;   // 크기 증가하고
                shark.exp = 0;  // 경험치 0으로 초기화
            }
            ans += v[0].dis - 1;    // 거리는 1을 빼주어야 함
            shark.y = v[0].y;
            shark.x = v[0].x;
        }
        
        if(flag == 0) return;   // 잡을수 있는 물고기가 없으므로 끝
    }

    return;
}

void input(){
    std::cin >> N;
    for(int j=0; j<N; j++){
        for(int i=0; i<N; i++){
            std::cin >> MAP[j][i];
            if(MAP[j][i] == 9){
                MAP[j][i] = 0;
                shark = {j, i, 2, 0};
            }else if(MAP[j][i] != 0){
                M++;
            }
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