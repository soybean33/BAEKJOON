#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

struct Coordinate{  // 좌표
    int y, x;
};

int N;  // N: 격자 한 변의 길이
int MAP[20][20];    // MAP[i][j]: i행 j열의 인구
int AREA[20][20];   // AREA[i][j]: i행 j열의 선거구
int ans = 21e8; // ans: 인구가 가장 많은 선거구와 가장 적은 선거구의 인구수 차이의 최소값

// 방향 벡터
int dirY[] = {0, 1, 0, -1};
int dirX[] = {1, 0, -1, 0};

void areaChk(int y, int x, int D2, int D1){ // y, x: 기준점, D2, D1: 경계의 길이
    memset(AREA, 0, sizeof(AREA));  // AREA 초기화
    Coordinate top = {y, x};    // top: 5번 지역구의 상 경계
    Coordinate left = {y+D1, x-D1}; // left: 5번 지역구의 좌 경계
    Coordinate buttom = {y+D1+D2, x-D1+D2}; // buttom: 5번 지역구의 하 경계
    Coordinate right = {y+D2, x+D2};    // right: 5번 지역구의 우 경계

    for(int i=0; i<=D1; i++){   // 상 경계에서 좌 경계로 이동하며 5번 지역구 표시
        int nextY = top.y + i;
        int nextX = top.x - i;
        AREA[nextY][nextX] = 5;
    }
    for(int i=0; i<=D2; i++){   // 좌 경계에서 하 경계로 이동하며 5번 지역구 표시
        int nextY = left.y + i;
        int nextX = left.x + i;
        AREA[nextY][nextX] = 5;
    }
    for(int i=0; i<=D1; i++){   // 하 경계에서 우 경계로 이동하며 5번 지역구 표시
        int nextY = buttom.y - i;
        int nextX = buttom.x + i;
        AREA[nextY][nextX] = 5;
    }
    for(int i=0; i<=D2; i++){   // 우 경계에서 상 경계로 이동하며 5번 지역구 표시
        int nextY = right.y - i;
        int nextX = right.x - i;
        AREA[nextY][nextX] = 5;
    }

    std::queue<Coordinate> q;   // q: 경계 내부 채우기 위한 queue
    // 상 부터
    q.push({top.y+1, top.x});
    AREA[top.y+1][top.x] = 5;

    while(!q.empty()){
        Coordinate cur = q.front();
        q.pop();

        for(int dir=0; dir<4; dir++){
            int nextY = cur.y + dirY[dir];
            int nextX = cur.x + dirX[dir];

            if(nextY < 0 || nextX < 0 || nextY >= N || nextX >= N) continue;
            if(AREA[nextY][nextX] != 0) continue;

            AREA[nextY][nextX] = 5;

            q.push({nextY, nextX});
        }
    }

    // 좌 부터
    q.push({left.y, left.x+1});
    AREA[left.y][left.x+1] = 5;

    while(!q.empty()){
        Coordinate cur = q.front();
        q.pop();

        for(int dir=0; dir<4; dir++){
            int nextY = cur.y + dirY[dir];
            int nextX = cur.x + dirX[dir];

            if(nextY < 0 || nextX < 0 || nextY >= N || nextX >= N) continue;
            if(AREA[nextY][nextX] != 0) continue;

            AREA[nextY][nextX] = 5;

            q.push({nextY, nextX});
        }
    }

    // 하 부터
    q.push({buttom.y-1, buttom.x});
    AREA[buttom.y-1][buttom.x] = 5;

    while(!q.empty()){
        Coordinate cur = q.front();
        q.pop();

        for(int dir=0; dir<4; dir++){
            int nextY = cur.y + dirY[dir];
            int nextX = cur.x + dirX[dir];

            if(nextY < 0 || nextX < 0 || nextY >= N || nextX >= N) continue;
            if(AREA[nextY][nextX] != 0) continue;

            AREA[nextY][nextX] = 5;

            q.push({nextY, nextX});
        }
    }

    // 우 부터
    q.push({right.y, right.x-1});
    AREA[right.y][right.x-1] = 5;

    while(!q.empty()){
        Coordinate cur = q.front();
        q.pop();

        for(int dir=0; dir<4; dir++){
            int nextY = cur.y + dirY[dir];
            int nextX = cur.x + dirX[dir];

            if(nextY < 0 || nextX < 0 || nextY >= N || nextX >= N) continue;
            if(AREA[nextY][nextX] != 0) continue;

            AREA[nextY][nextX] = 5;

            q.push({nextY, nextX});
        }
    }

    // 5번 선거구를 제외한 나머지 선거구 표시
    for(int j=0; j<N; j++){
        for(int i=0; i<N; i++){
            if(AREA[j][i] != 0) continue;

            if(j < left.y && i <= top.x)    // 1번 선거구
                AREA[j][i] = 1;
            else if(j <= right.y && i > top.x)  // 2번 선거구
                AREA[j][i] = 2;
            else if(j >= left.y && i < buttom.x)    // 3번 선거구
                AREA[j][i] = 3;
            else if(j > right.y && i >= buttom.x)   // 4번 선거구
                AREA[j][i] = 4;
        }
    }

    int sum[6] = {0,};  // sum[i]: i 선거구의 인구수
    for(int j=0; j<N; j++){
        for(int i=0; i<N; i++){
            sum[AREA[j][i]] += MAP[j][i];
        }
    }

    std::sort(sum, sum+6);  // 오름차순 정렬
    ans = std::min(ans, sum[5] - sum[1]);   // 인구가 가장 많은 선거구와 가장 적은 선거구의 인구수 차이를 구하고 최소값 갱신

    return;
}

void sol(){
    for(int j=0; j<N; j++){
        for(int i=0; i<N; i++){
            for(int d2=1; d2<=N; d2++){
                for(int d1=1; d1<=N; d1++){
                    int left = i - d1;  // left: 좌 경계
                    int buttom = j + d1 + d2;   // buttom: 하 경계
                    int right = i + d2; // right: 우 경계
                    if(left < 0 || buttom >= N || right >= N) continue; // 경계 중 하나가 범위 벗어나면 continue
                                        
                    areaChk(j, i, d2, d1);
                }
            }
        }
    }

    return;
}

void input(){
    std::cin >> N;
    for(int j=0; j<N; j++){
        for(int i=0; i<N; i++){
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