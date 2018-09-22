#!/usr/bin/perl
#
# Exercise 1.8 Perl Script
# Part 1: We are asked to write a program that uses the tr function to find the
# complement of any DNA sequence. ie. atcgATCG = tagcTAGC.

$dnastring = 'acCtagGgCCTTAcga';
$trdnastring = $dnastring;
$trdnastring =~ tr/atcgATCG/tagcTAGC/;
print "Original: $dnastring\n"; 
print "Complement: $trdnastring\n";


# Part 2: We are asked to translate a DNA string to RNA. Do not worry about 5'-3'

$dnastring = 'acCtagGgCCTTAcga';
$rnastring = $dnastring;
$rnastring =~ tr/atcgATCG/uagcUAGC/;
print "DNA: $dnastring\n";
print "RNA: $rnastring\n";

# ---------- Output -----------

=commentstart

Original: acCtagGgCCTTAcga
Complement: tgGatcCcGGAATgct

DNA: acCtagGgCCTTAcga
RNA: ugGaucCcGGAAUgcu

=commendend