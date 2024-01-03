#include <iostream>
#include <string>
#include <vector>

int N, K;   // N: 숫자의 개수, K: 지울 수 있는 수의 개수
std::string S;  // S[i]: 주어지는 i 번째 수
std::vector<char> v;    // v[i]: K를 지웠을 때 얻을 수 있는 가장 큰 수

std::string answer; // // answer: K를 지웠을 때 얻을 수 있는 가장 큰 수

void Solution(){

    int cnt = 0;    // cnt: 지운 수 개수

    for(const char& c : S){ // c: 이번에 판단할 수

        while(!v.empty() && cnt < K && c > v.back()){
            ++cnt;
            v.pop_back();
        }
        v.push_back(c);
    }

    while(cnt < K) {
        ++cnt;
        v.pop_back();
    }

    for(const char& c : v) {
        answer += c;
    }

    return;
}

void Input(){

    std::cin >> N >> K;

    std::cin >> S;

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer;

    return 0;
}