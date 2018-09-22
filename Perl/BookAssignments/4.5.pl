#!/usr/bin/perl

# Exercise 4.5

# Recall our earlier discussion on masking out CA-repeats. We don't want to replace each
# CA with an X, but only those occurrences of CA that are found consecutively, with say
# at least five copies. Try out the following code on different examples to determine if the
# following code will do this. 

print "Input a sequence: ";
$varstring = <>;

$varstring =~ s/(CA){5}(CA)*/X/g;

print "$var\n";

# --------- OUTPUT ---------

=pod
Input a sequence: CA
CA

Input a sequence: CACACACACA
X

Input a sequence: CACACACACACACACA
X

Input a sequence: AATTCCCACACACACACACAAAA
AATTCCXAAA

Input a sequence: CACACACACATCACACACACATCACA
XTXTCACA

This code replaces all occurrences of 5+ consecutive 'CA' with an 'X' if it is found 
in the input string.

=cut 