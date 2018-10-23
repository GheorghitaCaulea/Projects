#include<stdio.h>
long sumdiv(long int x){
	int d = 1, s = 0;
	while(d <= (x / 2)) {
		if(x % d == 0){
			s = s + d;
		}
		d ++;
	}
	return s;
}
//functia calculeaza suma divizorilor unui x dat
int main(void){
	long int k, i, j;
	scanf("%ld", &k);
	for(i = 1; i <= k - 1; i ++){
		j = sumdiv(i);
		if((sumdiv(j) == i) && (i < j)){
				printf("(%ld", i);
				printf(", %ld)\n", j);
				}
	 }
	return 0;
}
// se verifica proprietatea si se afiseaza perechile	

