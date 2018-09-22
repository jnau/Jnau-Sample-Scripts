#!/usr/bin/perl

# Exercise 3
# This is the Needleman-Wunsch global alignment algorithm WITH gaps.

# The modified parts of the code will contain a comment that states "NEW- " with
# a short explanation/statement about what was added AFTER the modified section. 

open (OUT, '> outer');
print "Input string 1 \n";
$line = <>;
chomp $line;
@string1 = split(//, $line); 

print "Input string 2\n";
$line = <>;
chomp $line;
@string2 = split(//, $line);

$n = @string1;
$m = @string2;

print "Enter match value (Vm): "; 
$Vm = <>;

print "Enter Mismatch cost (Cm): ";
$Cm = <>;

print "Enter Indel cost (Im): ";
$Im = <>;

print "Enter Gap cost (Gm): "; 
$Gm = <>;

while ($Gm < 0 or $Gm >= $Im){
	print "Gm should be a positive integer that is smaller than Im. Please enter it again: ";
	$Gm = <>;
} 
# NEW- asks the user for a Gap cost

print "The length of the two strings are $n, $m \n";

$V[0][0] = 0;

for ($i = 1; $i <= $n; $i++){

	if ($i==1){
		$V[$i][0] = -$Im*$i;
	}
	
	else{
		$V[$i][0] = -$Gm*$i; 
	}
	
	print OUT "$string1[$i-1]";
}
# NEW- This For-loop is modified to include the initial, horizontal gaps!

print OUT "\n";

for ($j = 1; $j <= $m; $j++) {

	if ($j==1){
		$V[0][$j] = -$Im*$j;
	}
	
	else{
		$V[0][$j] = -$Gm*$j;
	}
	
	print OUT "$string2[$j-1]";
}
# NEW- This For-loop is modified to include the initial, vertical gaps!

print OUT "\n";

$prevMove = "Start";

for ($i = 1; $i<=$n; $i++) {
	for ($j = 1; $j <= $m; $j++) {
	
		
		if ($string1[$i-1] eq $string2[$j-1]){
			$t = $Vm;
			$prevMove = "Diagonal";
		}
		
		else{
			$t = -$Cm;
			$prevMove = "Diagonal";
		}
		# NEW- This if-else statement checks for the DIAGONAL move (From Discussion Section)
		
		$max = $V[$i-1][$j-1] + $t;
		
		if ($prevMove eq "Horizontal_Space"){
			$score = $V[$i][$j-1] + $m - $m*2;
			
			if ($score > $max){
				$max = $score;
				$prevMove = "Horizontal_Gap";
			}
		}
		
		elsif ($prevMove eq "Horizontal_Gap"){
			$score = $V[$i][$j-1] - $m;
			
			if ($score > $max) {
				$max = $score;
				$prevMove = "Horizontal_Gap";
			}
		}
		
		else {
			$score = $V[$i][$j-1] - $Im;
			
			if ($score > $max){
			$max = $score;
			$prevMove = "Horizontal_Space";
			}
		
		}
		
		# NEW- The following block represents the HORIZONTAL moves (From Discussion Section)
		
		if ($prevMove eq "Vertical_Space"){
			$score = $V[$i-1][$j] + $n - $n*2;
			
			if ($score > $max){
				$max = $score;
				$prevMove = "Vertical_Gap";
			}
		}
		
		elsif ($prevMove eq "Vertical_Gap"){
			$score = $V[$i-1][$j] - $n;
			
			if ($score > $max) {
				$max = $score;
				$prevMove = "Vertical_Gap";
			}
		}
		
		else {
			$score = $V[$i-1][$j] - $Im;
			
			if ($score > $max){
			$max = $score;
			$prevMove = "Vertical_Space";
			}
		
		}
		# NEW- The following block represents the VERTICAL moves (Based off of the Horizontal Moves)
		
		$V[$i][$j] = $max;
		print OUT "\nV[$i][$j] has value $V[$i][$j]";
		
	}
	
}

print OUT "\n";
print OUT "\nThe similarity value is: $V[$n][$m]\n";
close (OUT);