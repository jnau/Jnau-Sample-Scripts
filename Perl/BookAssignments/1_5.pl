#!/usr/bin/perl
# 
# Exercise 1.5 Perl Script
# Program to change all lowercase letters into uppercase letters, vice versa.

$string = 'VRNrIAEelslrrFMVALILdIKrTPgNKPriaemICDIDtYIvEa'; 
$string =~ tr/A-Za-z/a-zA-Z/;
print "$string \n";

# ---------- Output -----------

=commentstart

vrnRiaeELSLRRfmvalilDikRtpGnkpRIAEMicdidTyiVeA 

=commentend