module Main where

crack :: String -> String
crack s = s

main :: IO ()
main = do
    code <- readFile "Code.txt"
    putStrLn $ crack code