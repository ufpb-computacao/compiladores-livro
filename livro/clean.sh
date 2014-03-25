#!/bin/sh
find images -iname "*.dvi" | xargs rm -f 
find images -iname "*.aux" | xargs rm -f 
find images -iname "*.log" | xargs rm -f 
find images -iname "*.tex" | xargs rm -f 

