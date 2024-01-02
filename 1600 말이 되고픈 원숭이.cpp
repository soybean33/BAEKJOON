#include <iostream>
#include <vector>
#include <queue>

// 원숭이 움직이기
constexpr int dirY[4] = {0, 1, 0, -1};
constexpr int dirX[4] = {1, 0, -1, 0};

// 말 처럼 움직이기
constexpr int dirYH[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
constexpr int dirXH[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

struct Move{    // Move: 움직인 원숭이의 상태
    int y, x;   // y, x: 좌표
    int cnt;    // cnt: 움직인 횟수
    int ability;    // ability: 말처럼 움직이기 위해 사용한 능력의 횟수
};

int K;  // K: 원숭이가 사용할 수 있는 능력의 횟수
int W, H;   // W: 격자판의 가로 길이, H: 격자판의 세로 길이
std::vector<std::vector<bool>> MAP; // MAP[i][j]: i 행 j 열로 이동할 수 있으면 true

int answer; // answer: 도착점에 갈 수 있을 때 동작 수의 최솟값, 갈 수 없으면 -1

void Solution(){

    std::queue<Move> q; // q: 탐색할 원숭이의 상태
    std::vector<std::vector<std::vector<bool>>> visited;    // visited[i][j][k]: i 행 j 열에 k 번 능력을 사용해서 도달했다면 true

    visited.assign(H, std::vector<std::vector<bool>>(W, std::vector<bool>(K+1, false)));

    // 초기 상태, (0, 0) 좌표에서 0 번의 움직임과 0 번의 능력을 사용
    q.push({0, 0, 0, 0});
    visited[0][0][0] = true;

    while(!q.empty()){
        Move curr = q.front();  // curr: 현재 원숭이의 상태
        q.pop();

        if(curr.y == H - 1 && curr.x == W - 1) {    // 도착지점에 도착한 경우
            answer = curr.cnt;  // 움직인 횟수 return
            return;
        }

        if(curr.ability < K){   // 능력을 사용할 수 있는 경우
            for(int dir=0; dir<8; ++dir){
                Move next = {curr.y + dirYH[dir], curr.x + dirXH[dir], curr.cnt + 1, curr.ability + 1}; // next: 능력을 사용했을 때의 상태

                if(next.y < 0 || next.x < 0 || next.y >= H || next.x >= W) {continue;}  // 범위 벗어나면 continue
                if(MAP[next.y][next.x] == false) {continue;}    // 장애물이 있다면 continue
                if(visited[next.y][next.x][next.ability] == true) {continue;}   // 이미 탐색했다면 continue

                q.push(next);
                visited[next.y][next.x][next.ability] = true;
            }
        }

        for(int dir=0; dir<4; ++dir){
            Move next = {curr.y + dirY[dir], curr.x + dirX[dir], curr.cnt + 1, curr.ability};   // next: 능력을 사용하지 않았을 때의 상태

            if(next.y < 0 || next.x < 0 || next.y >= H || next.x >= W) {continue;}  // 범위 벗어나면 continue
            if(MAP[next.y][next.x] == false) {continue;}    // 장애물이 있다면 continue
            if(visited[next.y][next.x][next.ability] == true) {continue;}   // 이미 탐색했다면 continue

            q.push(next);
            visited[next.y][next.x][next.ability] = true;
        }

    }

    answer = -1;    // 도착점까지 갈 수 없는 경우

    return;
}

void Input(){

    std::cin >> K;
    std::cin >> W >> H;

    MAP.assign(H, std::vector<bool>(W, false));

    for(int y=0; y<H; ++y){
        for(int x=0; x<W; ++x){
            int n;  // n: 0 이면 아무것도 없는 평지 1 이면 장애물
            std::cin >> n;
            MAP[y][x] = n == 0 ? true : false;
        }
    }

    return;
}

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Input();

    Solution();

    std::cout << answer;

    return 0;
}