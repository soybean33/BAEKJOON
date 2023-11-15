#include <iostream>
#include <vector>
#include <algorithm>

int N;  // N: 수열 A의 크기
std::vector<int> A; // A[i]: 수열 A의 i 번째 수
std::vector<int> dp;    // dp[i]: i 번째까지 증가하는 수열의 길이
std::vector<int> answer;    // answer[i]: 가장 긴 증가하는 부분 수열

void Solution(){

    int cnt = 0;    // cnt: 증가하는 수열의 길이
    std::vector<int> v; // v[i]

    dp.assign(N+1, 0);
    v.push_back(A[1]);

    for(int i=2; i<=N; ++i){
        if(v[cnt] < A[i]){  // 증가하는 수열의 경우
            v.push_back(A[i]);
            ++cnt;
            dp[i] = cnt;    // 증가
        }
        else{   // 감소하는 경우
            int pos = std::lower_bound(v.begin(), v.end(), A[i]) - v.begin();
            v[pos] = A[i];
            dp[i] = pos;
        }
    }

    int LIS_size = cnt;

    for(int i=N; i>=0; --i){
        if(dp[i] == LIS_size){
            answer.push_back(A[i]);
            --LIS_size;
        }
    }

    return;
}

void Input(){

    std::cin >> N;

    A.assign(N+1, 0);
    for(int i=1; i<=N; ++i) {std::cin >> A[i];}

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer.size() << '\n';
    while(!answer.empty()){
        std::cout << answer.back() << ' ';
        answer.pop_back();
    }

    return 0;
}