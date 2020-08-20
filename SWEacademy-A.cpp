#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int draw(pair<int, int> p, int d, int** B, int N, int color) {
	int len = 0;
	int dx, dy;

	switch (d) {
	case 0:
		dx = -1; dy = 0;
		break;
	case 1:
		dx = 0; dy = 1;
		break;
	case 2:
		dx = 1; dy = 0;
		break;
	case 3:
		dx = 0; dy = -1;
		break;
	default:
		break;
	}

	if (color == 2) {
		for (int i = 1; true; i++) {
			int x = p.first + dx * i;
			int y = p.second + dy * i;

			if (B[x][y]) return 0;
			if (x == N - 1 || y == N - 1 || x == 0 || y == 0) break;
		}
	}

	for (int i = 1; true; i++) {
		int x = p.first + dx * i;
		int y = p.second + dy * i;

		B[x][y] = color;
		len++;

		if (x == N - 1 || y == N - 1 || x == 0 || y == 0) break;
	}

	return len;
}

int main() {

	int T;
	cin >> T;
	for (int test_case = 0; test_case < T; test_case++) {
		int MISSED_CORE = 12;
		int MIN_LEN = 1000;

		int N;
		cin >> N;

		vector <pair<int, int>> cores;
		vector <bool> linked;

		int** B = new int* [N];
		for (int i = 0; i < N; i++) {
			B[i] = new int[N];
			for (int j = 0; j < N; j++) {
				cin >> B[i][j];
				if (B[i][j]) {
					if (!(i == 0 || i == N - 1 || j == 0 || j == N - 1))
						cores.push_back(make_pair(i, j));
					linked.push_back(false);
				}
			}
		}

		stack <int> stk;
		stk.push(0);
		int missed_core = 0;
		int length = 0;
		int idx = 0;
		// iterate through cores
		for (auto it = cores.begin(); true;) {

			int len = draw(*it, stk.top(), B, N, 2);
			length += len;
			if (!len) missed_core++;
			else linked[idx] = true;


			// if on last core or needless to proceed
			if (missed_core > MISSED_CORE || it == cores.end() - 1) {

				// update MISSED_CORE, MIN_LEN
				if (missed_core < MISSED_CORE) {
					MISSED_CORE = missed_core;
					MIN_LEN = length;
				}
				if (missed_core == MISSED_CORE && length < MIN_LEN) MIN_LEN = length;

				// go back till stk.top() != 3;
				while (stk.top() == 3) {
					if (linked[idx]) {
						length -= draw(*it, 3, B, N, 0);
						linked[idx] = false;
					}
					else missed_core--;
					stk.pop();

					if (stk.empty()) break;
					it--;
					idx--;
				}
				if (stk.empty()) break;
				int d = stk.top();
				if (linked[idx]) {
					length -= draw(*it, d, B, N, 0);
					linked[idx] = false;
				}
				else missed_core--;

				stk.pop();
				stk.push(d + 1);

			}
			// proceed
			else {
				stk.push(0);
				it++;
				idx++;
			}
		}

		cout << '#' << test_case +1 << ' ' << MIN_LEN << endl;
	}

	return 0;
}