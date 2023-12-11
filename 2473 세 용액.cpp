#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int N;  // N: 전체 용액의 수
std::vector<long long> Liquid;  // Liquid[i]: i 번째 용액의 특성값

std::vector<int> answers;   // answers[i]: 특성값이 0에 가장 가까운 용액을 만들어내는 세 용액의 특성 값

void Solution(){

    std::sort(Liquid.begin(), Liquid.end());    // 용액의 특성을 기준으로 오름차순 정렬

    answers.assign(3, 0);

    long long mix = 3'000'000'001;  // mix: 특성값의 최대 값

    int left, right;    // left, right: 이분탐색을 위한 인덱스
    for(int fix=0; fix<N-2; ++fix){ // fix: 한 용액 고정
        left = fix + 1;
        right = N - 1;
        while(left < right){
            long long value = Liquid[fix] + Liquid[left] + Liquid[right];   // value: 용액의 특성값

            if(std::abs(value) < mix) { // 더 0에 가까운 경우
                mix = std::abs(value);

                // 용액의 특성값 기록
                answers[0] = Liquid[fix];
                answers[1] = Liquid[left];
                answers[2] = Liquid[right];
            }

            if(value < 0) {++left;} // 음수의 경우 더 큰 특성값 조합
            else {--right;} // 양수의 경우 더 작은 특성값 조합
        }
    }

    return;
}

void Input(){

    std::cin >> N;

    Liquid.assign(N, 0);

    for(int i=0; i<N; ++i) {std::cin >> Liquid[i];}

    return;
}

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Input();

    Solution();

    for(const int& answer : answers) {std::cout << answer << ' ';}

    return 0;
}