function [H] = rgbHistogram(image, count_bins)
%creez matricea rgb pentru imaginea trimisa ca parametru
    I = imread(image);
    [m n k] = size(I);
%descompun matricea rezultata in trei vectori corespunzatori r1, r2, r3 
    r1(1:(m*n)) = I(1:m,1:n,1);
    r2(1:(m*n)) = I(1:m,1:n,2);
    r3(1:(m*n)) = I(1:m,1:n,3);
    r(1:count_bins) = 0;
    g(1:count_bins) = 0;
    b(1:count_bins) = 0;
%imi creez o valoare 'val' egala cu lungimea intervalului histogramei
    val = double(256/count_bins);
%impart cei trei vectori la 'val', prin aproximare in lipsa
%r1, r2, r3 vor avea valori egale cu intervalul histogramei din care fac parte -1 
    r1(1:(m*n)) = idivide(r1(1:(m*n)), val, 'floor');
    r2(1:(m*n)) = idivide(r2(1:(m*n)), val, 'floor');
    r3(1:(m*n)) = idivide(r3(1:(m*n)), val, 'floor');
    for i = 0 : (count_bins - 1)
%caut intervalele in cei trei vectori, incrementand in vectorul histograma
    x = find(r1 == i);
          r(i + 1) = length(x);       
          x = find(r2 == i);
          g(i + 1) += length(x);
          x = find(r3 == i);
          b(i + 1) += length(x);
    endfor
%concatenez vectorii
    H = [r g b];
endfunction
  