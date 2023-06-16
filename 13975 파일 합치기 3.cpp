#include <iostream>
#include <queue>

struct Num{
	long long n;	// n: 하나의 파일로 합칠 때 필요한 비용

	bool operator < (Num next) const {
		if(n != next.n) return n > next.n;	// 오름차순 정렬

		return false; 
	}
};

int K;	// K: 소설을 구성하는 장의 수
std::priority_queue<Num> pq;	// pq: 한 파일을 만드는데 필요한 비용 오름차순 정렬
long long ans;	// ans: 모든 장을 합치는데 필요한 최소 비용

void sol(){

	ans = 0;

	while(pq.size() > 1){	// 1장 이상 남아 있을 경우

		long long a, b;	// a, b: 파일의 크기를 나타내는 양의 정수

		a = pq.top().n;	// 가장 적은 비용이 필요한 파일의 크기
		pq.pop();
		b = pq.top().n;	// 두 번째로 적은 피용이 필요한 파일의 크기
		pq.pop();

		pq.push({a + b});	// 두 페이지를 합쳐서 pq에 삽입
		ans += (a + b);
	}

	pq.pop();

	return;
}

void input(){

	std::cin >> K;

	while(!pq.empty()) pq.pop();	// pq 비우기

	for(int i=0; i<K; i++){
		int n;	// n: 파일의 크기를 나타내는 양의 정수
		std::cin >> n;
		pq.push({n});	// pq에 넣기
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int T;	// T: 테스트 케이스의 수

	std::cin >> T;

	for(int tc = 0; tc < T; tc ++){

		input();

		sol();

		std::cout << ans << '\n';
	}

	return 0;
}