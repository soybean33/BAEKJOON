#include <iostream>
#include <algorithm>

struct Roll{
    int r, c, s;    // r, c: 기준 좌표, s: 반경
};

int N, M, K;    // N: 배열 A의 행 크기, M: 배열 A의 열 크기, K: 회전 연산의 개수
int A[55][55];  // A[i][j]: i행 j열의 값
Roll roll[7];   // roll[i]: 회전 정보 -> (r, c)를 기준으로 s만큼
int visited[7]; // visited[i]: 방문 체크

int ans = 21e8; // ans: 배열 A의 최소값

void reverseRollArray(int idx, int top[][55], int right[][55], int buttom[][55], int left[][55]){   // idx: 연산 번호
    int R = roll[idx].r;    // R: 행 번호
    int C = roll[idx].c;    // C: 열 번호
    int S = roll[idx].s;    // S: 반경

    for(int s=1; s<=S; s++){
        int cpyNum = s * 2;

        // 복구
        for(int i=0; i<cpyNum; i++){
            A[R-s][C-s+i] = top[s][i];  // 위
            A[R+s][C-s+i+1] = buttom[s][i]; // 아래
        }

        // 복구
        for(int j=0; j<cpyNum; j++){
            A[R-s+j][C+s] = right[s][j];    // 오른쪽
            A[R-s+j+1][C-s] = left[s][j];   // 왼쪽
        }
    }

    return;
}

void rollArray(int idx, int top[][55], int right[][55], int buttom[][55], int left[][55]){  // idx: 연산 번호
    int R = roll[idx].r;    // R: 행 번호
    int C = roll[idx].c;    // C: 열 번호
    int S = roll[idx].s;    // S: 반경

    for(int s=1; s<=S; s++){    // 반경의 크기에 따라 연산
        int cpyNum = s * 2; // cpyNum: 저장해야하는 배열의 길이

        // 반경만큼 배열 복사
        for(int i=0; i<cpyNum; i++){
            top[s][i] = A[R-s][C-s+i];  // 위
            buttom[s][i] = A[R+s][C-s+i+1]; // 아래
        }
        // 밴경만큼 배열 복사
        for(int j=0; j<cpyNum; j++){
            right[s][j] = A[R-s+j][C+s];    // 오른쪽
            left[s][j] = A[R-s+j+1][C-s];   // 왼쪽
        }

        // 반경만큼 배열 붙여넣기
        for(int i=0; i<cpyNum; i++){
            A[R-s][C-s+i+1] = top[s][i];    // 위
            A[R+s][C-s+i] = buttom[s][i];   // 아래
        }

        // 반경만큼 배열 붙여넣기
        for(int j=0; j<cpyNum; j++){
            A[R-s+j+1][C+s] = right[s][j];  // 오른쪽
            A[R-s+j][C-s] = left[s][j]; // 왼쪽
        }
    }

    return;
}


void DFS(int depth){    // depth: 연산 수행 횟수

    if(depth == K){ // 모든 연산 진행
        for(int j=0; j<N; j++){
            int sum = 0;    // sum: j 행의 합
            for(int i=0; i<M; i++){
                sum += A[j][i];
            }
            ans = std::min(ans, sum);   // 최소값 갱신
        }

        return;
    }

    for(int i=0; i<K; i++){
        if(visited[i] != 0) continue;   // 이미 사용한 연산이면 continue

        visited[i] = 1; // 연산 사용 체크
        int top[30][55] = {0,}; // top[i][j]: i반경으로 회전하는 위쪽 배열의 값
        int right[30][55] = {0,};   // right[i][j]: i 반경으로 회전하는 오른쪽 배열의 값
        int buttom[30][55] = {0,};  // buttom[i][j]: i 반경으로 회전하는 아래쪽 배열의 값
        int left[30][55] = {0,};    // left[i][j]: i 반경으로 회전하는 왼쪽 배열의 값
        rollArray(i, top, right, buttom, left); // 회전

        DFS(depth+1);   // 다음 연산 진행

        reverseRollArray(i, top, right, buttom, left);  // 회전 복구
        visited[i] = 0; // 연산 사용 체크 해제
    }
    return;
}

void sol(){
    DFS(0);

    return;
}

void input(){
    std::cin >> N >> M >> K;
    for(int j=0; j<N; j++){
        for(int i=0; i<M; i++){
            std::cin >> A[j][i];
        }
    }
    for(int i=0; i<K; i++){
        int r, c, s;
        std::cin >> r >> c >> s;    // (1, 1) ~ (N, M) 범위를 (0, 0) ~ (N-1, M-1)로 변경
        r--;
        c--;
        roll[i] = {r, c, s};
    }

    return;
}

int main(){
    input();
    sol();
    std::cout << ans;
    
    return 0;
}