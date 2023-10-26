#include <iostream>
#include <vector>
#include <cmath>

struct Coordinate{	// Coordinate: 좌표
	double x, y;
};

int N;	// N: 점의 개수
std::vector<Coordinate> v;	// v[i]: 점의 좌표

double answer;

double Ccw(double x1, double x2, double x3, double y1, double y2, double y3) {	// CCW
	double res = x1 * y2 + x2 * y3 + x3 * y1;
	res += (-y1 * x2 - y2 * x3 - y3 * x1);
	return res / 2;
}

void Solution(){

	// CCW
	for(int i=1; i<N; ++i){
		answer += Ccw(v[0].x, v[i-1].x, v[i].x, v[0].y, v[i-1].y, v[i].y);
	}

	return;
}

void Input(){

	std::cin >> N;

	v.assign(N, {0, 0});

	for(int i=0; i<N; ++i) {std::cin >> v[i].x >> v[i].y;}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	std::cout << std::fixed;
	std::cout.precision(1);

	std::cout << std::abs(answer);

	return 0;
}