function R = Algebraic(nume, d)
%se deschide fisierul pentru citire
  fid = fopen(nume, 'r');
  if fid > 0
%daca deschiderea fisierului reuseste, se citesc datele de intrare
  N = fscanf(fid, '%d', 1);
    A = zeros(N);
    for i = 1 : N
      lin = fscanf(fid, '%d', 1);
      nr_nod = fscanf(fid, '%d', 1);
      for j = 1 : nr_nod  
        z = fscanf(fid, '%d', 1);
        if z != lin
%se construieste matricea de adiacenta
          A(lin, z) = 1;
        endif
      endfor
    endfor
  endif
  fclose(fid);
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
%se contruieste matricea unitate
  I = zeros(N);
  for i = 1:N
    I(i,i) = 1;
%se aplica functia GramSchmidt pe matricea creata conform cerintei
  endfor
  T = I - d*M;
  R = GramSchmidt(T);
%se calculeaza vectorul PageRank
  unu(1, 1:N) = 1;
  R = R*double((1 - d)/N)*unu';
  endfunction