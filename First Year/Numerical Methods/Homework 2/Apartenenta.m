function y = Apartenenta(x, val1, val2)
%se calculeaza cele doua valori, a si b
  a = double(1 / (val2 - val1));
  b = double(val1 / (val1 - val2));
%in functie de intervalul lui x se calculeaza gradul de apartenta
  if(x < val1)
    y = 0;
  else  
    if(x >=val1 && x <= val2)
      y = x*a + b;
    else  
      y = 1;
    endif
  endif
endfunction
        