#include <iostream>
#include <queue>
#include <algorithm>

struct Positive{	// 1보다 큰 양수 내림차순
	int n;

	bool operator < (Positive next) const{
		if(n != next.n) return n < next.n;

		return false;
	}
};

struct Negative{	// 음수 오름차순
	int n;

	bool operator < (Negative next) const{
		if(n != next.n) return n > next.n;

		return false;
	}
};

int N;	// N: 수열의 크기
int oneCnt, zeroCnt;	// oneCnt: 1의 개수, zeroCnt: 0의 개수
std::priority_queue<Positive> positive;	// 1보다 큰 양수 내림차순 우선 순위 큐
std::priority_queue<Negative> negative;	// 음수 오름차순 우선 순위 큐
int ans;

void sol(){

	ans += oneCnt;	// 1은 곱하지 않고 모두 더함

	while(positive.size() > 1){	// 1보다 큰 양수가 1개 보다 많을 경우
		int a = positive.top().n;	// a: 곱할 첫 번째 1보다 큰 양수
		positive.pop();

		int b = positive.top().n;	// b: 곱할 두 번째 1보다 큰 양수
		positive.pop();

		ans += a * b;	// 곱해서 더함
	}

	if(positive.size()){	// 1보다 큰 양수가 1개 남아있을 경우
		int a = positive.top().n;	// a: 남아있는 야수
		positive.pop();

		ans += a;	// 더함
	}

	while(negative.size() > 1){	// 음수가 1개 보다 많은 경우
		int a = negative.top().n;	// a: 곱할 첫 번째 음수
		negative.pop();

		int b = negative.top().n;	// b: 곱할 두 번째 음수
		negative.pop();

		ans += a * b;	// 곱해서 더함
	}

	if(negative.size()){	// 음수가 남아 있는 경우
		if(!zeroCnt){	// 0이 없는 경우 -> 0이 있는 경우 0을 곱함
			ans += negative.top().n;	// 더함
			negative.pop();
		} 
	}

	return;
}

void input(){

	std::cin >> N;

	for(int i=0; i<N; i++){
		int n;	// n: 수열의 수
		std::cin >> n;
		if(n == 0) zeroCnt++;	// 0 인 경우
		else if(n==1) oneCnt++;	// 1 인 경우
		else if(n>1) positive.push({n});	// 1보다 큰 양수의 경우
		else if(n < 0) negative.push({n});	// 음수의 경우
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	std::cout << ans;

	return 0;
}