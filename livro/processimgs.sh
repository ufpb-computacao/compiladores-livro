#!/bin/sh

find images --iname "*.tikz" | xargs ./tikz2eps 
