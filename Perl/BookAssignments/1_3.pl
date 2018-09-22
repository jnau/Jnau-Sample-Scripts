#!/usr/bin/perl
# 
# Exercise 1.3 Perl Script
# Translating RNA to DNA strand. Introduction to the tr function and assignment of variables.

$nucstring = 'acCtagGgCCTTAcga';
$dnastring = $nucstring;
$nucstring =~ tr/tT/uU/;
print "$nucstring \n";
print "$dnastring \n";

# ---------- Output -----------

=commentstart

acCuagGgCCUUAcga 
acCtagGgCCTTAcga 

=commentend
