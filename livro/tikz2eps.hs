--
-- Transforma figuras em código TikZ para EPS
--
-- Andrei de A. Formiga, 2014-02-29
--

import Data.List (isInfixOf)
import Control.Monad (forM_)
import System.FilePath (splitExtension)
import System.Environment (getArgs)

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

outputFileName :: FilePath -> FilePath
outputFileName = (++".tex") . fst . splitExtension 

-- outputFileName fname = noext ++ ".tex"
--    where (noext, _) = splitExtension fname 

processFile :: Template -> FilePath -> IO ()
processFile temp f = do
    putStrLn $ "Processing file " ++ f
    fig <- readFile f
    let result = applyTemplate temp fig 
    writeFile (outputFileName f) result

main = do 
    args <- getArgs
    if null args then 
        usage
    else do
        template <- readTemplate templateName
        forM_ args (processFile template) 

