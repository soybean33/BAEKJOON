#include <iostream>
#include <cstring>

struct Shark{
    int speed;  // speed: 상어 속력
    int dir;    // dir: 상어 방향
    int size;   // size: 상어 크기
};

int R, C, M;    // R: 행의 크기, C: 열의 크기, M: 상어의 수
Shark MAP[102][102];    // MAP[i][j]: i행 j열의 상어 정보
int catchSize;  // catchSize: 낚시왕이 잡은 상어 크기의 합

// 방향 벡터: 상 하 우 좌
int dirY[] = {0, -1, 1, 0, 0};
int dirX[] = {0, 0, 0, 1, -1};

void sol(){
    for(int x=1; x<=C; x++){    // 낚시왕이 오른쪽으로 한 칸 이동
        // 낚시왕이 있느 ㄴ열에 있는 상어 중에서 땅과 제일 가까운 상어를 잡음
        // 상어를 잡으면 격자판에서 잡은 상어가 사라짐
        for(int j=1; j<=R; j++){    // 낚시왕이 있는 열의 땅과 가장 가까운 부분부터 검사
            if(MAP[j][x].size == 0) continue;   // 상어가 없으면 continue
            catchSize += MAP[j][x].size;    // 낚시왕이 잡은 상어 크기 증가
            MAP[j][x] = {0, 0, 0};  // 잡은 상어 제거
            break;
        }

        // 상어가 이동
        Shark tmpMAP[102][102]; // tmpMAP[i][j]: i행 j열로 이동한 상어 정보
        
        memset(tmpMAP, 0, sizeof(tmpMAP));  // 초기화

        for(int j=1; j<=R; j++){
            for(int i=1; i<=C; i++){
                if(MAP[j][i].size == 0) continue;   // 상어가 없으면 continue

                int speed = MAP[j][i].speed;    // speed: 이동할 상어의 속력
                int dir = MAP[j][i].dir;    // dir: 이동할 상어의 방향
                int size = MAP[j][i].size;  // size: 이동할 상어의 크기
                int nextY = j;  // nextY: 상어의 이동지
                int nextX = i;  // nextX: 상어의 이동지

                for(int s = 0; s < speed; s++){ // 속력만큼 반복
                    nextY += dirY[dir];
                    nextX += dirX[dir];

                    if(nextY <= 0 || nextX <= 0 || nextY > R || nextX > C){ // 격자판의 경계를 넘는 경우
                        // 복구
                        nextY -= dirY[dir];
                        nextX -= dirX[dir];
                        // 방향 반대로 전환
                        if(dir == 1) dir = 2;
                        else if(dir == 2) dir = 1;
                        else if(dir == 3) dir = 4;
                        else if(dir == 4) dir = 3;
                        // 바뀐 방향으로 이동
                        nextY += dirY[dir];
                        nextX += dirX[dir];
                    }
                }
                
                if(tmpMAP[nextY][nextX].size != 0){ // 상어가 이동한 칸에 다른 상어가 있다면
                    if(tmpMAP[nextY][nextX].size < size){   // 크기가 큰 상어가 칸을 차지
                        tmpMAP[nextY][nextX] = {speed, dir, size};
                    }
                }
                else{   // 상어가 이동한 칸이 빈 칸인 경우
                    tmpMAP[nextY][nextX] = {speed, dir, size};
                }
            }
        }
        memcpy(MAP, tmpMAP, sizeof(MAP));
    }
}

void input(){
    std::cin >> R >> C >> M;
    for(int i=0; i<M; i++){
        int r, c, s, d, z;  // r, c: 상어의 위치, s: 상어의 속력, d: 상어의 이동 방향 (1: 상, 2: 하, 3: 우, 4: 좌), z: 상어의 크기
        std::cin >> r >> c >> s >> d >> z;

        if(d == 1 || d == 2){   // 상어의 방향이 위 아래 인 경우
            s = s % ((R-1) * 2);    // (격자의 가로 길이 - 1) * 2 이상의 속력은 상어의 위치가 반복되므로 나머지 연산
        }
        else{   // 상어의 방향이 좌 우 인 경우
            s = s % ((C-1) * 2);    // (격자의 세로 길이 -1) * 2 이상의 속력은 상어의 위치가 반복되므로 나머지 연산
        }

        MAP[r][c] = {s, d, z};  // 상어 정보 입력
    }

    return;
}

int main(){
    input();
    sol();

    std::cout << catchSize;

    return 0;
}