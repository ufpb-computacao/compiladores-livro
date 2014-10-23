#!/bin/sh

find images --iname "*.tikz" | xargs ./tikz2eps 
# dvips -E fig.dvi -o fig.eps
# epstool --copy --bbox fig.eps fig_bb.eps
