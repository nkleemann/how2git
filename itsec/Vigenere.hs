{-
    plain = "ESHANDELTSICHUMEINMONOGRAPHISCHESPOLYALPHABETISCHESSUBSTITUTIONSVERFAHREN"
    key   = "PFAHL"
-}

module Vig where

import Data.Char
 
encode :: Char -> Char -> Char
encode key plain = toLetter $ mod (ord key + ord plain) 26

decode :: Char -> Char -> Char
decode key plain = toLetter $ mod (ord plain - ord key) 26

toLetter :: Int -> Char
toLetter = chr . (+) (ord 'A')

vigenere mode key plain = zipWith mode (cycle key) plain
