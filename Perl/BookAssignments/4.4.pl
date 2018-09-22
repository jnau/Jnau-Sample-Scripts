#!/usr/bin/perl

# Exercise 4.4

# Look up the triplets that code for the amino acid serine and a write regular expression 
# that matches the codons for serine. Then write a regular expression that matches any codon 
# for arginine or serine. Of course, one should put an "or" between the two separate regular 
# expressions for arginine and serine, but try instead to write a more regular expression 
# for them.

# Arginine: CGT, CGC, CGA, CGG, AGA, AGG
# 	Regular Expression: CG[ATCG]|AG[AG]

= pod

Serine: TC[TCAG]|AG[TC]
Arginine or Serine: (TC|AG|CG)[AGTC]

=cut