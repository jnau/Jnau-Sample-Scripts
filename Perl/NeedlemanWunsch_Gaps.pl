#!/usr/bin/perl

# Exercise 2
# This is the Needleman-Wunsch global alignment algorithm without gaps

# The modified parts of the code will contain a comment that states "NEW- " with
# a short explanation/statement about what was added AFTER the modified section. 

open (OUT, '> outer');
print "Input string 1\n";
$line = <>;
chomp $line;
@string1 = split(//, $line); # character array


print "Input string 2\n";
$line = <>;
chomp $line;
@string2 = split(//, $line);

$n = @string1;
$m = @string2;

print "The length of the two strings are $n, $m \n";


print "Enter match value (Vm): "; # Input score for a match
$Vm = <>;

print "Enter Mismatch cost (Cm): ";
$Cm = <>;

print "Enter Indel cost (Im): ";
$Im = <>;

# NEW- Asks the user for the different scoring values. 

$V[0][0] = 0; # first [] represents the row index, and second [] is column index, index starts at 0!

for ($i = 1; $i <= $n; $i++) {
	$V[$i][0] = -$Im*$i; 
	print OUT "$string1[$i-1]";
}

print OUT "\n";

for ($j = 1; $j <= $m; $j++) {
	$V[0][$j] = -$Im*$j; 
	print OUT "$string2[$j-1]";
}

# NEW- These two for loops changed in order to include the indel cost (Im).

print OUT "\n";

for ($i = 1; $i<=$n; $i++) {
	for ($j = 1; $j <= $m; $j++) {
	
	# 1) This statement checks for a diagonal move
	if ($string1[$i-1] eq $string2[$j-1]) {
		$t = 1*$Vm; # match
	}
	
	else {
		$t = -1*$Cm; # mismatch
	}
		
	# NEW- $t is changed to incorporate the cost of a mismatch and match.
		
	$max = $V[$i-1][$j-1] + $t;
	
	# 2) Check for a horizontal move
	if ($max < $V[$i][$j-1] - $Im) {
		$max = $V[$i][$j-1] - $Im;
	}
	
	# 3) Check for a vertical move
	if ($V[$i-1][$j] - $Im > $max) {
		$max = $V[$i-1][$j] - $Im;
	}
	
	# NEW - the horizontal and vertical checks are changed to inclue the indel cost. 
	$V[$i][$j] = $max;
	print OUT "\nV[$i][$j] has value $V[$i][$j]";
	
	}
}

print OUT "\n";
print OUT "\nThe similarity value is: $V[$n][$m]\n";
close (OUT);

# -------- Output -------- 

=pod

For Vm = 1, Cm = 1, and Im = 2

AATAAGGTTGA
ATAATCGTTAA

V[1][1] has value 1
V[1][2] has value -1
V[1][3] has value -3
V[1][4] has value -5
V[1][5] has value -7
V[1][6] has value -9
V[1][7] has value -11
V[1][8] has value -13
V[1][9] has value -15
V[1][10] has value -17
V[1][11] has value -19
V[2][1] has value -1
V[2][2] has value 0
V[2][3] has value 0
V[2][4] has value -2
V[2][5] has value -4
V[2][6] has value -6
V[2][7] has value -8
V[2][8] has value -10
V[2][9] has value -12
V[2][10] has value -14
V[2][11] has value -16
V[3][1] has value -3
V[3][2] has value 0
V[3][3] has value -1
V[3][4] has value -1
V[3][5] has value -1
V[3][6] has value -3
V[3][7] has value -5
V[3][8] has value -7
V[3][9] has value -9
V[3][10] has value -11
V[3][11] has value -13
V[4][1] has value -5
V[4][2] has value -2
V[4][3] has value 1
V[4][4] has value 0
V[4][5] has value -2
V[4][6] has value -2
V[4][7] has value -4
V[4][8] has value -6
V[4][9] has value -8
V[4][10] has value -8
V[4][11] has value -10
V[5][1] has value -7
V[5][2] has value -4
V[5][3] has value -1
V[5][4] has value 2
V[5][5] has value 0
V[5][6] has value -2
V[5][7] has value -3
V[5][8] has value -5
V[5][9] has value -7
V[5][10] has value -7
V[5][11] has value -7
V[6][1] has value -9
V[6][2] has value -6
V[6][3] has value -3
V[6][4] has value 0
V[6][5] has value 1
V[6][6] has value -1
V[6][7] has value -1
V[6][8] has value -3
V[6][9] has value -5
V[6][10] has value -7
V[6][11] has value -8
V[7][1] has value -11
V[7][2] has value -8
V[7][3] has value -5
V[7][4] has value -2
V[7][5] has value -1
V[7][6] has value 0
V[7][7] has value 0
V[7][8] has value -2
V[7][9] has value -4
V[7][10] has value -6
V[7][11] has value -8
V[8][1] has value -13
V[8][2] has value -10
V[8][3] has value -7
V[8][4] has value -4
V[8][5] has value -1
V[8][6] has value -2
V[8][7] has value -1
V[8][8] has value 1
V[8][9] has value -1
V[8][10] has value -3
V[8][11] has value -5
V[9][1] has value -15
V[9][2] has value -12
V[9][3] has value -9
V[9][4] has value -6
V[9][5] has value -3
V[9][6] has value -2
V[9][7] has value -3
V[9][8] has value 0
V[9][9] has value 2
V[9][10] has value 0
V[9][11] has value -2
V[10][1] has value -17
V[10][2] has value -14
V[10][3] has value -11
V[10][4] has value -8
V[10][5] has value -5
V[10][6] has value -4
V[10][7] has value -1
V[10][8] has value -2
V[10][9] has value 0
V[10][10] has value 1
V[10][11] has value -1
V[11][1] has value -19
V[11][2] has value -16
V[11][3] has value -13
V[11][4] has value -10
V[11][5] has value -7
V[11][6] has value -6
V[11][7] has value -3
V[11][8] has value -2
V[11][9] has value -2
V[11][10] has value 1
V[11][11] has value 2

The similarity value is: 2

=cut 