#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string A, B;

std::vector<std::vector<int>> dp;
std::string answer;

void Solution(){

    dp.assign(B.length(), std::vector<int>(A.length(), 0));

    for(int i=1; i<B.length(); ++i){
        for(int j=1; j<A.length(); ++j){
            if(A[j] == B[i]) {dp[i][j] = dp[i-1][j-1] + 1;} // 같은 문자
            else {dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);} // 다른 문자
        }
    }

    int col = A.length() - 1;
    int row = B.length() - 1;

    while(dp[row][col]){
        if(dp[row][col] == dp[row-1][col]){--row;}
        else if(dp[row][col] == dp[row][col-1]){--col;}
        else{
            answer += A[col];
            --row;
            --col;
        } 
    }

    return;
}

void Input(){

    std::string tmp1, tmp2;

    std::cin >> tmp1;
    std::cin >> tmp2;

    A = ' ' + tmp1;
    B = ' ' + tmp2;

    return;
}

int main(){

    Input();

    Solution();

    std::cout << dp[B.length()-1][A.length()-1] << '\n';
    if(answer.length() > 0) {
        std::reverse(answer.begin(), answer.end());
        std::cout << answer;
    }

    return 0;
}