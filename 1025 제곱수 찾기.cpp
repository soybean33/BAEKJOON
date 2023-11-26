#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

int N, M;   // N: 행의 크기, M: 열의 크기
std::vector<std::vector<int>> MAP;  // MAP[i][j]: i 행 j 열의 값

int answer = -1;    // naswer: 연두가 만들 수 있는 가장 큰 완전 제곱수, 완전 제곱수를 만들 수 없는 경우에 -1

bool Square(int num){   // 제곱수 판별
    int root = static_cast<int>(std::sqrt(num));    // root: 제곱수를 판별하기 위해 root
    return root * root == num;
}

void Solution(){

    for(int j=0; j<N; ++j){
        for(int i=0; i<M; ++i){
            for(int y=-N; y<N; ++y){
                for(int x=-M; x<M; ++x){
                    if(!x && !y) {continue;}    // 둘다 0 이면 continue
                    int r = j, c = i, num = 0;
                    while(0 <= r && r < N && 0 <= c && c < M){
                        num *= 10;
                        num += MAP[r][c];
                        
                        r += y;
                        c += x;

                        if(Square(num)) answer = std::max(answer, num);
                    }
                }
            }
        }
    }

    return;
}

void Input(){

    std::cin >> N >> M;

    MAP.assign(N, std::vector<int>(M, 0));

    for(int y=0; y<N; ++y){
        std::string S;
        std::cin >> S;
        for(int x=0; x<M; ++x){
            MAP[y][x] = S[x] - '0';
        }
    }

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer;

    return 0;
}