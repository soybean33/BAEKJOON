#include <iostream>
#include <vector>
#include <algorithm>

constexpr int INF = 10e8;	// INF: 나올 수 없는 값

int N;	// N: 회원의 수
std::vector<std::vector<int>> arr;	// arr[i][j]: i 회원과 j 회원의 점수

int answerDist = INF;	// answerDist: 회장 후부의 점수
std::vector<int> answers;	// answers[i]: 회장 후보 오름차순

void Solution(){

	// 플로이드-워셜
	for(int t=0; t<N; ++t){
		for(int i=0; i<N; ++i){
			for(int j=0; j<N; ++j){
				arr[i][j] = std::min(arr[i][j], arr[i][t] + arr[t][j]);
			}
		}
	}

	for(int i=0; i<N; ++i){
		int tmp = 0;	// tmp: 점수 계산
		for(int j=0; j<N; ++j) {tmp = std::max(tmp, arr[i][j]);}

		if(tmp < answerDist) {	// 더 높은 회장 점수가 발견된다면
			answers.clear();	// 지금까지의 회장 후보를 모두 버리고
			answerDist = tmp;	// 점수를 갱신한 다음
			answers.push_back(i);	// 회장 후보 등록
		}
		else if(tmp == answerDist) {answers.push_back(i);}	// 점수가 같으면 회장 후보
	}

	std::sort(answers.begin(), answers.end());	// 오름차순 정렬

	return;
}

void Input(){

	std::cin >> N;

	arr.assign(N, std::vector<int>(N, INF));

	for(int i=0; i<N; ++i){
		for(int j=0; j<N; ++j){
			if(i==j) {arr[i][j] = 0;}	// 같은 사람의 거리는 0
		}
	}

	while(true){
		int a, b;
		std::cin >> a >> b;
		if(a == -1 && b == -1) {break;}	// -1 -1 이 들어오면 종료

		arr[a-1][b-1] = 1;
		arr[b-1][a-1] = 1;
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	std::cout << answerDist << ' ' << answers.size() << '\n';
	for(const int& answer : answers) {std::cout << answer + 1 << ' ';}

	return 0;
}