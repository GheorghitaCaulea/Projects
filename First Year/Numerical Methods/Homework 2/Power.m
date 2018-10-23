function R = Power(nume, d, eps)
%se deschide fisierul pentru citire
  fid = fopen(nume, 'r');
  if fid > 0
%daca deschiderea reuseste se citesc datele din fisier
  N = fscanf(fid, '%d', 1);
    A = zeros(N);
    for i = 1 : N
      lin = fscanf(fid, '%d', 1);
      nr_nod = fscanf(fid, '%d', 1);
      for j = 1 : nr_nod  
        z = fscanf(fid, '%d', 1);
        if z != lin
%se contruieste matricea de adiacenta
          A(lin, z) = 1;
        endif
      endfor
    endfor
  endif
  fclose(fid);
  R(1:N) = double(1/N);
  R = R';
%se contruieste matricea ajutatoare 'M'
  M = zeros(N);
  for i =1:N
     for j=1:N
        if A(j, i) > 0
           x = find(A(j, 1:N) == 1);  
           M(i, j) = double(1 / length(x));
        endif
     endfor
  endfor 
  unu(1, 1:N) = 1;
  unu = unu';
%se creaza matricea 'E' cu elemente '1'
  E = unu*unu';
  T = d*M + double((1 - d)/N)*E;
  y = unu;
  aux = 0;
%se aplica metoda puterii directe si se contruieste vectorul PageRank
	while norm(y - aux) >= eps
    aux = y;
    z = T*y;
		y = z/norm(z);
	endwhile
  R = y;
%se normeaza vectorul
  R = double(R/norm(R, 1));
endfunction