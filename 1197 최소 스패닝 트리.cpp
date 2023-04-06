#include <iostream>
#include <queue>

struct Edge{
        int from, to;   // from, to: from 번호의 정점과 to 번호의 정점이 연결되어 있음
        int weight;     // weight: 가중치

        bool operator < (Edge next) const {     // 가중치 오름차순
                if(weight < next.weight) return false;
                if(weight > next.weight) return true;

                return false;
        } 
};

int V, E;       // V: 정점의 개수, E: 간선의 개수
std::priority_queue<Edge> pq;   // pq: 가중치 오름차순의 간선 정보
int parent[10001];      // parent[i]: i의 소속 정보
int ans;        // ans: 최소 스패닝 트리의 가중치

int Find(int now){      // now: 소속을 찾고자 하는 정점
        if(now == parent[now]) return now;      // 소속 찾음
        return parent[now] = Find(parent[now]); // 소속 찾기
}

void Union(int A, int B){       // A, B: 간선으로 연결하고자 하는 정점    
        int pa = Find(A);       // pa: A 정점의 소속
        int pb = Find(B);       // pb: B 정점의 소속

        if(pa == pb) return;    // 이미 소속이 같으면 return

        parent[pa] = pb;        // 소속 합침

        return;
}

void sol(){
        for(int i=1; i<=V; i++)
                parent[i] = i;  // 소속 정보 초기화

        while(!pq.empty()){
                Edge now = pq.top();    // now: 현재 연결하고자 하는 간선
                pq.pop();

                if(Find(now.from) == Find(now.to)) continue;    // 이미 같은 소속이면 continue

                ans += now.weight;      // 가중치 더함

                Union(now.from, now.to);        // 소속 합침
        }

}

void input(){
        std::cin >> V >> E;
        for(int i=0; i<E; i++){
                int A, B, C;    // A, B: 연결되어 있는 정점, C: A 정점과 B 정점을 연결하는 간선의 가중치
                std::cin >> A >> B >> C;
                pq.push({A, B, C});     // 가중치를 오름차순으로 하는 pq에 넣음
        }

        return;
}

int main(){
        input();
        sol();

        std::cout << ans;

        return 0;
}