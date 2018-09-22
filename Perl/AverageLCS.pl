#!/usr/bin/perl

# AverageLCS.pl
# Generate a number of random strings of a certain length and computes the average LCS.

#srand(1);
print "What is the name of your DNA file? \n";
$rstrings = <STDIN>;
open (OUT, ">$rstrings");

#print "What is the name of the file containing the average LCS? \n";
#$averageFile = <STDIN>;

print "How many random strings would you like:\n";
$numStr = <>;

print "How many nucleotides for the string?\n";
$nuc_length = <>;


$N = 0;
while($N < $numStr){
	$numstring = ''; # start with the empty string;
	$i = 0;
	while ($i < $nuc_length) {
   		$numstring = int(rand(4)) . $numstring;                                         
   		$i++;                                   
	}

	$dnastring = $numstring;                  
	$dnastring =~ tr/0123/actg/; # translate the numbers to DNA characters.
	print OUT "$dnastring\n";
	$N++;
}
close(OUT);

open (IN, "$rstrings");

$line = NULL;
$lineNum = 0;
$Sum = 0;
$Average = 0;

while($line = <IN>) {

	if ($lineNum eq 0) {
		chomp $line;
		$firstline = $line;
		#print OUT "$firstline\n";
		$lineNum = 1;
		
	}

	
	else {
		
		#print OUT "$line\n";
		chomp $line;
		$lineNum = $lineNum + 1;
		@string1 = split(//, $firstline);
		@string2 = split(//, $line);
		
		$n = @string1;
		$m = @string2;
		
		#print "@string1  @string2\n";
		#print "The lengths of the two strings are $n, $m \n";

		$Vm = 1;
		$Cm = 0;
		$Im = 0;

		$V[0][0] = 0;
		$max = 0;
		
		for ($i = 1; $i <= $n; $i++) {
        	$V[$i][0] = -$i;
        	#print OUT "$string1[$i-1]";
		}

		for ($j = 1; $j <= $m; $j++) {
        	$V[0][$j] = -$j;
        	#print OUT "$string2[$j-1]";
		}
		
		for ($i = 1; $i <= $n; $i++) {
			for ($j = 1; $j <= $m; $j++) {
        	
    			if ($string1[$i-1] eq $string2[$j-1]) {
        			$t = 1*$Vm;
        		}
                
        		else {
        			$t = 1*$Cm;
        		}

        		$max = $V[$i-1][$j-1] + $t;

        		if ($max < $V[$i][$j-1]) {
            		$max = $V[$i][$j-1] + (1 * $Im);
        		}

        		if ($V[$i-1][$j] > $max) {
        			$max = $V[$i-1][$j] + (1 * $Im);
        		}

        		$V[$i][$j] = $max;

    		}	
		}
		
		
		$Sum += $V[$n][$m];
		
		
	}
}

$Average = $Sum/$numStr;

print "Number of Strings: $numStr\nLength of String: $nuc_length\nAverage: $Average\n";
close(IN);

#--------- OUTPUT ---------

=pod
Number of Strings: 100

Length of String: 10

Average: 5.15


Number of Strings: 100

Length of String: 20

Average: 10.97


Number of Strings: 100

Length of String: 50

Average: 29.63


Number of Strings: 100

Length of String: 100

Average: 61.98


Number of Strings: 100

Length of String: 200

Average: 125.9

I observed that the average length of the LCS for each case, n = 10, 20, 50, 100, 200, fell
within the interval of the expected length. 0.54n <= E(LCS) <= 0.72n. 
=cut

