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

type Template = String

-- Nome default do template LaTeX para inserir o codigo da figura
templateName = "tikztempl.tex"

-- Marcador para inserir o codigo da figura no template
figureTag = "%%tikzfigure%%"

usage :: IO ()
usage = do
    putStrLn "Usage: tikz2eps <tikzfile>*"

applyTemplate :: Template -> String -> String
applyTemplate t fig = unlines $ concat [prolog, lines fig, epilog]
    where (prolog, epi) = break (isInfixOf figureTag) $ lines t
          epilog = case epi of { [] -> []; _ -> tail epi }

readTemplate :: FilePath -> IO Template
readTemplate = readFile

templateSubst :: Template -> FilePath -> IO ()
templateSubst temp f = do
    putStrLn $ "Processing file " ++ f
    fig <- readFile f
    let result = applyTemplate temp fig 
    let texFile = replaceExtension f ".tex"
    writeFile texFile result

main = do 
    args <- getArgs
    if null args then 
        usage
    else do
        template <- readTemplate templateName
        forM_ args (templateSubst template) 
