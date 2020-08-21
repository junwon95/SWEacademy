/*
0~3, 4~7, 8~9 
두번의 query로 구간 설정.
구간의 공 개수를 만족하는 가능한 모든 조합을 P에 저장
Query마다 P에서 제하며 
ball + strike = 4 인 조합 찾기
해당 조합을 찾으면 모든 경우에 대하여 하드코딩된 combinate() 함수로 정답 찾음.
*/


#define N 4



typedef struct {

    int strike;

    int ball;

} Result;



// API

extern Result query(int guess[]);

Result Query(int a, int b, int c, int d, int guess[]) {
	guess[0] = a;
	guess[1] = b;
	guess[2] = c;
	guess[3] = d;
	return query(guess);
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}


// -----------------------------------------------------------
void combinate(int guess[], Result result) {
	int n1 = guess[0], n2 = guess[1], n3 = guess[2], n4 = guess[3];
	Result r = result;
	if (r.ball == 4) {
		swap(&n1, &n2);
		swap(&n3, &n4);
		r = Query(n1, n2, n3, n4, guess);
		// SSSS
		if (r.strike == 4) return;
		// BBBB
		else if (r.strike == 0) {
			swap(&n1, &n3);
			swap(&n2, &n4);
			r = Query(n1, n2, n3, n4, guess);
			// SSSS
			if (r.strike == 4) return;
			// BBBB
			else if (r.strike == 0) {
				swap(&guess[0], &guess[1]);
				swap(&guess[2], &guess[3]);
				return;
			}
			// SSBB BBSS
			else {
				swap(&n1, &n2);
				r = Query(n1, n2, n3, n4, guess);
				// SSSS
				if (r.strike == 4) return;
				else {
					swap(&guess[0], &guess[1]);
					swap(&guess[2], &guess[3]);
					return;
				}
			}
		}
		// BSBS BSSB SBSB SBBS
		else if (r.strike == 2) {
			swap(&n2, &n3);
			r = Query(n1, n2, n3, n4, guess);
			if (r.strike == 4) return;
			else if (r.strike == 0) {
				swap(&guess[1], &guess[2]);
				swap(&guess[0], &guess[3]);
				return;
			}
			// BBBS SBBB
			else {
				swap(&n2, &n3);
				swap(&n1, &n3);
				r = Query(n1, n2, n3, n4, guess);
				if (r.strike == 4) return;
				else {
					swap(&guess[0], &guess[2]);
					swap(&guess[1], &guess[3]);
					return;
				}
			}
		}
	}
	else if (r.strike == 1) {
		swap(&n2, &n3);
		r = Query(n1, n2, n3, n4, guess);
		if (r.strike == 2) {
			swap(&n3, &n4);
			r = Query(n1, n2, n3, n4, guess);
			if (r.strike == 4) return;
			else if(r.strike == 0){
				swap(&guess[0], &guess[1]);
				swap(&guess[2], &guess[3]);
				return;
			}
			else {
				swap(&n3, &n4);
				swap(&n2, &n4);
				r = Query(n1, n2, n3, n4, guess);
				if (r.strike == 4) return;
				else {
					swap(&guess[0], &guess[2]);
					swap(&guess[1], &guess[3]);
					return;
				}
			}
		}
		// 3421 4123 2341 4312
		else {
			swap(&n1, &n2);
			r = Query(n1, n2, n3, n4, guess);
			// 1423 3241
			if (r.strike == 1) {
				swap(&n2, &n3);
				swap(&n3, &n4);
				r = Query(n1, n2, n3, n4, guess);
				if (r.strike == 4) return;
				else {
					swap(&guess[0], &guess[2]);
					swap(&guess[1], &guess[3]);
					return;
				}

			}
			// 4321 3412
			else {
				swap(&n1, &n3);
				swap(&n2, &n4);
				r = Query(n1, n2, n3, n4, guess);
				if (r.strike == 4) return;
				else {
					swap(&guess[0], &guess[1]);
					swap(&guess[2], &guess[3]);
					return;
				}
			}
		}

	}
	else if (r.strike == 2) {
		swap(&n1, &n2);
		r = Query(n1, n2, n3, n4, guess);
		if (r.strike == 4) return;
		else if (r.ball == 4) {
			swap(&guess[0], &guess[1]);
			swap(&guess[2], &guess[3]);
			return;
		}
		swap(&n1, &n2);
		swap(&n2, &n3);
		r = Query(n1, n2, n3, n4, guess);
		if (r.strike == 4) return;
		else if (r.ball == 4) {
			swap(&guess[1], &guess[2]);
			swap(&guess[0], &guess[3]);
			return;
		}
		swap(&n2, &n3);
		swap(&n1, &n3);
		r = Query(n1, n2, n3, n4, guess);
		if (r.strike == 4) return;
		else if (r.ball == 4) {
			swap(&guess[0], &guess[2]);
			swap(&guess[1], &guess[3]);
			return;
		}
	}
}
// -----------------------------------------------------------



bool validate(int p[], int A, int B, int C) {
	for (int i = 0; i < 4; i++) {
		if (p[i] < 4) A--;
		else if (p[i] < 8) B--;
		else C--;
	}
	return (A == 0 && B == 0 && C == 0);
}

bool filter(int p[], int ball, int guess[]) {
	for(int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (guess[i] == p[j]) ball--;
		}
	return (ball == 0);
}


void doUserImplementation(int guess[]) {

	bool possible[210];
	int P[210][4];

	int idx = 0;
	for (int i = 0; i < 7; i++)
		for (int j = i + 1; j < 8; j++)
			for (int k = j + 1; k < 9; k++)
				for (int l = k + 1; l < 10; l++) {
					P[idx][0] = i;
					P[idx][1] = j;
					P[idx][2] = k;
					P[idx][3] = l;
					idx++;
				}

	
	Result sectionA;
	Result sectionB;
	int A,B,C;

	sectionA = Query(0, 1, 2, 3, guess);
	A = sectionA.ball + sectionA.strike;
	if (A == 4) {
		// combination sectionA
		return combinate(guess, sectionA);
	}

	sectionB = Query(4, 5, 6, 7, guess);
	B = sectionB.ball + sectionB.strike;
	if (B == 4) {
		// combination sectionB
		return combinate(guess, sectionB);
	}

	C = 4 - A - B;
	
	for (int i = 0; i < 210; i++) {
		possible[i] = validate(P[i], A, B, C);
	}


	Result r;
	while (true) {
		for (int i = 0; i < 210; i++) {
			if (possible[i]) {
				r = Query(P[i][0], P[i][1], P[i][2], P[i][3], guess);
				if (r.ball + r.strike == 4) {
					return combinate(guess, r);
				}
				else {
					possible[i] = false;
				}
				break;
			}
		}
		for (int i = 0; i < 210; i++) {
			if(possible[i])
				possible[i] = filter(P[i], r.ball + r.strike, guess);
		}
	}
	
}
