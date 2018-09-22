#!usr/bin/perl

# Exercise 1.2.13
# Make the regular expressions as short as possible. Write a full program that reads in 
# a long string and determines if that string contains an E.Coli consensus promoter 
# sequence or a lactose promoter sequence. 

print "Input a sequence: ";

$var = <>;

print "Yes" if $var =~ m/TT(G|T)ACA(A|G|T|C){18}TAT(G|A)TT/;
print "\n";

# ----------- OUTPUT -----------

=pod

Input a sequence: GTACTTGACAATGATCGTAGCTAGTAGCTATATT
Yes

=cut