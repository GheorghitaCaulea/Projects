function [w] = learn(x, t)
    [n m] = size(x);
    x_t = x;
    x_t(1:n, m + 1) = 1;
    x_tT = x_t';
%adaug o cloana de 1 in matricea x, apoi in fac transpusa
    A = x_tT * x_t;
    b = x_tT * t;
%pentru rezolvarea sistemului mut inversa inmultirii celor doua matrice in partea stanga
%il initializez pe A cu matricea rezultata prin inmultirea celor doua matrice
%il initializez pe b 
%aplic Givens pentru descompunerea Q R b
    [m n] = size(A);
    G = eye(m);
    for k = 1 : n - 1
      for l = k + 1 : m
        r = sqrt(A(k ,k)^2 + A(l ,k)^2);
        c = A(k, k) / r;
        s = -A(l, k) / r;
        t = c * A(k,k:n) - s*A(l, k:n);
        A(l, k : n) = s * A(k, k:n) + c * A(l, k:n);
        A(k, k : n) = t;
        u = c * b(k) - s * b(l);
        b(l) = s * b(k) + c * b(l);
        b(k) = u;
        t = c * G(k, 1: m) - s * G(l, 1 : m);
        G(l, 1:m) = s * G(k, 1 : m) + c * G(l, 1 : m);
        G(k, 1 : m) = t;
       endfor
     endfor
   Q = G';
   R = A;
%dupa aplicarea Givens voi avea de rezolvat un sistem superior triunghiulat
   for i = n:-1:1
      sm = 0;
      for j = i+1 : n
        sm += A(i,j)*w(j);
      endfor
      if A(i, i) == 0
        w(i) = 0;
      else
        w(i) = (b(i) - sm) / A(i,i);
      endif
    endfor
    
endfunction
     