#include <iostream>
#include <queue>
#include <vector>

struct State{   // State: 상태 저장
    int display;    // display: 화면에 있는 아이콘의 수
    int clip;   // clip: 클립보드에 있는 아이콘의 수
    int time;   // time: 연산에 소요된 시간
};

int S;  // S: 영선이가 화면에 만들 아이콘의 수

int answer; // answer: 이모티콘을 S개 만들기 위해 필요한 시간의 최솟값

void Solution(){

    std::queue<State> q;    // q: 시도해 볼 상태
    std::vector<std::vector<bool>> visited; // visited[i][j]: 아모티콘이 화면에 i개, 클립보드에 j개 있는 상태 체크 여부

    q.push({1, 0, 0});  // 화면에 이모티콘 1개가 있는 상태에서 시작

    visited.assign(2'000, std::vector<bool>(2'000, false));
    visited[1][0] = true;

    while(!q.empty()){
        State curr = q.front(); // curr: 현재 상태
        q.pop();

        if(curr.display == S) { // 화면에 S개의 이모티콘이 있다면
            answer = curr.time; // Bfs 이므로 최소 시간
            return;
        }

        if(curr.display > 0 && curr.display < 2'000){   // 화면에 이모티콘이 있는 경우에 대하여
            // 화면에 있는 이모티콘을 모두 복사해서 클립보드에 저장한다
            if(visited[curr.display][curr.display] == false){
                visited[curr.display][curr.display] = true;
                q.push({curr.display, curr.display, curr.time + 1});
            }

            // 화면에 있는 이모티콘 중 하나를 삭제한다
            if(visited[curr.display - 1][curr.clip] == false){
                visited[curr.display - 1][curr.clip] = true;
                q.push({curr.display - 1, curr.clip, curr.time + 1});
            }
        }

        if(curr.clip > 0 && curr.display + curr.clip < 2'000){  // 클립보드에 이모티콘이 있는 경웨 대하여
            // 클립보드에 있는 모든 이모티콘을 화면에 붙여넣기 한다
            if(visited[curr.display + curr.clip][curr.clip] == false){
                visited[curr.display + curr.clip][curr.clip] = true;
                q.push({curr.display + curr.clip, curr.clip, curr.time + 1});
            }
        }
    }

    return;
}

void Input(){

    std::cin >> S;

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer;

    return 0;
}