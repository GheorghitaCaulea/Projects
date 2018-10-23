module Interpreter
  (
    -- * Types
    Prog,
    Asgn,

    -- * Functions
    evalRaw,
    evalAdt,
  ) where

-------------------------------------------------------------------------------
--------------------------------- The Expr ADT  -------------------------------
-------------------------------------------------------------------------------
data Expr = Add Expr Expr
          | Sub Expr Expr
          | Mult Expr Expr
          | Equal Expr Expr
          | Smaller Expr Expr
          | Symbol String
          | Value Int deriving (Show, Read)

data Asgn = Asgn String Expr deriving (Show, Read)

data Prog = Eq Asgn
          | Seq Prog Prog
          | If Expr Prog Prog
          | For Asgn Expr Asgn Prog
          | Assert Expr
          | Return Expr deriving (Show, Read)

parse :: String -> Maybe Prog
parse = undefined

{- Am definit tipul 'Dictionary' in care voi retine perechi de tipul '(String, Value x)'. -}
type Dictionary a = [(String, Expr)]  

{- Functia 'search' cauta in dictionar o pereche dupa un String dat. -}
search :: String -> Dictionary a -> Either String Int
search s [] = Left "Uninitialized variable"
search s (w:d) = if((fst w) == s) then (case evalExpr (snd w) (w:d) of 
    Left l -> Left l
    Right r -> Right r) else (search s d)

{- Functia 'evalAdd' evaluaeaza adunarea a doua expresii. -}
evalAdd :: Expr -> Expr -> Dictionary a -> Either String Int
evalAdd e1 e2 d = case ((evalExpr e1 d), (evalExpr e2 d)) of
    (Left l, _) -> Left l 
    (_, Left l) -> Left l
    (Right r1, Right r2) -> Right (r1 + r2)

{- Functia 'evalSub' evalueaza scaderea a doua expresii. -}    
evalSub :: Expr -> Expr -> Dictionary a -> Either String Int
evalSub e1 e2 d = case ((evalExpr e1 d), (evalExpr e2 d)) of
    (Left l, _) -> Left l
    (_, Left l) -> Left l
    (Right r1, Right r2) -> Right (r1 - r2)

{- Functia 'evalMult' evalueaza inmultirea a doua expresii. -} 
evalMult :: Expr -> Expr -> Dictionary a -> Either String Int
evalMult e1 e2 d = case ((evalExpr e1 d), (evalExpr e2 d)) of
    (Left l, _) -> Left l
    (_, Left l) -> Left l
    (Right r1, Right r2) -> Right (r1 * r2)

{- Functia 'evalEqual' evalueaza compararea egalitatii a doua expresii. -} 
evalEqual :: Expr -> Expr -> Dictionary a -> Either String Int
evalEqual e1 e2 d = case ((evalExpr e1 d), (evalExpr e2 d)) of
    (Left l, _) -> Left l
    (_, Left l) -> Left l
    (Right r1, Right r2) -> if (r1 == r2) then (Right 1) else (Right 0)

{- Functia 'evalEqual' evalueaza compararea a doua expresii(daca valoarea primeia este mai mica decat valoarea celei de-a doua). -} 
evalSmaller :: Expr -> Expr -> Dictionary a -> Either String Int
evalSmaller e1 e2 d = case ((evalExpr e1 d), (evalExpr e2 d)) of
    (Left l, _) -> Left l
    (_, Left l) -> Left l
    (Right r1, Right r2) -> if (r1 < r2) then (Right 1) else (Right 0)

{- Functia 'evalExpr' apeleaza functiile de mai sus pentru definirea generala a evaluarii unei expresii. -}
evalExpr :: Expr -> Dictionary a -> Either String Int
evalExpr e d = case e of
    Value i -> Right i
    Symbol i -> (case search i d of
        Left l -> Left l
        Right r -> Right r)
    Add e1 e2 -> evalAdd e1 e2 d 
    Sub e1 e2 -> evalSub e1 e2 d
    Mult e1 e2 -> evalMult e1 e2 d
    Equal e1 e2 -> evalEqual e1 e2 d
    Smaller e1 e2 -> evalSmaller e1 e2 d

