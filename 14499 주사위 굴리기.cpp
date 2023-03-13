#include <iostream>

int N, M;    // N: 세로 크기, M: 가로 크기
int x, y;    // x, y: 주사위를 놓을 곳의 좌표 -> x가 세로이므로 바꿔 사용
int K;    // K: 명령의 개수
int MAP[22][22];    // MAP[i][j]: i행 j열의 지도에 있는 숫자 
int order[1001];    // order[i]: i번째 명령
int dice[] = { 0, 0, 0, 0, 0, 0 };    // dice[i]: 주사위 정보 0: 위, 1: 뒤, 2: 오, 3: 왼, 4: 앞, 5: 바닥

// 방향벡터 -> 동 서 북 남 -> 방향이 1부터 들어오므로 1부터 시작
int dirY[] = { 0, 0, 0, -1, 1 };
int dirX[] = { 0, 1, -1, 0, 0 };

void diceRoll(int dir) {
    int newDice[] = { 0, 0, 0, 0, 0, 0 };    // newDice: 변경된 정보를 저장할 곳

    if (dir == 1) {    // 동
        newDice[0] = dice[3];
        newDice[1] = dice[1];
        newDice[2] = dice[0];
        newDice[3] = dice[5];
        newDice[4] = dice[4];
        newDice[5] = dice[2];
    }
    else if (dir == 2) {    // 서
        newDice[0] = dice[2];
        newDice[1] = dice[1];
        newDice[2] = dice[5];
        newDice[3] = dice[0];
        newDice[4] = dice[4];
        newDice[5] = dice[3];
    }
    else if (dir == 3) {    // 북
        newDice[0] = dice[4];
        newDice[1] = dice[0];
        newDice[2] = dice[2];
        newDice[3] = dice[3];
        newDice[4] = dice[5];
        newDice[5] = dice[1];
    }
    else if (dir == 4) {    // 남
        newDice[0] = dice[1];
        newDice[1] = dice[5];
        newDice[2] = dice[2];
        newDice[3] = dice[3];
        newDice[4] = dice[0];
        newDice[5] = dice[4];
    }

    for (int i = 0; i < 6; i++)    // 원래 주사위로 복사
        dice[i] = newDice[i];

    return;
}

int roll(int dir) {

    // newY, newX: 명령에 의해 이동할 좌표
    int newY = y + dirY[dir];
    int newX = x + dirX[dir];

    if (newY < 0 || newX < 0 || newY >= N || newX >= M) return -1;    // 지도 밖으로 나면 return -1

    diceRoll(dir);    // 주사위 굴리기

    if (MAP[newY][newX] == 0) {    // 이동한 칸에 쓰여 있는 수가 0이면
        MAP[newY][newX] = dice[5];    // 주사위의 바닥면에 쓰여 있는 수가 칸에 복사
    }
    else {    // 0이 아닌 경우
        dice[5] = MAP[newY][newX];    // 칸에 쓰여 있는 수가 주사위의 바닥면으로 복사
        MAP[newY][newX] = 0;    // 칸에 쓰여 있는 수는 0
    }

    // 이동한 좌표 업데이트
    y = newY;
    x = newX;

    return dice[0];
}

void sol() {
    for (int k = 0; k < K; k++) {    // k개의 명령 실행
        int ans = roll(order[k]);
        if (ans != -1)    // ans가 -1인 경우 지도 밖으로 나간 경우이므로 
            std::cout << ans << '\n';
    }
}

void input() {    // 입력
    std::cin >> N >> M >> y >> x >> K;
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < M; i++) {
            std::cin >> MAP[j][i];
        }
    }
    for (int k = 0; k < K; k++)
        std::cin >> order[k];

    return;
}

int main() {
    input();
    sol();
    return 0;
}
