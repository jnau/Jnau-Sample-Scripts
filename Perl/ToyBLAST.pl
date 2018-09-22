#!/usr/bin/perl

# Lab 3 Exercise 3. 
# We will be creating a toy blast program
# We will be finding seed words (k-mers) first and then extending them to find potential
# alignments. 

# Enter Sfile
print "Enter Database Filename (S): ";
$sfile = <>;
open IN, "$sfile";
$comp = ""; # to read in a paragraph. what does this do? Answer in PDF.
while($dna = <IN>){
        $comp = $comp . $dna; # dot operator in order to concatenate
        chomp $comp;
}

# 
$dna = $comp;
chomp $dna;
#$dna =~ s/\n//g; # substitution operator
#$dna =~ s/\r//g;

@str1 = split(//, $dna);
$Qlen = @str1;

# initialization of Q array
$Qarr[0] = 0;
for ($i = 0; $i < $Qlen; $i++){
        $Qarr[$i] = $str1[$i];
#       print "$str1[$i] ";
}

# Enter Qfile
print "Enter Query Filename (Q): ";
$qfile = <>;
open IN, "$qfile";
$comp = "";
while($s = <IN>){
        $comp = $comp . $s;
        chomp $comp;
}

$s = $comp;
chomp $s;

@str2 = split(//, $s);
$Slen = @str2;

# initialization of S array
$Sarr[0] = 0;
for ($i = 0; $i < $Slen; $i++){
        $Sarr[$i] = $str2[$i];
#       print "$str2[$i] ";
}

# enter size of kmers taken from kmerfirst.pl
print "Input the length of the window: ";
$k = <>;
chomp $k;

%kmer = ();
$i=1;

#Make hash table for Query named "$s"
while (length($s) >= $k) {
        $s =~ m/(.{$k})/;
#       print "$1, $i \n";
        if(! defined $kmer{$1}){
                $kmer{$1} = [$i];
        }else {
                 push (@{$kmer{$1}}, $i)
        }

        $i++;
        $s = substr($s, 1, length($s) -1);
}

$count = 0;
%stringhash = ();
$i = 1;

while(length($dna) >= $k) {
        $dna =~ m/(.{$k})/;
        $count++;
        $lenmatch = $k;
        #print "$count";
        foreach $kmerkey (sort keys(%kmer)){
                if ($1 eq $kmerkey){
					foreach $position (@{$kmer{$kmerkey}}){
				
							$Qleft = $position;
							$Qright = $Qleft + ($k-1);
							$Sleft = $count;
							$Sright = $count + ($k-1);

							while(($Qleft - 1 >= - 1 && $Sleft- 1 >= -1) && $Sarr[$Sleft - 1] eq $Qarr[$Qleft-1]){
									$lenmatch++;
									$Qleft--;
									$Sleft--;
							}

							while(($Qright + 1 <= (keys %kmer) && $Sright + 1 <= length($dna)) && $Sarr[$Sright + 1] eq $Qarr[$Qright + 1]){
									$lenmatch++;
									$Qright++;
									$Sright++;
							}
							

							# Q: Why this would happen multiple times. 
							# A: Happens because we didn't have a reference to search through and it was not recorded.
							if(! defined $stringhash{$Qleft} && $lenmatch > 10){
									$stringhash{$Qleft} = $Qleft;

									$HSP = substr($dna, $Qleft, $lenmatch);
									#print "$stringhash{$firstOcc}";
									print "HSP: $HSP, with length $lenmatch\n";

								
							}
							
					}
                }
                
		$lenmatch = $k;
        }

        $dna = substr($dna, 1 , length($dna) - 1);
        $Sleft = 0;
        $Sright = 0;
}
