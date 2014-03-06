--
-- Transforma figuras em código TikZ para EPS
--
-- Andrei de A. Formiga, 2014-02-29
--

import Data.List (isInfixOf)

type Template = String

-- Nome default do template LaTeX para inserir o codigo da figura
templateName = "tikztempl.tex"

-- Marcador para inserir o codigo da figura no template
figureTag = "$$tikzfigure$$"


applyTemplate :: Template -> String -> String
applyTemplate t fig = unlines $ concat [prolog, lines fig, epilog]
    where (prolog, epi) = break (isInfixOf figureTag) $ lines t
          epilog = case epi of { [] -> []; _ -> tail epi }

readTemplate :: FilePath -> IO Template
readTemplate = readFile

main = do 
    template <- readTemplate templateName
    putStrLn "ok"

