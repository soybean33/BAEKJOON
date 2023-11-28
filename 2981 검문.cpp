#include <iostream>
#include <vector>
#include <algorithm>

int N;  // N: 종이에 적은 수의 개수
std::vector<int> V; // V[i]: 종이에 적은 i 번째 수

std::vector<int> answer;    // answer: 가능한 M의 모음

int Gcd(int a, int b){
    if(b==0) return a;
    return Gcd(b, a%b);
}

void Solution(){

    int gcd;

    std::sort(V.begin(), V.end());

    gcd = V[1] - V[0];

    for(int i=2; i<N; ++i) {gcd = Gcd(gcd, V[i] - V[i-1]);}

    for(int i=2; i*i <= gcd; ++i){
        if(gcd % i == 0){
            answer.push_back(i);
            answer.push_back(gcd / i);
        }
    }

    answer.push_back(gcd);

    std::sort(answer.begin(), answer.end());
    answer.erase(std::unique(answer.begin(), answer.end()), answer.end());

    return;
}

void Input(){

    std::cin >> N;

    V.assign(N, 0);

    for(int i=0; i<N; ++i){std::cin >> V[i];}

    return;
}

int main(){

    Input();

    Solution();

    for(const int& n : answer) {std::cout << n << ' ';}

    return 0;
}