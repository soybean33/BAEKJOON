#include <iostream>
#include <vector>
#include <cmath>

struct Query {  // a: 1인 경우 b번째 수를 c로 바꿈, 2인 경우 b번째 수부터 c번째 수까지의 합을 구하여 출력
    int a, b;
    long long c;
};

int N, M, K;    // N: 수의 개수, M: 수의 변경이 일어나는 횟수, K: 구간의 합을 구하는 횟수
std::vector<long long> element; // element[i]: i번째로 입력 받은 수
std::vector<Query> query;   // query[i]: i 번째 명령어
std::vector<long long> segmentTree; // segmentTree[i]: i 노드의 수

long long calSumFromSegmentTree(int nodeNum, int start, int end, int left, int right) { // nodeNum: 노드 번호, start, end: 노드에 연결되어 있는 노드 번호의 범위, left, right: 합을 구하고자하는 노드 범위
    if (left > end || right < start) return 0;  // 범위에 포함되지 않는 경우 -> 합에 영향이 가지 않도록 0 반환
    if (left <= start && right >= end) return segmentTree[nodeNum]; // 범위에 포함되며 해당하는 노드인 경우 노드 번호 return

    int middle = (start + end) / 2;
    long long leftResult = calSumFromSegmentTree(nodeNum * 2, start, middle, left, right);  // 왼쪽 노드의 합
    long long rightResult = calSumFromSegmentTree(nodeNum * 2 + 1, middle + 1, end, left, right);   // 오른쪽 노드의 합

    return leftResult + rightResult;    // 양쪽 노드의 합 반환
}

void updateSegmentTree(int nodeNum, int start, int end, int idx, long long diff) {  // nodeNum: 노드 번호, start, end: 노드에 연결되어 있는 노드 번호의 범위, idx: 변경할 노드 번호, diff: 변경할 노드의 수와 변경할 수의 차이

    if (idx < start || idx > end) return;   // 변경할 노드 번호가 포함되지 않는 범위는 return

    segmentTree[nodeNum] += diff;   // 변경할 노드 번호가 포함되어 있는 범위의 노드는 갱신

    if (start != end) { // 범위에는 포함되나, 변경할 노드가 아니라면
        int middle = (start + end) / 2;
        updateSegmentTree(nodeNum * 2, start, middle, idx, diff);   // 왼쪽 갱신
        updateSegmentTree(nodeNum * 2 + 1, middle + 1, end, idx, diff); // 오른쪽 갱신
    }

    return;
}

long long makeSegmentTree(int nodeNum, int start, int end) {    // nodeNum: 노드 번호, start, end: 노드에 연결되어 있는 노드 번호의 범위

    if (start == end) { // 한 개의 노드만 남음
        segmentTree[nodeNum] = element[start];  // 노드에 원소 값 넣음
        return segmentTree[nodeNum];
    }

    int middle = (start + end) / 2; // middle: 왼쪽 노드와 오른쪽 노드의 범위를 정하기 위한 변수
    long long left = makeSegmentTree(nodeNum * 2, start, middle);   // 왼쪽 노드
    long long right = makeSegmentTree(nodeNum * 2 + 1, middle + 1, end);    // 오른쪽 노드

    segmentTree[nodeNum] = left + right;    // 왼쪽 노드와 오른쪽 노드의 합을 저장

    return segmentTree[nodeNum];
}

void sol() {

    int treeHeight = std::ceil(std::log2(N));   // treeHeight: 세그먼트 트리의 높이
    int treeSize = 1 << (treeHeight + 1);   // treeSize: 세그먼트 트리의 사이즈 -> 노드의 수
    segmentTree.assign(treeSize, 0);    // 세그먼트 트리 공간 할당

    makeSegmentTree(1, 0, N - 1);

    for (int i = 0; i < M + K; i++) {
        Query cur = query[i];   // cur: 실행할 명령

        if (cur.a == 1) {   // a가 1이면 b 번째 수를 c로 바꿈
            updateSegmentTree(1, 0, N - 1, cur.b - 1, cur.c - element[cur.b - 1]);  // 변경할 수와 현재 수와의 차이 만큼을 전달
            element[cur.b - 1] = cur.c;
        }
        else if (cur.a == 2) {  // a가 2이면 b번째 수부터 c 번째 수까지의 합을 구하여 출력
            std::cout << calSumFromSegmentTree(1, 0, N - 1, cur.b - 1, cur.c - 1) << '\n';
        }
    }

    return;
}

void input() {

    std::cin >> N >> M >> K;

    for (int i = 0; i < N; i++) {
        long long n;    // n: 입력받은 수
        std::cin >> n;
        element.push_back(n);
    }

    for (int i = 0; i < M + K; i++) {
        int a, b;   // a, b, c: 명령 입력
        long long c;
        std::cin >> a >> b >> c;
        query.push_back({ a, b, c });
    }

    return;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    input();
    sol();

    return 0;
}
