#!/usr/bin/perl

# Exercise 4.6
# Would it be correct to write the regular expression for Genbank accession numbers as
# \s\w{1,2}\d{5,6}\s? Explain.


# -------- OUTPUT ---------
=pod

No. The regular expression above, \s\w{1,2}\d{5,6}\s, will not work for the accession 
number because as we define an accession number to be either ONE capital letter followed
by FIVE digits or TWO capital letters followed by SIX digits. This expression may give 
us an expression with 1 capital letter followed by 6 digits, or 2 capital letters 
followed by 5 digits. 

=cut