{-Functia 'evalAsgn' evalueaza o atribuire, introducand in dictionar noua pereche sau intorcand eroare .-}
evalAsgn :: Asgn -> Dictionary a -> Either String (Dictionary a)
evalAsgn (Asgn s e) d = case (evalExpr e d) of 
    Left l -> Left l
    Right r -> Right ((s,(Value r)):d)
{-Functia 'evalAssert evaluaza un 'assert' si intoare '1' sau o eroare. -}
evalAssert :: Expr -> Dictionary a -> Either String Int
evalAssert e d = case evalExpr e d of
    Left l -> Left l
    Right r -> if (r == 1) then (Right r) else Left "Assert failed"
{-Functia 'EvalReturn' evalueaza un return si intoarce o valoare sau o expresie. -}
evalReturn :: Expr -> Dictionary a -> Either String Int
evalReturn e d = case evalExpr e d of
    Left l -> Left l
    Right r -> Right r
{-Functia 'evalIf' evalueaza o structura 'if'. -}
evalIf :: Expr -> Prog -> Prog -> Dictionary a -> Either String (Either (Dictionary a) Int)
evalIf e p1 p2 d = case evalExpr e d of
    Left l -> Left l
    Right r -> if (r == 1) then (case evalProg p1 d of
                                    Left l -> Left l
                                    Right r -> Right r) else (case evalProg p2 d of
                                                                Left l1 -> Left l1
                                                                Right r1 -> Right r1)
{-Functia 'evalFor' evalueaza o structura 'For'. -}
evalFor :: Asgn -> Expr -> Asgn -> Prog -> Dictionary a -> Either String (Either (Dictionary a) Int)
evalFor a1 e a2 p d = case evalAsgn a1 d of
    Left l -> Left l
    Right r -> (case evalExpr e r of
                Left l -> Left l
                Right r1 -> if (r1 == 1) then (case evalProg p r of
                                                Left l -> Left l
                                                Right (Left l2) -> evalFor a2 e a2 p l2
                                                Right (Right r2) -> Right (Right r2)) else (Right (Left r)))
{-Functia 'evalProg' evalueaza un program. -}
evalProg :: Prog -> Dictionary a -> Either String (Either (Dictionary a) Int)
evalProg p d = case p of
    Eq a -> case evalAsgn a d of 
        Left l -> Left l 
        Right r -> Right (Left (r))
    Seq p1 p2 -> case evalProg p1 d of 
            Left l -> Left l
            Right (Left l) -> (case evalProg p2 l of
                        Left l1 -> Left l1
                        Right (Left l1) -> Right (Left l1)
                        Right (Right r) -> Right (Right r))
            Right (Right r) -> Right (Right r) 
    Assert e -> case evalAssert e d of
        Left l -> Left l
        Right r -> Right (Left d)
    Return e -> case evalReturn e d of
        Left l -> Left l 
        Right r -> Right (Right r)
    If e p1 p2 -> case evalIf e p1 p2 d of
        Left l -> Left l
        Right r -> Right r
    For a1 e a2 p -> case (evalFor a1 e a2 p d) of
        Left l -> Left l
        Right r -> Right r

{-Apelez functia 'evalProg' cu un 'dictionar gol'.-}
evalAdt :: Prog -> Either String Int
evalAdt p = case evalProg p [] of
    Left l -> Left l
    Right (Left l) -> Left "Missing return"
    Right (Right r) -> Right r

evalRaw :: String -> Either String Int
evalRaw rawProg =
    case parse rawProg of
        Just prog -> evalAdt prog
        Nothing   -> Left "Syntax error"
