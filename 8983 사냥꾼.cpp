#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int M, N, L;    // M: 사대의 수, N: 동물의 수, L: 사정거리
std::vector<int> v; // v[i]: i 번째 사대의 x 좌표
std::vector<std::pair<int, int>> coordi;    // coordi[i]: i 번째 동물의 좌표 x, y

int answer; // answer: 잡을 수 있는 동물의 수

void Solution(){

    std::sort(v.begin(), v.end());  // 사대의 위치 오름차순 정렬
    for(int i=0; i<N; ++i){
        int left = 0, right = M - 1;    // left, right, 이분 탐색
        while(left <= right) {
            int middle = left + (right - left) / 2; // middle: 중앙값

            int cal = std::abs(v[middle] - coordi[i].first) + coordi[i].second;
            if(cal <= L) {
                ++answer;
                break;
            }
            else{
                if(coordi[i].first >= v[middle]) {left = middle + 1;}
                else {right = middle - 1;}
            }
        }
    }

}

void Input(){

    std::cin >> M >> N >> L;

    v.assign(M, 0);
    for(int i=0; i<M; ++i) {std::cin >> v[i];}

    coordi.assign(N, {0, 0});
    for(int i=0; i<N; ++i) {std::cin >> coordi[i].first >> coordi[i].second;}

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