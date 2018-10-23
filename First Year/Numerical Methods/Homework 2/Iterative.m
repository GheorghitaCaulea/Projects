function R = Iterative(nume, d, eps)
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
  R(1:N) = double(1/N);
  R = R';
  M = zeros(N);
%se contruieste matricea ajutatoare 'M'
  for i =1:N
     for j=1:N
        if A(j, i) > 0
           x = find(A(j, 1:N) == 1);  
           M(i, j) = double(1 / length(x));
        endif
     endfor
  endfor 
  aux = 0;
  unu(1, 1:N) = 1;
  unu = unu';
%se aplica algoritmul cat timp eroarea este mai mare decat o toleranta data
  while norm(R - aux) >= eps    
    aux = R;
    R = d*M*aux + double((1 - d)/N)*unu;
  endwhile
endfunction