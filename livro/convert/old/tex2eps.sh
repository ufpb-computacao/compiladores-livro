#!/bin/sh

latex $1
dvips -E $2 -o $3
epstool --copy --bbox $3 $4 
