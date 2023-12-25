#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int A, B, C;    // A, B, C: 각 그룹의 돌의 개수

int answer; // answer: 돌을 같은 개수로 만들 수 있으면 1, 아니면 0

void Solution(){

    int sum = A + B + C;    // sum: 모든 돌의 개수

    if(sum % 3) {return;}   // 강호가 돌을 같은 개수로 만들 수 없으면 return

    std::vector<std::vector<bool>> visited; // visited[i][j]: X 그룹의 돌의 개수가 i, Y 그룹의 돌의 개수가 j 일 경우 방문 여부
    visited.assign(sum + 1, std::vector<bool>(sum + 1, false)); // 공간 할당

    std::queue<std::pair<int, int>> q;  // q: X, Y 그룹의 돌의 개수를 담고 있는 큐

    // 초기 세팅
    q.push({A, B});
    visited[A][B] = true;

    std::vector<int> tmp;
    tmp.assign(3, 0);

    while(!q.empty()){        
        tmp[0] = q.front().first;   // X 그룹
        tmp[1] = q.front().second;  // Y 그룹
        tmp[2] = sum - tmp[0] - tmp[1]; // 나머지 돌의 개수

        q.pop();

        for(int i=0; i<3; ++i){
            for(int j=0; j<3; ++j){
                if(tmp[i] < tmp[j]) {
                    int x = tmp[i] * 2; // x: 작은 쪽은 x
                    int y = tmp[j] - tmp[i];    // y: 큰 쪽은 y

                    if(visited[x][y]) {continue;}   // 이미 방문한 적 있다면 continue

                    q.push({x, y});
                    visited[x][y] = true;
                }
            }
        }
    }

    answer = visited[sum / 3][sum / 3]; // 가능한 경우의 수면 1

    return;
}

void Input(){

    std::cin >> A >> B >> C;

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer;

    return 0;
}