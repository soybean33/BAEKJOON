#include <iostream>

struct Robot{   // 로봇 청소기 정보
    int y, x;   // y, x: 위치
    int dir;    // dir: 북쪽부터 반시계 방향
};

int N, M;   // N: 방의 y축 길이, M: 방의 x축 길이
Robot robot;    // robot: robot의 현재 상태
int room[51][51];   // room[j][i]: j형 i열의 방 정보 0: 청소 안됨, 1: 벽 2: 청소됨
int ans = 0;    // ans: 로봇 청소기의 청소하는 칸의 수

// 방향 벡터: 북 서 남 동
int dirY[] = {-1, 0, 1, 0};
int dirX[] = {0, -1, 0, 1};

void sol(){
    while(true){
        // 1 현재 칸이 아직 청소되지 않은 경우, 현재 칸을 청소한다
        if(room[robot.y][robot.x] == 0){    // 0은 청소되지 않은 칸
            ans++;  // 청소
            room[robot.y][robot.x] = 2; // 청소 완료 후 2로 표시
        }

        int flag = 0;   // flag: 주변 4칸 중 청소가 안된 칸이 있다면 flag 1
        for(int dir = 0; dir < 4; dir++){
            int chkY = robot.y + dirY[dir];
            int chkX = robot.x + dirX[dir];

            if(chkY < 0 || chkX < 0 || chkY >= N || chkX >= M) continue;    // 범위 벗어남

            if(room[chkY][chkX] == 0){  // 4 방향 중 청소 되지 않은 칸 있음
                flag = 1;
                break;
            }
        }
        // 2 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 없는 경우
        if(flag == 0){
            //  후진 좌표 확인
            int newY = robot.y + dirY[(robot.dir+2)%4];
            int newX = robot.x + dirX[(robot.dir+2)%4];

            if(newY < 0 || newX < 0 || newY >= N || newX >= M){ // 범위를 벗어나 후진할 수 없음 -> 작동 멈춤
                return;
            }
            if(room[newY][newX] == 1){  // 벽 때문에 후진할 수 없음 -> 작동 멈춤
                return;
            }

            // 후진
            robot.y = newY;
            robot.x = newX;
        }else{  // 3 현재 칸의 주변 4칸 중 청소되지 않은 빈 칸이 있는 경우
            robot.dir = (robot.dir + 1)%4;  // 반시계 방향으로 90도 회전

            // 반시계 방향 90도 회전 후, 확인 해 볼 앞쪽 칸
            int newY = robot.y + dirY[robot.dir];
            int newX = robot.x + dirX[robot.dir];

            if(newY < 0 || newX < 0 || newY >=N || newX >= M) continue; // 범위 벗어남

            if(room[newY][newX] == 0){  // 청소되지 않은 빈 칸인 경우 한 칸 전진
                robot.y = newY;
                robot.x = newX;
            }
        }
        
    }

    return;
}

void input(){
    int d;
    std::cin >> N >> M;
    std::cin >> robot.y >> robot.x;
    std::cin >> d;
    // 입력 받은 방향은 시계 방향으로 입력 받아 지므로 방향 벡터에 맞게 재 조정 -> 방향 벡터는 로봇의 회전을 위해 반시계 순서
    if(d==0)
        robot.dir = 0;
    else if(d==1)
        robot.dir = 3;
    else if(d==2)
        robot.dir = 2;
    else if(d==3)
        robot.dir = 1;
    for(int j=0; j<N; j++){
        for(int i=0; i<M; i++){
            std::cin >> room[j][i];
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