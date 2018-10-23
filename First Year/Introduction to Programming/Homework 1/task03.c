#include<stdio.h>
#include<math.h>
int main(void){
        unsigned long long mut, ajut1, ajut2, tab, masc1, masc2;
        int n, l;
        scanf("%Lu", &tab);
        scanf("%d", &n);
        for(l = 1; l <= n; l ++){
                scanf("%Lu", &mut);
                masc1 = pow(2, 63 - (mut & 63));
//creez un masc1, cu un sigur bit 1 pe pozitia curenta
                ajut1 = tab & masc1;
                if(ajut1 == masc1){
//se verifica daca am bit pe pozitia curenta
                        tab = tab - masc1;
			masc2 =pow(2, 63 - ((mut & 4032) / 64));
//creez masc2, cu un singur bit pe pozitia care prezinta interes
                        ajut2 = tab & masc2;
                        if(ajut2 == 0){						//virific daca am bit pe aceasta pozitie si efectuez operatiile necesare                                	
				tab = tab + masc2;
                                }
                        else{
                                tab = tab - masc2;
                        }
                }
        }
        printf("%Lu\n", tab);
        return 0;
}

