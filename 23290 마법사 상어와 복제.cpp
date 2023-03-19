#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>

struct Coordinate{
    int y, x;   // y, x: 좌표
};

int M, S;   // M: 물고기의 수, S: 마법을 연습한 횟수
std::vector<int> MAP[4][4];  // MAP[i][j]: i행 j열에 있는 물고기 방향(0 ~ 7)
int smell[4][4];    // smell[i][j]: i행 j열의 물고기 냄새 -> 2, 1, 0
Coordinate shark;   // shark: 상어의 위치

// 방향 벡터: 왼쪽 방향 부터 시계 방향
int dirY[] = {0, -1, -1, -1, 0, 1, 1, 1};
int dirX[] = {-1, -1, 0, 1, 1, 1, 0, -1};

std::vector<int> moveMAP[4][4]; // moveMAP[i][j]: i행 j열로 움직인 물고기의 방향

int visited[4][4];  // visited[i][j]: i행 j열의 상어 방문 체크 -> 방문한 곳에 다시 상어가 방문할 수 있지만, 제외된 물고기는 2번 카운트 되면 안됨
int eatFish;    // eatFish: 제거된 물고기 수
int eatFishDic; // eatFishDic: 상어의 방향 사전 순

// 방향 벡터: 상 좌 하 우
int dirSharkY[] = {0, -1, 0, 1, 0};
int dirSharkX[] = {0, 0, -1, 0, 1};

int ans;    // ans: S번 연습을 모두 마쳤을 때 격자에 있는 물고기의 수


void DFS(int y, int x, int depth, int path, int catchFish){ // y, x: 위치, depth: 이동한 거리, path: 이동 방향 기록, catchFish: 제거한 물고기

    if(depth == 3){ // 3칸 이동
        if(catchFish > eatFish){    // 더 많은 물고기 제거한 경우
            eatFish = catchFish;    // 제거한 물고기 갱신
            eatFishDic = path;  // 사전순서와 상관없이 갱신
        }else if(catchFish == eatFish){ // 같은 수의 물고기 제거한 경우
            if(path < eatFishDic){  // 사전순서를 고려하여 갱신
                eatFish = catchFish;
                eatFishDic = path;                
            }
        }

        return;
    }

    for(int dir=1; dir<=4; dir++){  // 상 좌 하 우 순서로 탐색
        // newY, newX: 이동할 좌표
        int newY = y + dirSharkY[dir];
        int newX = x + dirSharkX[dir];

        if(newY < 0 || newX < 0 || newY >= 4 || newX >= 4) continue;    // 범위 벗어나면 continue

        if(visited[newY][newX] == 1){   // 이미 방문 했던 곳
            DFS(newY, newX, depth+1, path+dir*std::pow(10, 2-depth), catchFish);    // 물고기 제거 증가하지 않음
        }else{  // 방문한적 없는 곳
            visited[newY][newX] = 1;    // 방문 체크
            DFS(newY, newX, depth+1, path+dir*std::pow(10, 2-depth), catchFish + moveMAP[newY][newX].size());   // 물고기 제거 증가
            visited[newY][newX] = 0;    // 방문 헤제
        }        
    }

    return;
}

