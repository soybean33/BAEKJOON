#include <iostream>
#include <vector>
#include <algorithm>

long long N;    // N: 한 변의 주사위의 개수
std::vector<int> V; // V[i]: 주사위의 여섯 면의 수

long long answer;   // answer: 보이는 5개의 면에 쓰여 있는 수의 합의 최솟값

void Solution(){

    int max_num = 0;    // max_num: 주사위의 여섯 면 중 가장 큰 값

    for(int i=0; i<6; ++i){
        answer += V[i];
        max_num = std::max(max_num, V[i]);
    }

    if(N == 1) {    // 주사위 1개만 사용할 경우
        answer -= max_num;  // 가장 큰 면을 안보이게
    }
    else{
        answer = 0;

        // 최대 3면이 보이게 되므로 마주보는 면 중 작은 값으로 설정
		V[0] = std::min(V[0], V[5]);
		V[1] = std::min(V[1], V[4]);
		V[2] = std::min(V[2], V[3]);
	
        // 정렬
		std::sort(V.begin(), V.begin() + 3);

		int sum1 = V[0];
		int sum2 = sum1 + V[1];
		int sum3 = sum2 + V[2];


		answer += sum3 * 4;
		answer += sum2 * (4 * (N - 2) + 4 * (N - 1));
		answer += sum1 * (4 * (N - 1) * (N - 2) + (N - 2) * (N - 2));
    }

    return;
}

void Input(){

    std::cin >> N;
    V.assign(6, 0);

    for(int i=0; i<6; ++i){std::cin >> V[i];}

    return;
}

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Input();

    Solution();

    std::cout << answer;

    return 0;
}