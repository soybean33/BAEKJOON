#include <iostream>
#include <vector>
#include <queue>
#include <string>

struct Node{    // Node: 탐색할 숫자
    int num;    // num: 숫자
    int cnt;    // cnt: 변경한 횟수
};

std::vector<bool> DAT;  // DAT[i]: i 가 소수면 true
int start, end; // start: 시작 비밀번호, end: 변경 비밀 번호

int answer; // answer: 두 소수 사이의 변환이 필요한 최소 횟수, 불가능한 경우 Impossible

void Solution(){

    std::queue<Node> q; // q: 변경할 숫자
    std::vector<bool> visited;  // visited[i]: i 숫자 방문 여부

    q.push({start, 0});
    visited.assign(10'000, false);
    visited[start] = true;

    answer = -1;

    while(!q.empty()){
        Node curr = q.front();  // curr: 현재 시도해볼 숫자
        q.pop();

        if(curr.num == end) {   // 비밀번호 변경 완료
            answer = curr.cnt;
            return;
        }

        for(int i=0; i<4; ++i){
            Node next = {0, curr.cnt + 1};  // next: 비밀 번호 변경

            for(int j=0; j<10; ++j){
                std::string s = std::to_string(curr.num);   // s: 비밀번호 변경을 위해 문자열로 변경
                s[i] = j + '0';
                next.num = std::stoi(s);

                if(next.num < 1'000) {continue;}    // 4자리가 아니면 continue
                if(DAT[next.num] == false) {continue;}  // 소수가 아니면 continue
                if(visited[next.num] == true) {continue;}   // 이미 변경 한 적 있다면 continue
                
                q.push(next);
                visited[next.num] = true;
            }
        }
    }
    
    return;
}

void Input(){

    std::cin >> start >> end;

    return;
}

void Init(){

    DAT.assign(10'000, true);

    // 에라토스테네스의 체
    for(int i=2; i<10'000; ++i){
        for(int j=2; i*j < 10'000; ++j){
            DAT[i*j] = false;
        }
    }

    return;
}

int main(){

    int T;

    std::cin >> T;

    Init();

    for(int tc=0; tc<T; ++tc){

        Input();

        Solution();

        if(answer == -1) {std::cout << "impossible\n";}
        else {std::cout << answer << '\n';}
    }

    return 0;
}