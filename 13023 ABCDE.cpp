#include <iostream>
#include <vector>

int N, M;   // N: 사람의 수, M: 친구 관계의 수
std::vector<std::vector<int>> v;    // v[i][j]: i 번 사람과 j 번째 사람 친구

bool answer = false;    // answer: 문제의 조건이 맞으면 1 아니면 0

void Dfs(int k, int curr, std::vector<bool>& visited){
    if(k==4){   // 4번 친구라면
        answer = true;  // 문제의 조건을 만족
        return;
    }

    for(int j=0; j<v[curr].size(); ++j){
        int next = v[curr][j];  // next: 다음 친구
        if(visited[next]) continue; // 이미 친구라면 continue
        
        visited[next] = true;
        Dfs(k+1, next, visited);
        visited[next] = false;
    }
}

void Solution(){

    for(int i=0; i<N; ++i){
        std::vector<bool> visited;
        visited.assign(N, false);

        visited[i] = true;
        Dfs(0, i, visited);
        if(answer) break;
    }

    return;
}

void Input(){

    std::cin >> N >> M;
    
    v.assign(N, std::vector<int>(0, 0));

    for(int i=0; i<M; ++i){
        int a, b;   // a, b: a와 b는 친구
        std::cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);  // 양방향
    }    

    return;
}

int main(){

    Input();

    Solution();

    if(answer) {std::cout << 1;}
    else {std::cout << 0;}

    return 0;
}