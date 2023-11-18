#include <iostream>
#include <vector>

int N;  // N: 행렬 A의 크기
long long B;    // B: B 제곱

std::vector<std::vector<long long>> A;  // A[i][j]: 행렬 A의 i 행 j 열의 값

std::vector<std::vector<long long>> answer; // answer[i][j]: 행렬 A를 B 제곱하고 1,000으로 나눈 i 행 j 열의 값

void Multi(std::vector<std::vector<long long>>& x, std::vector<std::vector<long long>>& y){

    std::vector<std::vector<long long>> tmp;
    tmp.assign(N, std::vector<long long>(N, 0));

    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            for(int k=0; k<N; ++k){
                tmp[i][j] += (x[i][k] * y[k][j]);
            }
            tmp[i][j] %= 1'000;
        }
    }

    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            x[i][j] = tmp[i][j];
        }
    }

    return;
}

void Solution(){

    while(B>0){
        if(B%2 == 1) {Multi(answer, A);}    // 홀수일 경우
        Multi(A, A);
        B /= 2;
    }

    return;
}

void Input(){

    std::cin >> N >> B;

    A.assign(N, std::vector<long long>(N, 0));
    answer.assign(N, std::vector<long long>(N, 0));

    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            std::cin >> A[i][j];
        }
        answer[i][i] = 1;
    }

    return;
}

int main(){

    Input();

    Solution();

    for(int i=0; i<N; ++i){
        for(int j=0; j<N; ++j){
            std::cout << answer[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}