#!/usr/bin/perl

# 4.7
# Restriction enzymes are proteins that recognize specific DNA sequences and cut the DNA 
# molecule at a specific location in that sequence. One such recognition sequence is 
# GCCNNNNNGGC, where the character N stands for any of the four DNA nucleotides A, T, C or G.
# This sequence is recognized by the restriction enzyme called BGl1. Write a perl regular 
# expression that matches any BGl1 recognition sequence, and write a Perl program that takes
# in a string and determines if it contains a BGl1 recognition sequence.


print "Input a sequence: ";
$var = <>;

print "YES\n" if $var =~ m/GCC[ATCG][ATCG][ATCG][ATCG][ATCG]GCC/;
#print "YES\n" if $var =~ m/GCC[ATCG]{5}GCC/;

# -------- OUTPUT -------
=pod

Input a sequence: GCCAAAAAGCC
YES

=cut