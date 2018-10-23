valnum(X):- char_type(X, alnum), char_type(X, ascii).
vother(X):- member(X, [';','<','+','-','*','(',')','{','}']).
validc(X):- valnum(X) ; vother(X) ;  X == '='.

lparseq(['='|L],'==',L).
lparseq([X|L],'=',[X|L]):-dif(X,'=').
lparseq([],'=',[]).

lparsealn([X|L],L2,R,L3):- valnum(X), lparsealn(L, [X|L2], R, L3).
lparsealn([X|L],L2,R,[X|L]):- \+valnum(X), reverse(L2, L3), atom_chars(R, L3).
lparsealn([],L2,R,[]):- reverse(L2, L3), atom_chars(R, L3).

lparse2(['='|L],L2,L3):- lparseq(L,R,L4), lparse2(L4,[R|L2],L3).
lparse2([X|L],L2,L3):- valnum(X),lparsealn(L,[X],R,L4), lparse2(L4,[R|L2],L3).
lparse2([X|L],L2,L3):- vother(X), lparse2(L,[X|L2],L3).
lparse2([X|L],L2,L3):- \+validc(X), lparse2(L,L2,L3).
lparse2([],L2,L3):- reverse(L2,L3).

lparse(S, L):- atom_chars(S, L2), lparse2(L2,[],L),!.

parse_alpha([H|T], H, T) :- char_type(H, alpha).
parse_int([H|T], H, T) :- char_type(H, digit).

star(_, L, [], L).
star(P, L, [F|FR], RF) :- call(P, L, F, R), star(P, R, FR, RF), !.

plus(P, L, [F|FR], RF) :- call(P, L, F, R), star(P, R, FR, RF), !.

parse_var([], _, []).
parse_var(L, O, R) :- plus(parse_alpha, L, Op, R), atomic_list_concat(Op, O).
parse_val(L, N, R) :- plus(parse_int, L, Op, R), atomic_list_concat(Op, O), atom_number(O, N).

parse_tok([], _, []).
parse_tok([H | L], symbol(O), L) :- atom_chars(H, Lc), parse_var(Lc, O, []), !. 
parse_tok([H1 | L], value(O), L) :- atom_number(H1, H), number_chars(H, Lc), parse_val(Lc, O, []), !. 

parse_mult_expr(L, mult(X, Y), R) :- parse_tok(L, X, R1), parse_char('*', R1, _, R2), parse_mult_expr(R2, Y, R), !.
parse_mult_expr(L, O, R) :- parse_tok(L, O, R).

parse_add_expr(L, add(X, Y), R, S) :- S = 0, parse_mult_expr(L, X, R1), parse_char('+', R1, _, R2), parse_add_expr(R2, Y, R, 0), !.
parse_add_expr(L, sub(X, Y), R, S) :- S = 1, parse_mult_expr(L, X, R1), parse_char('+', R1, _, R2), parse_add_expr(R2, Y, R, 0), !.
parse_add_expr(L, sub(X, Y), R, S) :- S = 0, parse_mult_expr(L, X, R1), parse_char('-', R1, _, R2), parse_add_expr(R2, Y, R, 1), !.
parse_add_expr(L, add(X, Y), R, S) :- S = 1, parse_mult_expr(L, X, R1), parse_char('-', R1, _, R2), parse_add_expr(R2, Y, R, 1), !.
parse_add_expr(L, O, R, _) :- parse_mult_expr(L, O, R).

parse_smaller_expr(L, smaller(X, Y), R) :- parse_add_expr(L, X, R1, 0), parse_char('<', R1, _, R2), parse_smaller_expr(R2, Y, R), !.
parse_smaller_expr(L, O, R) :- parse_add_expr(L, O, R, 0).

parse_equal_expr(L, equal(X, Y), R) :- parse_smaller_expr(L, X, R1), parse_char('==', R1, _, R2), parse_equal_expr(R2, Y, R), !.
parse_equal_expr(L, O, R) :- parse_smaller_expr(L, O, R).

parse_expr(I, O) :- parse_equal_expr(I, O, []).

parse_char(C, [C|T], C, T).

get_expr(L, [], R) :- parse_char(';', L, _, R), !.
get_expr([H|L], [H|T], R) :- get_expr(L, T, R), !.

get_expr_if(L, [], R) :- parse_char(')', L, _, R), !.
get_expr_if([H|L], [H|T], R) :- get_expr_if(L, T, R), !.

get_prog(L, [], R, C) :- C = 0, parse_char('}', L, _, R), !.
get_prog([H|L], [H|T], R, C) :- H = '{', C1 is C + 1, get_prog(L, T, R, C1),  !.
get_prog([H|L], [H|T], R, C) :- H = '}', C1 is C - 1, get_prog(L, T, R, C1), !.
get_prog([H|L], [H|T], R, C) :- get_prog(L, T, R, C), !.

parse_return(L, return(Rex1), R) :- parse_char(return, L, _, Re), get_expr(Re, Rex, R), parse_expr(Rex, Rex1), !.

