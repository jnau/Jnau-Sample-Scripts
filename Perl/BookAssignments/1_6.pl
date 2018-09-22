#!/usr/bin/perl
#
# Exercise 1.6 Perl Script
# Program to regroup amino acids into group memberships: A E I as seen below.
# Ambivalent Group: A C G P S T W Y
# External Group: R N D Q E H K
# Internal Group: I L M F V

$proteinstring = 'SEETQMRLQLKRKLQRNRTSFTQEQIEALEKEFERTHYPDVFARERL';
$trprotein = $proteinstring;
$trprotein =~ tr/CGPSTWYA/A/;
$trprotein =~ tr/RNDQEHK/E/;
$trprotein =~ tr/ILMFV/I/;
print "Original: $proteinstring\n";
print "Sorted: $trprotein\n";

# ---------- Output -----------

=commentstart

Original: SEETQMRLQLKRKLQRNRTSFTQEQIEALEKEFERTHYPDVFARERL
Sorted: AEEAEIEIEIEEEIEEEEAAIAEEEIEAIEEEIEEAEAAEIIAEEEI

=commentend