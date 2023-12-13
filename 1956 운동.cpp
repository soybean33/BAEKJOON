#include <iostream>
#include <vector>
#include <algorithm>

constexpr int INF = 10e8;   // INF: 나올 수 없는 값

int V, E;   // V: 마을의 개수, E: 도로의 개수

std::vector<std::vector<int>> v;    // v[i][j]: i 마을에서 j 마을로 가는 최소 비용

int answer = INF;   // answer: 최소 사이클의 도로 길이의 합

void Solution(){

    // 플로이드 워셜
    for(int t=1; t<=V; ++t){
        for(int i=1; i<=V; ++i){
            for(int j=1; j<=V; ++j){
                v[i][j] = std::min(v[i][j], v[i][t] + v[t][j]);
            }
        }
    }

    for(int i=1; i<=V; ++i){answer = std::min(answer, v[i][i]);}

    return;
}

void Input(){

    std::cin >> V >> E;

    v.assign(V + 1, std::vector<int>(V + 1, INF));

    for(int i=0; i<E; ++i){
        int a, b, c;
        std::cin >> a >> b >> c;
        v[a][b] = c;
    }

    return;
}

int main(){

    Input();

    Solution();

    if(answer == INF) {std::cout << -1;}
    else std::cout << answer;

    return 0;
}