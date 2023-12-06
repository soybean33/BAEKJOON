#include <iostream>
#include <vector>

int T;  // T: 테스트 케이스의 개수
int N;  // N: 학생의 수
std::vector<int> STUDENT;   // STUDENT[i]: i 학생이 선택한 학생의 번호

std::vector<bool> visited;  // visited[i]: i 학생이 하고 싶어하는 학생을 고르면 true
std::vector<bool> done; // done[i]: i 학생이 사이클이 만들어져서 팀이 만들어지면 true
int cnt;

int answer;

void Cycle(int curr){

    visited[curr] = true;   // 팀을 만들어 줄 것

    int next = STUDENT[curr];   // curr 학생이 선택한 학생 next

    if(visited[next] == false) {Cycle(next);}
    else if(done[next] == false) {
        for(int i=next; i!=curr; i=STUDENT[i]){++cnt;}
        ++cnt;
    }
    done[curr] = true;
}

void Solution(){

    visited.assign(N+1, false);
    done.assign(N+1, false);
    cnt = 0;

    for(int i=1; i<=N; ++i){
        if(visited[i] == false) {Cycle(i);} // i 학생이 아직 팀이 없다면, 사이클을 만들어 보기
    }

    answer = N - cnt;

    return;
}

void Input(){

    std::cin >> N;

    STUDENT.assign(N+1, 0);

    for(int i=1; i<=N; ++i){std::cin >> STUDENT[i];}    

    return;
}

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> T;

    for(int tc=0; tc<T; ++tc){
        Input();
        Solution();
        std::cout << answer << '\n';
    }

    return 0;
}