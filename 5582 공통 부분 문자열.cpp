#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string S1, S2; // S1, S2: 두 문자열

int answer; // 두 문자열에 모두 포함 된 부분 문자열 중 가장 긴 것

void Solution(){

    std::vector<std::vector<int>> dp;   // dp[i][j]: 부분 문자열 중 가장 긴 것

    dp.assign(S2.length(), std::vector<int>(S1.length(), 0));

    for(int i=0; i<S2.length(); ++i){
        for(int j=0; j<S1.length(); ++j){
            if(S2[i] != S1[j]) {continue;}  // 다른 문자면 continue

            dp[i][j] = 1;   // 같은 문자면 1

            if(i >= 1 && j >= 1) {dp[i][j] += dp[i-1][j-1];}    // 직전의 같은 문자열의 길이를 더함
            answer = std::max(answer, dp[i][j]);    // 문자열 길이 갱신
        }
    }

    return;
}

void Input(){

    std::cin >> S1 >> S2;

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer;

    return 0;
}