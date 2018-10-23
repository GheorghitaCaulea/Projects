function B = GramSchmidt(A)
%se aplica descopunerea Q R pentru matricea A data
  [N N] = size(A);
  [m n] = size(A);
  Q = zeros(m,n);
  Re = zeros(n);
  for j = 1 : n
    for i = 1 : j - 1
      Re(i,j) = (Q(:,i)')*A(:,j);
    endfor
    s = zeros(m,1);
    for i = 1 : j-1
      s = s + Re(i,j)*Q(:,i);
    endfor
    aux = A(:,j) - s;
    Re(j,j) = norm(aux,2);
    Q(:,j) = aux/Re(j,j);
  endfor
   I = zeros(N);
%se initializeaza o matrice unitate
   for i = 1:N
    I(i,i) = 1;
  endfor
%se aplica algoritmul de rezolvare SST pentru fiecare coloana
  for k = 1 : N
    S = Q'*I(:, k);
    w = 0;
    for i = N:-1:1
        sm = 0;
        for j = i+1 : N
          sm += Re(i,j)*w(j);
      endfor
      if Re(i, i) == 0
        w(i) = 0;
      else
        w(i) = (S(i) - sm) / Re(i,i);
      endif
    endfor
    B(1:N, k) = w;
  endfor
endfunction