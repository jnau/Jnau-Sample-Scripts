#!/usr/bin/perl

# Exercise 4.14
# In Eukaryotes, promoter sequences are more variable in Prokaryotes, such as the bacteria
# E.coli. In Eukaryotes, there are several different RNA polymerases that recognized different
# Eukaryotic promoter sequences. One type of RNA polymerase, the RNA polymerase II, recognizes 
# DNA sequences that consists of two segments, the TATA box (TATAWAW where W is either A or T), 
# and the initiator sequence (YYCARR), where Y is either C or T and R is either A or G.

# The two segments in these promoter sequences are separated by 17 nucleotides. Write a regular
# expression that matches this RNA polymerase II promoter sequence. 

# --------- OUTPUT --------

=pod
 
Regular Expression: TATA[AT]A[AT][ACTG]{17}[CT][CT]CA[AG][AG]

=cut