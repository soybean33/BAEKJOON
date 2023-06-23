#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Class{	// 수업의 시작 시간과 끝나는 시간
	int start, end;	// start, end: 시작 시간과 끝나는 시간
};

int N;	// N: 수업의 갯수
std::vector<Class> v;	// v[i]: 시작 시간을 기준으로 오름차순 정렬한 i 번째 수업 시간
int ans;	// ans: 강의실의 개수

struct Cmp{
	bool operator () (Class left, Class right) const{	// pq[i]: 끝나는 시간을 기준으로 오름차순 정렬한 i 번째 수업 시간
		if(left.end != right.end) return left.end > right.end;

		return false;
	}
};

bool cmp(Class left, Class right){
	if(left.start != right.start) return left.start < right.start;	// 시작 시간을 기준으로 오름차순 정렬

	return false;
}

void solution(){

	std::sort(v.begin(), v.end(), cmp);	// 시작 시간을 기준으로 오름차순 정렬 -> 빨리 시작하는 수업부터 pq에 넣음

	std::priority_queue<Class, std::vector<Class>, Cmp> pq;	// 끝나는 시간을 기준으로 오름차순 정렬

	pq.push(v[0]);	// 강의 한 개 넣고 시작 -> 강의실 1개는 무조건 필요

	for(int i=1; i<N; i++){
		if(pq.top().end <= v[i].start){	// 강의실을 추가할 필요 없음
			pq.pop();	// 강의실 줄이기
			pq.push(v[i]);	// 강의실 추가하기
		}
		else pq.push(v[i]);	// 강의실 추가
	}

	ans = pq.size();	// pq의 크기는 강의실의 크기

	return;
}

void input(){

	std::cin >> N;

	v.resize(N);

	for(int i=0; i<N; i++) {
		int start, end;	// start, end: 수업 시작 시간과 끝나는 시간
		std::cin >> start >> end;
		v[i] = {start, end};
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	std::cout << ans;

	return 0;
}