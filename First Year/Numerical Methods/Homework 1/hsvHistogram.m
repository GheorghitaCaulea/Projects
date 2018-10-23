function [V] = hsvHistogram(image, count_bins)
%creez matricea rgb pentru imaginea trimisa ca parametru
   I = imread(image);
   [m n k] = size(I);
   I = double(I);
   h(1:(m*n)) = 0;
   s(1:(m*n)) = 0;
   v(1:(m*n)) = 0;
%descompun matricea rezultata in trei vectori corespunzatori r, g, b 
   r(1:(m*n)) = I(1:m,1:n,1);
   g(1:(m*n)) = I(1:m,1:n,2);
   b(1:(m*n)) = I(1:m,1:n,3);
%impart fiecare valoare din vector la 255
   r(1:(m*n)) = r(1:(m*n))/255;
   g(1:(m*n)) = g(1:(m*n))/255;
   b(1:(m*n)) = b(1:(m*n))/255;
%aplic algoritmul ce conversie 
%creez trei vectori cu specificatiile cerute:cmax, cmin, delta
   cmax = max(r, g);
   cmax = max(cmax, b);
   cmin = min(r, g);
   cmin = min(cmin, b);
   delta = cmax - cmin;
   deltacp = delta;
%fac o copie a vectorului delta, deltacp
%caut indicii valorilor nule in delta si le modific, pentru a evita erorile la impartirea cu 0;
   [ix] = find(delta == 0);
   delta(ix) = 1;
%aplic algoritmul de conversie cautand de fiecare data indicii valorilor care satisfac conditia
   [ix] = find(cmax == r);   
   h(ix) = 60 * mod((g(ix) - b(ix)) ./ delta(ix), 6);
   [ix] = find(cmax == g);
   h(ix) = 60 * ((b(ix) - r(ix)) ./ delta(ix) + 2);        
   [ix] = find(cmax == b);
   h(ix) = 60 * ((r(ix) - g(ix)) ./ delta(ix) + 4);
   [ix] = find(deltacp == 0);
   h(ix) = 0;
   h = h / 360;
   [ix] = find(cmax == 0);
   s(ix) = 0;
   [ix] = find(cmax > 0);
   s(ix) = deltacp(ix) ./ cmax(ix);
   v = cmax;
   h1(1:count_bins) = 0;
   s1(1:count_bins) = 0;
   v1(1:count_bins) = 0;
   val2 = 101/count_bins;
   h = h * 100;
   s = s * 100;
   v = v * 100;
%creez cei trei vectori h, s, v pe care ii impart la 'val', pentru a-mi da indicele unde trebuie sa incrementez in vectorul histograma
   h(1:(m*n)) = idivide(h(1:(m*n)), val2, 'floor');
   s(1:(m*n)) = idivide(s(1:(m*n)), val2, 'floor');
   v(1:(m*n)) = idivide(v(1:(m*n)), val2, 'floor');
   for i = 0 : (count_bins - 1)
          x = find(h == i);
          h1(i + 1) += length(x);       
          x = find(s == i);
          s1(i + 1) += length(x);
          x = find(v == i);
          v1(i + 1) += length(x);
    endfor
%concatenez vectorii
    V = [h1 s1 v1];
endfunction