#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

struct Water{	// 통의 부피와, 통에 있는 물의 부피
	int A, B, C;
};

Water water;	// water: 물통의 부피

std::vector<int> answers;	// answers: 세 번째 물통에 담겨있을 수 있는 물의 양

void Solution(){

	std::queue<Water> q;	// q: 각 물통의 물의 양
	q.push({0, 0, water.C});	// 초기에는 세 번째 물통에 물이 가득 차 있음

	std::vector<std::vector<std::vector<bool>>> visited;	// visited[i][j][k]: 각 물통에 i, j, k 리터의 물이 있었던 적이 있으면 continue
	visited.assign(201, std::vector<std::vector<bool>>(201, std::vector<bool>(201, false)));	// 초기값 false

	while(!q.empty()){
		Water curr = q.front();	// curr: 현재 물통의 정보
		q.pop();

		if(visited[curr.A][curr.B][curr.C] == true) {continue;}	// 현재 상태인 적이 있었다면 continue
		visited[curr.A][curr.B][curr.C] = true;	// 방문 체크

		if(curr.A == 0) {answers.push_back(curr.C);}	//	첫 번째 물통이 비어 있을 때

		// A -> B
		if(curr.A + curr.B > water.B) {
			Water next = {curr.A + curr.B - water.B, water.B, curr.C};
			q.push(next);
		}
		else{
			Water next = {0, curr.A + curr.B, curr.C};
			q.push(next);
		}

		// A -> C
		if(curr.A + curr.C > water.C) {
			Water next = {curr.A + curr.C - water.C, curr.B, water.C};
			q.push(next);
		}
		else{
			Water next = {0, curr.B, curr.A + curr.C};
			q.push(next);
		}

		// B -> A
		if(curr.B + curr.A > water.A) {
			Water next = {water.A, curr.B + curr.A - water.A, curr.C};
			q.push(next);
		}
		else{
			Water next = {curr.B + curr.A, 0, curr.C};
			q.push(next);
		}

		// B -> C
		if(curr.B + curr.C > water.C) {
			Water next = {curr.A, curr.B + curr.C - water.C, water.C};
			q.push(next);
		}
		else{
			Water next = {curr.A, 0, curr.B + curr.C};
			q.push(next);
		}

		// C -> A
		if(curr.C + curr.A > water.A) {
			Water next = {water.A, curr.B, curr.C + curr.A - water.A};
			q.push(next);
		}
		else{
			Water next = {curr.C + curr.A, curr.B, 0};
			q.push(next);
		}

		// C -> B
		if(curr.C + curr.B > water.B) {
			Water next = {curr.A, water.B, curr.C + curr.B - water.B};
			q.push(water);
		}
		else{
			Water next = {curr.A, curr.B + curr.C, 0};
			q.push(water);
		}
	}

	std::sort(answers.begin(), answers.end());

	return;
}

void Input(){

	std::cin >> water.A >> water.B >> water.C;

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	for(const int& answer : answers) {std::cout << answer << ' ';}

	return 0;
}