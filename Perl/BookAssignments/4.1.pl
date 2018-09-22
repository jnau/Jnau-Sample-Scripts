#!/usr/bin/perl

# Exercise 4.1

# Write a full program to take in a string and then determine if the string
# contains a substring that matches TA+GG. Try the input ATATAAAGGGA; then 
# try out the input string ATATGGA. Then change the symbol + to * in the
# regular expression and try out the two input strings again. Explain the results. 

print "Input a sequence: "; # take in a string
$var = <>;

# determine if the string contains TA+GG or TA*GG 
print "There is a substring that matches TA+GG\n" if $var =~ m/TA+GG/; 
print "There is a substring that matches TA*GG\n" if $var =~ m/TA*GG/; 


# ----------- OUTPUT -----------

=pod
Case 1 (+)
Input a sequence: ATATAAAGGGA
There is a substring that matches TA+GG

Input a sequence: ATATGGA

For this case, only the first input returned a match, while the second does not return anything.
This is because the second sequence ATATGGA does not contain a character 'A' one or more times
followed by 'GG'.

Case 2 (*)
Input a sequence: ATATAAAGGGA
There is a substring that matches TA*GG

Input a sequence: ATATGGA
There is a substring that matches TA*GG

For this case, both sequences returned a match. The (*) operator means that the character
'A' can appear zero or more times, and then followed by 'GG'.
=cut