#!/usr/bin/perl

# Modified Needleman-Wunsch algorithm in order to compute the LCS. 

open (OUT, '> perl_test2.txt');      

# Asks the user for the length of strings.
#print "Enter length of the strings: \n"; 
#$len = <>;

# creates an array of nucleotides
#@chars = ("A","C","T","G");

# .= is to concatenate the nucleotides from the array @chars.
#$line1 .= $chars[rand @chars] for 1..$len;
#$line2 .= $chars[rand @chars] for 1..$len;
print "Enter your first string: \n";
$line1 = <>;
chomp $line1;

print "Enter your second string: \n";
$line2 = <>;
chomp $line2;

@string1 = split(//, $line1);
@string2 = split(//, $line2);

#print "@string1  @string2\n";

$n = @string1;                                              
$m = @string2;

print "The lengths of the two strings are $n, $m \n";

$Vm = 1;
$Cm = 0;
$Im = 0;

$V[0][0] = 0;

for ($i = 1; $i <= $n; $i++) {
        $V[$i][0] = -$i;
        print OUT "$string1[$i-1]";
}

print OUT "\n";

for ($j = 1; $j <= $m; $j++) {
        $V[0][$j] = -$j;
        print OUT "$string2[$j-1]";
}

print OUT "\n";

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
        print OUT "\nV[$i][$j] has value $V[$i][$j]";

    }
}

print "\n";
print OUT "\nLCS:  $V[$n][$m]\n";
close(OUT);