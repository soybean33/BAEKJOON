#include <iostream>
#include <vector>
#include <algorithm>

struct Work{    // Work: 과제
    int d, w;   // d: 과제 마감일까지 남은 일수, w: 과제의 점수
};

int N;  // N: 과제의 개수
std::vector<Work> WORKS;    // WORKS[i]: 주어진 과제들

std::vector<int> v; // v[i]: i 일에 할 과제의 점수

int answer; // answer: 얻을 수 있는 점수의 최댓값

bool Cmp(const Work& left, const Work& right) { // left, right: 정렬할 과제
    if(left.w != right.w) {return left.w > right.w;}    // 점수를 기준으로 내림차순 정렬
    return false;
}

void Solution(){

    std::sort(WORKS.begin(), WORKS.end(), Cmp); // 과제의 점수를 기준으로 내림차순 정렬

    v.assign(1'001, 0);

    for(const Work work : WORKS) {  // 과제의 점수가 높은 것 부터 탐색
        for(int j=work.d; j>0; --j){    // 미룰 수 있을 때 까지 미룸
            if(v[j] == 0) { // 과제를 할 수 있는 날이라면
                v[j] = work.w;  // 좌제 진행
                break;
            }
        }
    }

    for(int i=1; i<=1'000; ++i){answer += v[i];}    // 점수의 최댓값

    return;
}

void Input(){

    std::cin >> N;

    WORKS.assign(N, {0, 0});

    for(int i=0; i<N; ++i) {std::cin >> WORKS[i].d >> WORKS[i].w;}

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