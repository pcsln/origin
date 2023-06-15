#include "Math.h"

int add(int N, int M) {
	return N + M;
}
int sub(int N, int M) {
	return N - M;
}
int mult(int N, int M) {
	return N * M;
}
double division(int N, int M) {
	return static_cast<double>(N) / static_cast<double>(M);
}
long int power(int N, int M) {
	if (M == 1) return N;
	else return N * power(N, M - 1);
}