#!usr/bin/perl

# Exercise 1.2.12
# Write a regular expression that defines the E. Coli consensus promoter sequence
# Promoter sequence: TTGACANNNNNNNNNNNNNNNNNTATATT where N is any nucleotide A,T,C,G and
# there are 18 N's.


=pod 

Regular expression: TTGACA(A|G|T|C){18}TATATT

=cut