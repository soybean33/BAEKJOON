#include <iostream>
#include <vector>
#include <algorithm>

struct Lecture{ // 강연 정보
    int p, d;   // p: 강연료, d: 강연 날짜
};

int N;  // N: 강연 요청 개수
std::vector<Lecture> lectures;  // lectures[i]: 요청 받은 강연 정보

std::vector<bool> days; // days[i]: i 번째 날의 강의 여부

int answer; // answer: 최대로 벌 수 있는 돈

bool Cmp(const Lecture& left, const Lecture& right){
    if(left.p != right.p) {return left.p > right.p;}    // 강연료를 기준으로 내림차순 정렬
    return false;
}

void Solution(){

    days.assign(10'001, false);

    std::sort(lectures.begin(), lectures.end(), Cmp);   // 강연료를 기준으로 내림차순 정렬

    for(const Lecture& lecture : lectures){
        if(days[lecture.d] == false){   // 강연이 없는 경우
            answer += lecture.p;
            days[lecture.d] = true;
        }
        else{   // 강연이 있는 경우
            for(int j=lecture.d - 1; j >= 1; --j){
                if(days[j] == false){
                    days[j] = true;
                    answer += lecture.p;
                    break;
                }
            }
        }
    }

    return;
}

void Input(){

    std::cin >> N;

    lectures.assign(N, {0, 0});

    for(int i=0; i<N; ++i){std::cin >> lectures[i].p >> lectures[i].d;}

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