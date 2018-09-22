#!/usr/bin/perl

# Exercise 4.3

# According to the Prosite documentation, all known ER proteins, except for
# liver esterases, contain one of the 24 strings defined by the regular 
# expression above. The liver esterases are a bit different. Their motif is H
# followed by EL. Write a single Perl regular expression for that motif; then write
# a single Perl regular expression for "or" of the two regular expressions for ER proteins;
# then write a Perl program that takes in a sequence and checks to see if it contains
# any ER motif defined in this latter regular expression. How many different ER motifs
# are defined by that regular?

# Expressions:
# Liver esterase: H(T|V|I)EL
# ER Proteins: (K|R|H|Q|S|A)(D|E|N|Q)EL

print "Input a sequence: ";
$var = <>;

#print "YES\n" if $var =~ m/H(T|V|I)EL/; #liver esterase
#print "YES\n" if $var =~ m/(K|R|H|Q|S|A)(D|E|N|Q)EL/; #ER proteins

print "YES\n" if $var =~ m/H(T|V|I)EL|(K|R|H|Q|S|A)(D|E|N|Q)EL/; 

# ------- OUTPUT -------

=pod

27 motifs are defined, since 3 + 24 = 27.

=cut
