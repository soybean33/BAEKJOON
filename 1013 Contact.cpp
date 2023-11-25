#include <iostream>
#include <string>

std::string BITS;   // BITS[i]: 전파

void Solution(){

    int idx = 0;    // idx: 검사중인 전파의 인덱스
    bool flag = true;   // flag: 직녀성의 전파 기록을 가지고 있으면 true

    while(idx < BITS.length() && flag){
        switch(BITS[idx]){
            case '0':   // 0인경우
                ++idx;
                if(BITS.length() <= idx || '0' == BITS[idx]) {flag = false;}
                ++idx;
                break;
            case '1':   // 1인경우
                ++idx;

                int next_one = BITS.find('1', idx);
                if(next_one == std::string::npos || next_one - idx < 2) {
                    flag = false;
                    break;
                }

                int next_zero = BITS.find('0', next_one);
                if(next_zero == BITS.length() - 1) {
                    flag = false;
                    break;
                }

                if(next_zero == std::string::npos) {
                    idx = BITS.size();
                    break;
                }

                idx = next_zero;
                if('0' == BITS[next_zero + 1] && 1 < next_zero - next_one){
                    --idx;
                    break;
                }
        }
    }

    std::cout << (idx == BITS.length() && flag ? "YES" : "NO") << '\n';

    return;
}

void Input(){

    std::cin >> BITS;

    return;
}

int main(){

    int T;  // T: 테스트 케이스의 개수
    std::cin >> T;

    while(T--){
        Input();
        Solution();
    }

    return 0;
}