parse_assert(L, assert(Rex1), R) :- parse_char(assert, L, _, R1), parse_char('(', R1, _, R2),
                                    get_expr_if(R2, Rex, R3), parse_expr(Rex, Rex1), parse_char(';', R3, _, R), !.

parse_assign_for(L, assign(X, Y), R) :- parse_tok(L, X, R1), parse_char('=', R1, _, R2), 
                                    get_expr_if(R2, Rex, R), parse_expr(Rex, Y), !.


parse_for(L, for(A1, E, A2, P), R) :- parse_char(for, L, _, R1), parse_char('(', R1, _, R2), parse_assign(R2, A1, R3), 
                                      get_expr(R3, Rex, R4), parse_expr(Rex, E), parse_assign_for(R4, A2, R5),
                                      parse_char('{', R5, _, R6), get_prog(R6, Prg, R, 0), parse_all_prog(Prg, P), !.


parse_if(L, if(E, P1, P2), R) :- parse_char(if, L, _, R1), parse_char('(', R1, _, R2), get_expr_if(R2, Rex, R4), parse_expr(Rex, E), 
                                 parse_char(then, R4, _, R5), parse_char('{', R5, _, R6), get_prog(R6, Prg1, R7, 0), parse_all_prog(Prg1, P1),
                                 parse_char(else, R7, _, R8), parse_char('{', R8, _, R9), get_prog(R9, Prg2, R, 0), parse_all_prog(Prg2, P2), !.

parse_assign(L, assign(X, Y), R) :- parse_tok(L, X, R1), parse_char('=', R1, _, R2), 
                                    get_expr(R2, Rex, R), parse_expr(Rex, Y), !.

parse_semcol(L, semcol, R) :- parse_char(';', L, _, R).                                   

parse_prog(L, P, R) :- parse_assign(L, P, R).
parse_prog(L, P, R) :- parse_assert(L, P, R).
parse_prog(L, P, R) :- parse_return(L, P, R).
parse_prog(L, P, R) :- parse_if(L, P, R).
parse_prog(L, P, R) :- parse_for(L, P, R).
parse_prog(L, P, R) :- parse_semcol(L, P, R).

parse_all_prog(L, [X | P]) :- parse_prog(L, X, R1), parse_all_prog(R1, P), !.
parse_all_prog([], []).

search(_, [], _, 3).
search(symbol(X), [[N, _] | L], R, E) :- N \= symbol(X), search(symbol(X), L, R, E), !.
search(symbol(X), [[N, V] | _], R, 0) :- N = symbol(X), R is V, !.

eval_expr(value(X), X, 0, _).

eval_expr(symbol(X), R, E, D) :- search(symbol(X), D, R, E), !.

eval_expr(mult(X, Y), R, 0, D) :- eval_expr(X, R1, E1, D), eval_expr(Y, R2, E2, D), E1 = 0, E2 = 0, R is R1 * R2, !.
eval_expr(mult(X, Y), _, E, D) :- eval_expr(X, _, E1, D), eval_expr(Y, _, _, D), E1 \= 0, E is E1, !.
eval_expr(mult(X, Y), _, E, D) :- eval_expr(X, _, _, D), eval_expr(Y, _, E2, D), E2 \= 0, E is E2, !.

eval_expr(add(X, Y), R, 0, D) :- eval_expr(X, R1, E1, D), eval_expr(Y, R2, E2, D), E1 = 0, E2 = 0, R is R1 + R2, !.
eval_expr(add(X, Y), _, E, D) :- eval_expr(X, _, E1, D), eval_expr(Y, _, _, D), E1 \= 0, E is E1, !.
eval_expr(add(X, Y), _, E, D) :- eval_expr(X, _, _, D), eval_expr(Y, _, E2, D), E2 \= 0, E is E2, !.

eval_expr(sub(X, Y), R, 0, D) :- eval_expr(X, R1, E1, D), eval_expr(Y, R2, E2, D), E1 = 0, E2 = 0, R is (R1 - R2), !.
eval_expr(sub(X, Y), _, E, D) :- eval_expr(X, _, E1, D), eval_expr(Y, _, _, D), E1 \= 0, E is E1, !.
eval_expr(sub(X, Y), _, E, D) :- eval_expr(X, _, _, D), eval_expr(Y, _, E2, D), E2 \= 0, E is E2, !.

eval_expr(smaller(X, Y), R, 0, D) :- eval_expr(X, R1, E1, D), eval_expr(Y, R2, E2, D), E1 = 0, E2 = 0, R1 < R2, R is 1, !.
eval_expr(smaller(X, Y), R, 0, D) :- eval_expr(X, _, E1, D), eval_expr(Y, _, E2, D), E1 = 0, E2 = 0, R is 0, !.
eval_expr(smaller(X, Y), _, E, D) :- eval_expr(X, _, E1, D), eval_expr(Y, _, _, D), E1 \= 0, E is E1, !.
eval_expr(smaller(X, Y), _, E, D) :- eval_expr(X, _, _, D), eval_expr(Y, _, E2, D), E2 \= 0, E is E2, !.

