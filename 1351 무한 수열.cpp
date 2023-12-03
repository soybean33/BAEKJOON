#include <iostream>
#include <unordered_map>

long long N;    // N: N
int P, Q;   // P: P, Q: Q

std::unordered_map<long long, long long> um;    // um[i]: i 인덱스의 값

long long answer;   // answer: A_N

long long Dfs(long long n){

    if(n==0) {return 1;}

    long long& ret = um[n];
    if(ret != 0) {return ret;}

    return ret = Dfs(n / P) + Dfs(n / Q);
}

void Solution(){

    answer = Dfs(N);

    return;
}

void Input(){

    std::cin >> N >> P >> Q;

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer;

    return 0;
}