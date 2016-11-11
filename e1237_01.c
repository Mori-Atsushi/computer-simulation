/*
問1
1. そのままの場合
	O(n^2)
2. ホーナー法
	O(n)

問2
	O(n^3)
*/

#include <stdio.h>

int main(void) {
	int x, n, i, ans;

	/* 問3 (a) */
	printf("x^n\n");
	printf("x:");
	scanf("%d", &x);
	printf("n:");
	scanf("%d", &n);

	for(i = 1, ans = x; i < n; i *= 2)
		ans *= ans;

	printf("%d^%d = %d\n", x, n, ans);

	/* 問3 (b) */
	printf("\nx^4 + 2x^3 - x^2 + 3x - 1\n");
	printf("x:");
	scanf("%d", &x);

	printf("%d^4 + 2 * %d^3 - %d^2 + 3 * %d - 1 = %d\n", x, x, x, x, (((x + 2) * x - 1) * x + 3) * x - 1);

	/* 問3 (c) */
	n = 37;
	x = n + 2;
	printf("\ng(x) = ");
	for(i = 1; i <= 4; i++) {
		printf("%d", x);
		if(i != 4) {
			printf("x");
			if(i != 3)
				printf("^%d", 4 - i);
			printf(" + ");
		}
		x = x * 3 + (n + 2 - i);
	}
	printf("\nR = %d\n", x);

	return 0;
}