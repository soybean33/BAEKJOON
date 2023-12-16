#include <iostream>
#include <vector>

int N;  // N: 물건의 개수
int M;  // M: 미리 측정된 물건 쌍의 개수
std::vector<std::vector<int>> arr;  // arr[i][j]: i 물건이 j 물건보다 무겁다면 1, 아니면 -1, 측정되지 않으면 0

int answer; // answer: 비교 결과를 알 수 없는 물건의 개수

void Solution(){

    // 플로이드 워셜
    for(int t=1; t<=N; ++t){
        for(int i=1; i<=N; ++i){
            for(int j=1; j<=N; ++j){
                if(arr[i][t] == arr[t][j] && arr[i][t] != 0) {arr[i][j] = arr[i][t];}
            }
        }
    }

    for(int i=1; i<=N; ++i){
        int answer = N - 1;
        for(int j=1; j<=N; ++j){
            if(arr[i][j] != 0) {--answer;}
        }
        std::cout << answer << '\n';
    }

    return;
}

void Input(){

    std::cin >> N;
    std::cin >> M;

    arr.assign(N+1, std::vector<int>(N+1, 0));

    for(int i=0; i<M; ++i){
        int a, b;
        std::cin >> a >> b;
        arr[a][b] = 1;
        arr[b][a] = -1;
    }

    return;
}

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Input();

    Solution();

    return 0;
}