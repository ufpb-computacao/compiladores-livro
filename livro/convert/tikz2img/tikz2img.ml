(* 

  tikz2img.ml
  Converte imagens em TikZ para uma imagem

*)

(** Codigo inicial (prologo) *)
let prologo = 
"\\documentclass[a4paper]{article}
\\usepackage[T1]{fontenc}
\\usepackage[brazil]{babel}
\\usepackage[latin1]{inputenc}
\\usepackage{cmbright}
\\usepackage{color, graphicx, shortvrb, array}
\\usepackage{amsmath}
\\usepackage{amsthm}
\\usepackage{amsfonts}
\\usepackage{dsfont}
\\usepackage{amssymb} 
\\usepackage{tikz}

\\begin{document}

\\pagenumbering{gobble}"

(** Codigo final (epilogo) *)
let epilogo = "\\end{document}"

let imprime_instrucoes () = 
  print_string "Uso: tikz2img <arquivo>\n"

let constroi_tex fig = 
  String.concat "\n\n" [prologo; fig; epilogo]

(* Funcoes utilitarias para ler e escrever artigos, sem verificacao de erros *)
let le_arquivo arq = 
  let ch = open_in arq in 
  let len = in_channel_length ch in 
  let b = Buffer.create len in 
  Buffer.add_channel b ch len;
  close_in ch;
  Buffer.contents b

let escreve_arquivo arq cont = 
  let ch = open_out arq in
  output_string ch cont;
  close_out ch

let altera_extensao arq ext = 
  String.concat "." [Filename.chop_extension arq; ext] 

(* Comandos para conversao *)
let rec comandos lcs = 
  match lcs with
    [] -> ()
  | c :: resto -> 
    if Sys.command c = 0 then comandos resto 
    else Printf.printf "Erro executando comando: %s\n" c

let latex arq_tex = 
  Printf.sprintf "latex -halt-on-error -interaction=batchmode %s" arq_tex

let dvips arq_dvi arq_eps = 
  Printf.sprintf "dvips -E %s -o %s " arq_dvi arq_eps

let epstool arq_pre arq_eps = 
  Printf.sprintf "epstool --copy --bbox %s %s" arq_pre arq_eps

let convert arq_eps arq_png = 
  Printf.sprintf "convert -density 600 %s -alpha off %s" arq_eps arq_png 

(* Processa um arquivo de figura *)
let converte_figura arq = 
  let codigo_tex = le_arquivo arq |> constroi_tex in
  let arq_tex = altera_extensao arq "tex" in
  let arq_dvi = altera_extensao arq "dvi" in
  let arq_eps_pre = Filename.temp_file "tikz2img" ".eps" in
  let arq_eps = altera_extensao arq "eps" in
  let arq_png = altera_extensao arq "png" in
  escreve_arquivo arq_tex codigo_tex;
  comandos [latex arq_tex; 
            latex arq_tex; 
            dvips arq_dvi arq_eps_pre;
            epstool arq_eps_pre arq_eps;
            convert arq_eps arq_png;
            "rm -f *.log *.aux *.dvi *.eps"]


(* funcao principal *)
let main () = 
  if Array.length Sys.argv < 2 then 
    imprime_instrucoes ()
  else
    converte_figura Sys.argv.(1)

let () = main ()
