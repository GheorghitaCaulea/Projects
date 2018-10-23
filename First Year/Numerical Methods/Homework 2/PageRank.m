function [R1 R2 R3] = PageRank(nume, d, eps)
%se contruiesc trei vectori pe baza functiilor anterior contruite
  R1 = Iterative(nume, d, eps);
  R2 = Algebraic(nume, d);
  R3 = Power(nume, d, eps);
%se citesc datele din fisier pentru a putea accesa ultimile doua valori
  fid = fopen(nume, 'r');
  if fid > 0
    N = fscanf(fid, '%d', 1);
    A = zeros(N);
    for i = 1 : N
      lin = fscanf(fid, '%d', 1);
      nr_nod = fscanf(fid, '%d', 1);
      for j = 1 : nr_nod  
        z = fscanf(fid, '%d', 1);
        if z != lin
          A(lin, z) = 1;
        endif
      endfor
    endfor
  endif
%se citesc cele doua valori
  val1 = fscanf(fid, '%f', 1);
  val2 = fscanf(fid, '%f', 1);
  fclose(fid);
%prin concatenare se creaza numele fisierului de scriere si se deschide pentru scriere
  fis = strcat(nume, '.out');
  fid = fopen(fis, 'w');
%se scrie in fisier numarul de noduri si apoi cei trei vectori coloana
  fprintf(fid, '%d\n', N);
  for i=1:N-1
    fprintf(fid, '\n%f', R1(i));
  endfor
  fprintf(fid, '\n%f\n', R1(N));
  for i=1:N-1
    fprintf(fid, '\n%f', R2(i));
  endfor
  fprintf(fid, '\n%f\n', R2(N));
  for i=1:N-1
    fprintf(fid, '\n%f', R3(i));
  endfor
  fprintf(fid, '\n%f\n', R3(N));
  sw = 1;
%se creaza un vector de pozitii
  for i = 1:N
    poz(i) = i;
  endfor;
%se sorteaza prin metoda bulelor vectorul R2 si totodata vectorul de pozitii
  while(sw == 1)
    sw = 0;
    for i = 1:N-1
      if(R2(i) < R2(i + 1))
        aux = R2(i);
        R2(i) = R2(i + 1);
        R2(i + 1) = aux;
        aux = poz(i);
        poz(i) = poz(i + 1);
        poz(i + 1) = aux;
        sw = 1;
      endif
     endfor
  endwhile
  fprintf(fid, '\n');
%se scriu in fisier pozitiile si gradul de apartenenta obtinut
  for i = 1 : N
    fprintf(fid, '\n%d %d', i, poz(i));
    proc = Apartenenta(R2(i), val1, val2);
    fprintf(fid, ' %f\n', proc);
  endfor
  fclose(fid);
endfunction