void sol(){
    while(S>0){
        // 모든 물고기에게 복제 마법 시전
        std::vector<int> copyMAP[4][4]; // copyMAP[i][j]: i행 j열의 물고기 방향 정보 복제
        for(int j=0; j<4; j++){
            for(int i=0; i<4; i++){
                if(MAP[j][i].empty()) continue; // 해당 칸에 물고기가 없으면 continue

                int fishNum = MAP[j][i].size(); // fishNum: j행 i열의 물고기 수
                for(int f=0; f<fishNum; f++){
                    copyMAP[j][i].push_back(MAP[j][i][f]);  // 복사
                }
            }
        }

        // 모든 물고기가 한 칸 이동
        for(int j=0; j<4; j++){
            for(int i=0; i<4; i++){
                if(MAP[j][i].empty()) continue; // 움직일 물고기가 없다면 continue

                while(!MAP[j][i].empty()){  // j행 i열의 물고기가 모두 이동 해야 함
                    int curFish = MAP[j][i].back(); // curFish: 물고기의 이동 방향
                    MAP[j][i].pop_back();
                    
                    int flag = 0;   // flag: 해당 방향으로 움직일 수 있으면 0, 회전후 움직이면 2, 이동할 수 있는 칸이 없으면 1

                    // newY, newX: 물고기 이동 좌표
                    int newY = j + dirY[curFish];
                    int newX = i + dirX[curFish];

                    if(newY < 0 || newX < 0 || newY >= 4 || newX >= 4) {    // 격자 범위 벗어나면 flag = 1
                        flag = 1;
                    }

                    if(flag == 0){  // 격자 범위를 벗어나지는 않음
                        if(newY == shark.y && newX == shark.x)  // 상어가 있는 위치면 flag = 1
                            flag = 1;
                        if(smell[newY][newX] != 0)  // 물고기 냄새가 있는 위치면 flag = 1
                            flag = 1;
                    }

                    if(flag == 0){  // 진행 방향 그래도 물고기가 욺직일 수 있음
                        moveMAP[newY][newX].push_back(curFish);
                    }
                    else{   // 물고기가 움직일 방향을 찾기 위해 회전
                        for(int dir=1; dir<8; dir++){  // 지금 현재 방향을 제외한 7방향 반시계 방향으로 시도
                            int newDir = (curFish - dir + 8) % 8;   // newDir: 새로운 방향

                            newY = j + dirY[newDir];
                            newX = i + dirX[newDir];

                            if(newY < 0 || newX < 0 || newY >= 4 || newX >= 4) continue;    // 격자의 범위를 벗어나는 칸 continue
                            if(newY == shark.y && newX == shark.x) continue;    // 상어가 있는 칸 continue
                            if(smell[newY][newX] != 0) continue;    // 물고기의 냄새가 있는 칸

                            flag = 2;   // 물고기가 회전을 해서 움직일 수 있으면 flag = 2

                            moveMAP[newY][newX].push_back(newDir);
                            break;  // 반시계 방향으로 돌면서 찾았으므로 더 이상 안해봐도 됨
                        }

                        if(flag == 1)   // 회전을 했음에도 움직일 수 있는 칸이 없다면 그 자리에 그대로 있으면서 방향도 그대로
                            moveMAP[j][i].push_back(curFish);
                    }
                    
                }
            }
        }

        // 상어가 연속해서 3칸 이동
        memset(visited, 0, sizeof(visited));    // 방문 체크 -> 상어는 방문했던 위치에 다시 방문할 수 있음
        eatFish = 0;    // 제거된 물고기 0
        eatFishDic = 999;   // 사전순으로 나열할 것이므로 999로 초기화
        DFS(shark.y, shark.x, 0, 0, 0); // 상어는 연속해서 3칸 이동, 가능한 이동 방법 중에서 제외되는 물고기의 수가 가장 많은 방법, 사전 순으로 가장 앞서는 방법
        
        for(int i=0; i<3; i++){
            int dir;    // dir: 방향
            if(i==0){   // 상어의 첫 번째 이동
                dir = eatFishDic / 100;
            }else if(i==1){ // 상어의 두 번째 이동
                dir = (eatFishDic % 100) / 10;
            }else if(i==2){ // 상어의 세 번째 이동
                dir = eatFishDic % 10;
            }
            // 상어 위치 갱신
            shark.y += dirSharkY[dir];
            shark.x += dirSharkX[dir];

            if(moveMAP[shark.y][shark.x].empty()) continue; // 상어가 이동한 위치에 물고기가 없으면 continue
            smell[shark.y][shark.x] = 3;    // 물고기가 있으면 물고기 냄새 3으로 설정 -> 다음 단계에서 1회 바로 감소
            while(!moveMAP[shark.y][shark.x].empty()){  // 물고기 제거
                moveMAP[shark.y][shark.x].pop_back();
            }
        }

        // 물고기 냄새가 격자에서 사라짐
        for(int j=0; j<4; j++){
            for(int i=0; i<4; i++){
                if(smell[j][i] > 0) // small이 0이 되면 물고기 냄새 사라짐
                    smell[j][i]--;
            }
        }

        // 이동 물고기 및 복사된 물고기 반영
        for(int j=0; j<4; j++){
            for(int i=0; i<4; i++){
                if(!moveMAP[j][i].empty()){ // 이동한 물고기 반영
                    while(!moveMAP[j][i].empty()){
                        MAP[j][i].push_back(moveMAP[j][i].back());
                        moveMAP[j][i].pop_back();
                    }
                }
                if(!copyMAP[j][i].empty()){ // 복제된 물고기 반영
                    while(!copyMAP[j][i].empty()){
                        MAP[j][i].push_back(copyMAP[j][i].back());
                        copyMAP[j][i].pop_back();
                    }
                }
            }
        }
        S--;    // 연습 횟수 감소
    }
    for(int j=0; j<4; j++){
        for(int i=0; i<4; i++){
            if(MAP[j][i].empty()) continue;
            ans += MAP[j][i].size();    // S번 연습을 모두 마쳤을 때, 남아있는 물고기의 수
        }
    }

    return;
}

void input(){
    std::cin >> M >> S;
    for(int i=0; i<M; i++){
        int x, y, d;    // x, y: 물고기 위치, d: 방향
        std::cin >> y >> x >> d;    // 주어지는 (1, 1) ~ (4, 4)를 (0, 0) ~ (3, 3)로 변경
        x--;
        y--;
        d--;    // 모듈러 연산을 사용하기 위해 1 ~ 8의 방향을 0 ~ 7 방향으로 변경
        MAP[y][x].push_back(d);
    }
    int x, y;
    std::cin >> y >> x;
    x--;
    y--;
    shark = {y, x}; // 상어의 위치 저장

    return;
}

int main(){
    input();
    sol();
    std::cout << ans;

    return 0;
}