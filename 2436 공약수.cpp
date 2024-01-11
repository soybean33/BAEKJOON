#include <iostream>
#include <cmath>
#include <algorithm>

int GCD, LCM;   // GCD: 최대공약수, LCM: 최소공배수

std::pair<long long, long long> answer;

int Gcd(int a, int b){  // a, b의 최대공약수 구하기
    if(b == 0) return a;
    return Gcd(b, a % b);
}

void Solution(){

    int divide = LCM / GCD;

    for(int i=1; i<=std::sqrt(divide); ++i){
        if(divide % i != 0) {continue;} // 나누어 떨어지지 않은 경우 continue

        int a = i;
        int b = divide / i;

        if(Gcd(a, b) == 1) {    // 서로소 인 경우
            answer.first = a;
            answer.second = b;
        }
    }

    return;
}

void Input(){
    
    std::cin >> GCD >> LCM;

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer.first * GCD << ' ' << answer.second * GCD;

    return 0;
}