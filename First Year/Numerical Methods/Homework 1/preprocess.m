function [x t] = preprocess(directory, string, count_bins)
%creez caile absolute catre cele doua directoare unde trebuie sa fac prelucrari
  dir1 = strcat(directory, 'cats/');
  dir2 = strcat(directory, 'not_cats/');
%cu ajutoul 'dir' accesez imaginile din cele doua directoare
  files1 = dir(dir1);
  files2 = dir(dir2);
  x = zeros(length(files1) + length(files2) - 4, 3 * count_bins);
%initializez matricea x
  for i = 3 : length(files1)
%plec de la 3 pentru a evita cele 2 fisiere ascunse
%initializez t cu valori diferite(1 sau -1) in functie de directorul in care ma situez
       t(i - 2) = 1;
       img1 = strcat(dir1, files1(i).name);
%creez calea catre fiecare imagine si imi completez fiecare linie din x, in functie de string
       if strcmp(string, 'RGB') == 1
        x(i - 2, 1 : 3 * (count_bins)) = rgbHistogram(img1, count_bins);
       else
        x(i - 2, 1 : 3 * (count_bins)) = hsvHistogram(img1, count_bins);
       endif
  endfor
  for i = 3 : length(files2)
       t(length(files1) + i - 4) = -1;
       img2 = strcat(dir2, files2(i).name);
       if strcmp(string, 'RGB') == 1
        x(i + length(files1) - 4, 1 : 3 * count_bins) = rgbHistogram(img2, count_bins);
       else
        x(i + length(files1) - 4, 1 : 3 * count_bins) = hsvHistogram(img2, count_bins);
       endif

       endfor
%transpun vectorul t obtinut
   t = t';
 endfunction