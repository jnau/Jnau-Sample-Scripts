# PART D: Convert the sample FASTA file to FASTQ format
# Input: sample_fasta.txt file
# Output: sample_fastq.txt

open IN, 'sample_fasta.txt';
open OUT, '>sample_fastq.txt';
$newline = NULL;
while($newline=<IN>){

$titlecopy = $newline; 
$newline =~tr/>/@/;
print OUT $newline;

$newline=<IN>;
$seqcopy = $newline;
print OUT $newline;

$titlecopy =~ tr/>/+/;
print OUT $titlecopy;

$seqcopy =~ tr/ATGCatgc/X/;
print OUT $seqcopy;

}

close(IN);
close(OUT);