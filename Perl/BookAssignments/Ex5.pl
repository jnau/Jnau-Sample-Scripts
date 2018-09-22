#!/pkg/bin/perl -w

# Exercise 5.1

# This is program accession.pl mentioned in lab 4.
# As a line is read, it checks if the line has the word ACCESSION
# followed by a space followed later by an accession number.
#It grabs the accession number if so. An accession number is
#a string that has either 1 or 2 capital letters, followed by
#a run of between 3 to 7 digitis. After the digits should
#be either a space, a comma, a period,
#a semi-colon, a colon, or a question mark. 

print "type the input file name please\n";
open (INFO, <>);  # open the input file and assign the handle INFO

print "type the output file name please\n";
$myoutfile = <>;  # Read in the file name for the output.
open (OUTFO, "> $myoutfile"); # open the output file and assign the handle
                              #OUTFO

while ( $line = <INFO>) {     # Read one line at a time from INFO, until
        while($line =~ m/.*?ACCESSION .*?([A-Z]{1,2}\d{3,7})[ ,.;:?]/g){
                print OUTFO "$1\n";
        }
}

# ------- Output --------

=pod

Results for Exercise 5.1

U63121
FA10325
PQ3469
NO9978

Results for Exercise 5.2

The input line does contain what looks like a dna sequence of length at least three, and it is ACC 
The input line is 
The primary ACCESSION number might be something like U63121 or maybe the ACCESSION is FA10325, 
or the ACCESSION is PQ3469. I don't know what the sequences are for these numbers. Maybe they 
are atcGGGAcatcaGGG or maybe not. Is this another ACCESSION number NO9978 or is it a telephone 
number. Perhaps XYzCATCGGAPQ is a DNA string? What will the program do with it? Is that what 
you want it to do? 

=cut