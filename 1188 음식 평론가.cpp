#include <iostream>

int N, M;   // N: 소시지의 수, M: 평론가의 수

int answer; // answer: 모든 평론가에게 동일한 양을 주기 위해 필요한 칼질 횟수의 최솟값

int Gcd(int n, int m){  // 최대 공약수 구하기

    if(n % m == 0) {return m;}

    return Gcd(m, n % m);
}

void Solution(){

    answer = M - Gcd(N, M); // 칼질의 횟수

    return;
}

void Input(){

    std::cin >> N >> M;

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer;

    return 0;
}