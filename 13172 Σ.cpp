#include <iostream>
#include <numeric>

constexpr int MODULAR = 1'000'000'007;  // MODULAR: 모듈러 값

int M;  // M: 주사위의 수
int N, S;   // N: 주사위의 면의 수, S: 주사위의 모든 면에 적힌 수의 합

long long answer;   // answer: 모든 주사위를 한 번씩 던졌을 때 나온 숫자들의 합의 기댓값

long long Fermat(int x, int y){ // 페르마 소정리
    if(y == 1) return x;
    if(y % 2 == 1) return x * Fermat(x, y-1) % MODULAR;

    long long ret = Fermat(x, y/2);

    return ret * ret % MODULAR;
}

void Solution(){

    while(M--){
        std::cin >> N >> S;

        int gcd = std::gcd(N, S);   // gcd: 최대 공약수

        // 기약분수
        N /= gcd;
        S /= gcd;

        answer += S *  Fermat(N, MODULAR - 2) % MODULAR;
        answer %= MODULAR;
    }

    return;
}

void Input(){

    std::cin >> M;

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer;

    return 0;
}