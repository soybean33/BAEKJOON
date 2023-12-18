#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int N, M;
std::vector<int> v;
int idx;

int answer;

void Solution(){

    std::sort(v.begin(), v.end());

    for(int i=N-1; i>=idx; i-=M) {answer += v[i] * 2;}

    for(int i=0; i<idx; i+=M) {answer += std::abs(v[i] * 2);}

    answer -= std::max(std::abs(v[0]), std::abs(v[N-1]));

    return;
}

void Input(){

    std::cin >> N >> M;

    v.assign(N, 0);

    for(int i=0; i<N; ++i) {
        std::cin >> v[i];
        if(v[i] < 0) {++idx;}
    }

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer;

    return 0;
}