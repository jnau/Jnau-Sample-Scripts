#!/usr/bin/perl
#
# Exercise 1.9 Perl Script
# We are asked to count the number of purines in a DNA sequence.
# Purine = A & G. Pyrimidine = C & T

$dnastring = 'acCtagGgCCTTAcga';
#$purine = $dnastring;
#$purine =~ tr/agAG/agAG/;
#print "$dnastring\n";
print $dnastring =~ tr/agAG/agAG/;

# ---------- Output -----------

=commentstart

8

=commentend