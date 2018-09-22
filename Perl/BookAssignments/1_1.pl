#!/usr/bin/perl
#
# Exercise 1.1 Perl Script
# A Simple Printing Program in order to understand the functionality of the print statement
# and corresponding special characters, such as \n or \t.

# Original Code
print "Welcome to Perl\n"; # Print a greeting
print "TATA is a box\n"; # Print a second line

# Part 1: Remove the \n characters from the first line and rerun
print "Welcome to Perl";
print "TATA is a box\n";

# Part 2: Remove second one too
print "Welcome to Perl";
print "TATA is a box";

# Part 3: Put the first one in, leave second out
print "Welcome to Perl\n";
print "TATA is a box";

# Part 4: insert \t after the quotes
print "Welcome to Perl";
print "\tTATA is a box\n";

# Part 5: insert \t in middle of statement
print "Welcome to Perl";
print "TATA \t is a \t box\n";
 
# Part 6: Replace double quotes with single quotes
print "Welcome to Perl";
print 'TATA is a box\n';

# Part 7: Use no quotes on one of the lines
print "Welcome to Perl";
print TATA is a box;

# ---------- Output -----------

=commentstart
Part 1
Welcome to PerlTATA is a box

Part 2
Welcome to PerlTATA is a box

Part 3
Welcome to Perl
TATA is a box

Part 4
Welcome to Perl	TATA is a box

Part 5
Welcome to PerlTATA 	 is a 	 box

Part 6
Welcome to PerlTATA is a box\n

Part 7
There is an error and it will not print the statement.
=commentend

