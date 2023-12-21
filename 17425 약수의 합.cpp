#include <iostream>
#include <vector>

std::vector<long long> dp;  // dp[i]: 숫자 i 보다 작거나 같은 약수의 합

long long answer;   // answer: g(N)의 값

void Solution(){

    int N;  // N: g(N)을 구할 값
    std::cin >> N;

    answer = dp[N];

    return;
}

void Init(){

    dp.assign(1'000'001, 0);

    for(int i=1; i<=1'000'000; ++i){
        for(int j=i; j<=1'000'000; j+=i){   // 약수인 경우
            dp[j] += i; // 약수 값 더함
        }
    }

    for(int i=2; i<=1'000'000; ++i) {dp[i]+=dp[i-1];}   // 작거나 같은 약수의 합

    return;
}

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;  // T: 테스트 케이스의 개수
    std::cin >> T;

    Init();

    for(int tc=0; tc<T; ++tc){
        Solution();
        std::cout << answer << '\n';
    }

    return 0;
}