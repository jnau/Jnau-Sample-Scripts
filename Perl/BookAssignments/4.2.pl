#!/usr/bin/perl

# Exercise 4.2

# Modify the regular expression presented in the discussion of Rule 5, so that
# the new regular expression matches all of TATATAGG, and not only TAGG.

print "Input a sequence: ";
$var = <>;

if ($var =~ m/(TA)+GG/) {
	print "YES\n" ;
	}


# --------- OUTPUT ---------

=pod

Input a sequence: TATATAGG
YES

=cut