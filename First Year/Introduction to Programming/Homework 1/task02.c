#include<stdio.h>
#include<math.h>
int pal(int x){
	int z, y;
	z = 0;
	y = x;
	while(x > 0){
		z = (z * 10) + (x % 10);
		x = x / 10;
	}
	if(y == z){
		return 1;
	} else {
		return 0;
	}
}
//funtia verifica proprietatea de palindrom a unui x dat
int nrcif( long int q){
	if(q == 0){
		return 0;
	}
	else{
		return 1 + nrcif(q / 10);
	}
}
//functia returneaza numarul de cifre a unui q dat
int main(void){
	long int i, k, f;
	int t, g;
	g = 0;
	scanf("%d %ld", &t, &f);
	for(k = 1; k <= (f - 1); k++){
		if(pal(k) == 1){
			i = pow(10, t - 1);
			while(i < pow(10, t)){
				if((k % i == 0) && (nrcif(k / i) == t) && (k / i != i)){
					g ++;
					break;
				}
				i++;
			}
		}	
	}	
	if(t == 1){
		g ++;
	}
	printf("%d\n", g);
	return 0;
} 
//se merge pe interval si se verica proprietatea, dupa care se pun conditiile pe impartitor si cat		 	
