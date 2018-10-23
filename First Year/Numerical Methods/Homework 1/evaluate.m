function [proc] = evaluate(directory, z, string, count_bins)
%creez caile absolute catre cele doua directoare si cu 'dir' accesez imaginile
  dir1 = strcat(directory, 'cats/');
  dir2 = strcat(directory, 'not_cats/');
  files1 = dir(dir1);
  files2 = dir(dir2);
  nr_cats = 0;
  nr_ncats = 0;
%transpun vectorul learn si initializez un vector de lungime 3 * count_bins + 1, cu valoarea 1 pe ultima pozitie
  w = z';
  x = zeros(1, 3 * count_bins + 1);
  x(3 * count_bins + 1) = 1;
%accesez fiecare director
%pentru fiecare imagine creez un nou vector x
%verific conditia data si incrementez nr_cats sau nr_ncats daca e cazul
  for i = 3 : length(files1)
       img1 = strcat(dir1, files1(i).name);
       if strcmp(string, 'RGB') == 1
          x(1, 1 : 3 * (count_bins)) = rgbHistogram(img1, count_bins);
        if x * w >= 0
           nr_cats += 1;
        endif
       else
        x(1, 1 : 3 * (count_bins)) = hsvHistogram(img1, count_bins);
        if x * w >= 0
           nr_cats += 1;
        endif
       endif
  endfor
  for i = 3 : length(files2)
       img2 = strcat(dir2, files2(i).name);
       if strcmp(string, 'RGB') == 1
        x(1, 1 : 3 * count_bins) = rgbHistogram(img2, count_bins);
        if x * w < 0
           nr_ncats += 1;
        endif
       else
        x(1, 1 : 3 * count_bins) = hsvHistogram(img2, count_bins);
        if x * w < 0
           nr_ncats += 1;
        endif
       endif
  endfor
%calculez procentajul obtinut
  proc = 100 * (nr_cats + nr_ncats) / (length(files1) + length(files2) - 4);
endfunction