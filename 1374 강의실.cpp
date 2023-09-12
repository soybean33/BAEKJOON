#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Lecture {
	int lectureNum;	// lectureNum: 강의 번호 -> 1<=N<=1e8
	int startTime;	// startTime: 강의 시작 시간 -> 0<=startTime<=1e9
	int endTime;	// endTime: 강의 종료 시간 -> 0<=endTime<=1e9
};

bool Cmp(const Lecture& left, const Lecture& right) {	// 강의 시간 오름차순 정렬

	if (left.startTime != right.startTime) { return left.startTime < right.startTime; }	// 강의 시작 시간 오름차순 정렬
	if (left.endTime != right.endTime) { return left.endTime < right.endTime; }	// 강의 종료 시간 오름차순 정렬

	return false;
}

int Solution(const int& N, std::vector<Lecture>& v) {

	int answer = 1;	// answer: 필요한 최소 강의실 개수
	std::priority_queue<int, std::vector<int>, std::greater<int>> pq;	// pq: 진행 중인 강의를 넣는 우선순위 큐 -> 오름차순정렬

	std::sort(v.begin(), v.end(), Cmp);

	for (const Lecture& lecture : v) {	// lecture: 시작하고자 하는 가의 정보
	
		if (pq.empty()) { pq.push(lecture.endTime); }	// 진행 중인 강의가 없는 경우 우선순위큐에 넣음
		else {
			if (pq.top() > lecture.startTime) { ++answer; }	// 가장 빨리 종료되는 강의보다 더 빨리 시작하는 강의의 경우 강의실을 늘림
			else {
				pq.pop();	// 강의실을 비워줄 수 있음
			}
			pq.push(lecture.endTime);	// 강의 넣음
		}	
	}

	return answer;
}

void Input(int& N, std::vector<Lecture>& v) {

	std::cin >> N;

	v.assign(N, { 0, 0, 0 });

	for (int i = 0; i < N; ++i) {
		std::cin >> v[i].lectureNum >> v[i].startTime >> v[i].endTime;
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;	// N: 강의실의 개수 1<=N<=100'000
	std::vector<Lecture> v;	// v[i]: i 번째로 입력된 강의

	Input(N, v);

	std::cout << Solution(N, v);

	return 0;
}