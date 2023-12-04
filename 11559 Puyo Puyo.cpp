#include <iostream>
#include <vector>
#include <string>
#include <queue>

// 방향벡터
constexpr int dirY[4] = {0, 1, 0, -1};
constexpr int dirX[4] = {1, 0, -1, 0};

struct Coordinate{  // Coordinate: 좌표
    int y, x;   // y, x: 좌표
};

std::vector<std::vector<char>> MAP; // MAP[i][j]: i 행 j 열의 뿌요 색 -> '.' 빈 공간, 'R' 빨강, 'G' 초록, 'B' 파랑, 'P' 보라, 'Y' 노랑

int answer; // answer: 연쇄의 수

void Solution(){

    while(true){

        std::vector<Coordinate> pop;    // pop: 이번 연쇄에 터지는 뿌요의 좌표
        std::queue<Coordinate> q;   // q: 탐색할 좌표
        std::vector<std::vector<bool>> visited; // visited[i][j]: i 행 j 열 방문 여부

        visited.assign(12, std::vector<bool>(6, false));    // 방문 체크 공간 할당

        for(int y=0; y<12; ++y){
            for(int x=0; x<6; ++x){
                if(MAP[y][x] == '.') {continue;}    // 빈 공간의 경우 continue

                char color = MAP[y][x]; // color: 탐색을 시작할 뿌요의 색

                std::vector<Coordinate> tmpPop; // tmpPop: 터뜨릴 뿌요의 좌표 임시 저장

                tmpPop.push_back({y, x});
                q.push({y, x});
                visited[y][x] = true;

                while(!q.empty()){
                    Coordinate curr = q.front();    // curr: 탐색을 시작할 좌표
                    q.pop();

                    for(int dir=0; dir<4; ++dir){
                        Coordinate next = {curr.y + dirY[dir], curr.x + dirX[dir]}; // next: 다음 좌표

                        if(next.y < 0 || next.x < 0 || next.y >= 12 || next.x >= 6) {continue;} // 범위 벗어나면 continue
                        if(MAP[next.y][next.x] != color) {continue;}    // 탐색을 시작한 뿌요의 색과 다르면 continue
                        if(visited[next.y][next.x] == true) {continue;} // 이미 방문한 곳이면 continue
                        
                        tmpPop.push_back(next);
                        q.push(next);
                        visited[next.y][next.x] = true;
                    }
                }

                if(tmpPop.size() >= 4) {    // 같은 색이 4개 이상이여서 뿌요가 터질 수 있다면
                    for(const Coordinate& coordi : tmpPop){ // coordi: 터질 수 있는 뿌요의 좌표
                        pop.push_back(coordi);
                    }
                }
                
            }
        }

        if(pop.empty()) {return;}   // 뿌요가 터질 수 없다면 return

        ++answer;   // 연쇄 증가
        for(const Coordinate& coordi : pop){
            MAP[coordi.y][coordi.x] = '.';  // 뿌요가 터져 빈 공간이 됨
        }

        for(int x=0; x<6; ++x){
            std::vector<char> color;    // color: 한 열의 색 정보
            for(int y=11; y>=0; --y){
                if(MAP[y][x] == '.') {continue;}
                color.push_back(MAP[y][x]);
            }

            while(color.size() < 12) {  // 한 열이 12 행이 될 수 있도록 채움
                color.push_back('.');
            }

            for(int y=0; y<12; ++y){
                MAP[y][x] = color.back();
                color.pop_back();
            }
        }

    }

    return;
}

void Input(){

    MAP.assign(12, std::vector<char>(6, '.'));  // 빈 공간으로 채움

    for(int y=0; y<12; ++y){
        std::string s;  // s: 한 행 정보
        std::cin >> s;
        for(int x=0; x<6; ++x){
            MAP[y][x] = s[x];   // 해당 정보로 칸을 채움
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