eval_expr(equal(X, Y), R, 0, D) :- eval_expr(X, R1, E1, D), eval_expr(Y, R2, E2, D), E1 = 0, E2 = 0, R1 = R2, R is 1, !.
eval_expr(equal(X, Y), R, 0, D) :- eval_expr(X, R1, E1, D), eval_expr(Y, R2, E2, D), E1 = 0, E2 = 0, R1 \= R2, R is 0, !.
eval_expr(equal(X, Y), _, E, D) :- eval_expr(X, _, E1, D), eval_expr(Y, _, _, D), E1 \= 0, E is E1, !.
eval_expr(equal(X, Y), _, E, D) :- eval_expr(X, _, _, D), eval_expr(Y, _, E2, D), E2 \= 0, E is E2, !.

eval_prog(assign(X, Y), _, E, D1, [[X, R1] | D1], 0) :- eval_expr(Y, R1, E1, D1), E1 = 0, E is E1, !.
eval_prog(assign(_, Y), _, E, D1, D1, 0) :- eval_expr(Y, _, E1, D1), E1 \= 0, E is E1, !.

eval_prog(assert(X), R, E, D1, D1, 0) :- eval_expr(X, R1, E1, D1), E1 = 0, R1 = 0, E is 2, R is R1, !.
eval_prog(assert(X), R, E, D1, D1, 0) :- eval_expr(X, R1, E1, D1), E1 = 0, R1 = 1, E is E1, R is R1, !.
eval_prog(assert(X), _, E, D1, D1, 0) :- eval_expr(X, _, E1, D1), E1 \= 0, E is E1, !.

eval_prog(return(X), R, E, D1, D1, 1) :- eval_expr(X, R1, E1, D1), E1 = 0, R is R1, E is E1, !.
eval_prog(return(X), _, E, D1, D1, 0) :- eval_expr(X, _, E1, D1), E1 \= 0, E is E1, !.
 
eval_prog(semcol, _, 0, D, D, 0).

eval_prog(if(Exp, P1, _), R, E, D1, D2, S) :- eval_expr(Exp, R1, E1, D1), E1 = 0, R1 = 1, eval_list_prog(P1, R, E, D1, D2, S), !.
                                          
eval_prog(if(Exp, _, P2), R, E, D1, D2, S) :- eval_expr(Exp, R1, E1, D1), E1 = 0, R1 = 0, eval_list_prog(P2, R, E, D1, D2, S), !.

eval_prog(if(Exp, _, _), _, E, D1, _, 0) :- eval_expr(Exp, _, E1, D1), E1 \= 0, E is E1, !.


eval_prog(for(A1, Exp, A2, P), R, E, D1, D4, S) :- eval_prog(A1, _, E1, D1, D2, _), E1 = 0, eval_expr(Exp, R2, E2, D2), E2 = 0, R2 = 1, 
                                                   eval_list_prog(P, _, E3, D2, D3, S1), 
                                                   S1 = 0, E3 = 0,  eval_prog(for(A2, Exp, A2, P), R, E, D3, D4, S), !. 

eval_prog(for(A1, Exp, _, P), _, E, D1, D3, S1) :- eval_prog(A1, _, E1, D1, D2, _), E1 = 0, eval_expr(Exp, R2, E2, D2), E2 = 0, R2 = 1, 
                                                   eval_list_prog(P, _, E, D2, D3, S1), S1 = 0, !.

eval_prog(for(A1, Exp, _, _), _, E2, D1, D2, _) :- eval_prog(A1, _, E1, D1, D2, _), E1 = 0, eval_expr(Exp, R2, E2, D2), E2 = 0, R2 = 0, !.

eval_prog(for(A1, _, _, _), _, E, D1, D2, _) :- eval_prog(A1, _, E1, D1, D2, _), E1 \= 0, E is E1, !.  
 

eval_list_prog([H|P], R, E, D1, D3, S) :- eval_prog(H, _, E1, D1, D2, S1), E1 = 0, S1 = 0, eval_list_prog(P, R, E, D2, D3, S), !.                   
eval_list_prog([H|P], R, E, D1, D3, S) :- eval_prog(H, _, E1, D1, D2, S1), E1 \= 0, E1 \= 3, S1 = 0, E is E1, eval_list_prog(P, R, E, D2, D3, S), !.                   
eval_list_prog([H|_],R1, E1, D1, D2, S1) :- eval_prog(H, R1, E1, D1, D2, S1), !.                                   
eval_list_prog([], _, _, D, D, 0).

parseInputAux(L, R):- parse_all_prog(L, Ls), eval_list_prog(Ls, _, E, [], _, S), E = 0, S = 0, R = x, !.
parseInputAux(L, R):- parse_all_prog(L, Ls), eval_list_prog(Ls, R, E, [], _, S), E = 0, S = 1, !.
parseInputAux(L, R):- parse_all_prog(L, Ls), eval_list_prog(Ls, _, E, [], _, _), E = 2, R = a, !.
parseInputAux(L, R):- parse_all_prog(L, Ls), eval_list_prog(Ls, _, E, [], _, _), E = 3, R = e, !.
parseInputAux(_, e).

parseInput(F, R):-read_file_to_string(F, S, []), lparse(S, L), parseInputAux(L, R), !.








