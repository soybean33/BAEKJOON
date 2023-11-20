#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int N;  // N: 정수의 개수
std::vector<int> V; // V[i]: i 번째 수

int answer = -1;    // answer: 정수를 하나를 빼서 만들 수 있는 가장 큰 최대공약수
int k = -1; // k: 뺀 수

void Solution(){

    std::vector<int> LtoR;  // LtoR[i]: 왼쪽부터 차례로 최대공약수를 누적한 배열
    std::vector<int> RtoL;  // RtoL[i]: 오른쪽부터 차례로 최대공약수를 누적한 배열

    LtoR.assign(N, 0);
    RtoL.assign(N, 0);

    LtoR[0] = V[0];
    RtoL[N-1] = V[N-1];

    // 왼쪽부터 오른쪽으로 최대공약수 구함
    for(int i=1; i<N; ++i){LtoR[i] = std::gcd(std::max(LtoR[i-1], V[i]), std::min(LtoR[i-1], V[i]));}

    // 오른쪽에서 왼쪽으로 최대공약수 구함
    for(int i=N-2; i>=0; --i){RtoL[i] = std::gcd(std::max(RtoL[i+1], V[i]), std::min(RtoL[i+1], V[i]));}

    // 유클리드 호제법
    for(int i=0; i<N; ++i){
        if(i==0) {
            answer = std::max(answer, RtoL[1]);
            k = V[i];
        }
        else if(i == N-1){
            if(answer < LtoR[N-2]){
                answer = LtoR[N-2];
                k = V[i];
            }
        }
        else{
            if(answer < std::gcd(LtoR[i-1], RtoL[i+1])){
                answer = std::gcd(LtoR[i-2], RtoL[i+1]);
                k = V[i];
            }
        }
    }

    return;
}

void Input(){

    std::cin >> N;

    V.assign(N, 0);

    for(int i=0; i<N; ++i) {std::cin >> V[i];}


    return;
}

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Input();

    Solution();

    if(k % answer == 0) {std::cout << "-1";}    // 정답이 없는 경우
    else {std::cout << answer << ' ' << k;}

    return 0;
}