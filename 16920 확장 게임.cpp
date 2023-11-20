#include <iostream>
#include <string>
#include <vector>
#include <queue>

// 방향 벡터
constexpr int dirY[4] = {0, 1, 0, -1};
constexpr int dirX[4] = {1, 0, -1, 0};

struct Coordinate{  // Coordinate: 좌표
    int y, x;   // y, x: 좌표
};

int N, M, P;    // N, M: 격자판의 크기, P: 플레이어의 수
std::vector<std::vector<int>> MAP;  // MAP[i][j]: i 행 j 열의 정보, 벽(-1), 빈 칸(0), 플레이어(1~9)
std::vector<int> S; // S[i]: i 플레이어가 이동할 수 있는 칸의 수
std::vector<std::queue<Coordinate>> castle; // castle[i]: i 플레이어의 좌표

std::vector<int> answer;    // answer[i]: i 플레이어가 가진 성의 수

void Solution(){

    bool flag = true;   // flag: 더 이상 확장할 수 없으면 false

    while(flag){

        flag = false;

        for(int castleNum=1; castleNum<=P; ++castleNum){    // castleNum: 움직일 플레이어 번호
            for(int s=0; s<S[castleNum]; ++s){
                int castleSize = castle[castleNum].size();  // castleSize: 움직일 플레이어의 수

                if(castleSize == 0) {break;}    // 움직일 것이 없다면 break

                for(int i=0; i<castleSize; ++i){
                    Coordinate curr = castle[castleNum].front();    // curr: 현재 좌표
                    castle[castleNum].pop();

                    for(int dir=0; dir<4; ++dir){
                        Coordinate next = {curr.y + dirY[dir], curr.x + dirX[dir]}; // next: 다음 좌표

                        if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= M) {continue;}  // 범위 밖으로 나가면 continue
                        if(MAP[next.y][next.x] != 0) {continue;}    // 빈 곳이 아니라면 continue

                        flag = true;    // 플레이어가 다음에도 움직일 수 있음
                        castle[castleNum].push(next);   // 다음에 움직일 수 있도록 넣음
                        MAP[next.y][next.x] = castleNum;    // 성 입력
                        ++answer[castleNum];    // 성 개수 카운트
                    }
                }
            }
        }
    }

    return;
}

void Input(){

    std::cin >> N >> M >> P;

    MAP.assign(N, std::vector<int>(M, 0));
    S.assign(P+1, 0);
    castle.assign(P+1, std::queue<Coordinate>{});

    answer.assign(P+1, 0);

    for(int i=1; i<=P; ++i){std::cin >> S[i];}

    for(int y=0; y<N; ++y){
        std::string s;  // s[i]: 행의 i 번째 정보
        std::cin >> s;
        for(int x=0; x<M; ++x){
            if(s[x] == '.') {continue;} // 빈칸
            if(s[x] == '#') {   // 벽
                MAP[y][x] = -1;
                continue;
            }

            // 플레이어
            MAP[y][x] = s[x] - '0';
            castle[s[x] - '0'].push({y, x});
            ++answer[s[x] - '0'];   // 성 개수 카운트
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

    for(int i=1; i<=P; ++i){
        std::cout << answer[i] << ' ';
    }

    return 0;
}