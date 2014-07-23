--
-- Transforma figuras em código TikZ para EPS
--
-- Andrei de A. Formiga, 2014-02-29
--

import Data.List (isInfixOf)
import Control.Monad (forM_)
import System.FilePath (dropExtension, replaceExtension)
import System.Environment (getArgs)
import System.Process (system)

usage :: IO ()
usage = do
    putStrLn "Usage: tex2eps <texfile>*"

latex :: FilePath -> IO ()
latex f = system ("latex " ++ f) >> return ()

dvips :: FilePath -> IO ()
dvips f = system ("dvips -E " ++ f ++ " -o " ++ (replaceExtension f ".eps")) >> return ()

epstool :: FilePath -> IO ()
epstool f = system ("epstool --copy --bbox " ++ tempFile ++ " " ++ f) >> return ()
    where tempFile = replaceExtension ((dropExtension f) ++ "_pre") ".eps"

processFile :: FilePath -> IO ()
processFile f = do
    putStrLn $ "Processing file " ++ f
    latex f
    dvips $ replaceExtension f ".dvi"
    epstool $ replaceExtension f ".eps"

main = do 
    args <- getArgs
    if null args then 
        usage
    else do
        forM_ args (processFile template) 

