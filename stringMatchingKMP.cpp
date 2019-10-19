#include <bits/stdc++.h>
using namespace std;

const int mxsz = 1e6 + 3;
int n, m;
char s1[mxsz], s2[mxsz];
int pi[mxsz], i, k, tot;

int main(){
	scanf("%s", s1 + 1);
	scanf("%s", s2 + 1);
	n = strlen(s1 + 1); m = strlen(s2 + 1);
	pi[0] = -1;
	for (i = 1, k = -1; i <= m; i++){
		while (k >= 0 && s2[k + 1] != s2[i]) k = pi[k];
		pi[i] = ++k;
	}
	for (i = 1, k = 0; i <= n; i++){
		while (k >= 0 && s2[k + 1] != s1[i])
			k = pi[k];
		k++;
		if (k == m)tot++, k = pi[k];
	}
	printf("%d\n", tot);
	return 0;
}
