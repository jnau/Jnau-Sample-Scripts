# LCS_problem.py

# This is for Python 2.7
# This python script is meant to generate the ILP file to solve the LCS problem.
# Call this program on command line as: python2.7 RNA_file.txt LP_outputfile.lp minDist
# Inputs:
#	RNA_file.txt, a plain text file containing an RNA sequence with max 100 nucleotides.
#	minDist, the minimum distance between matches, we can consider this as spaces/indels.
# Output:
#	LP_outputfile.lp

# import sys module
import sys

arg1 = sys.argv[1]
arg2 = sys.argv[2]
minD = sys.argv[3]

minD = int(minD) # this will be set to 0 for a minimum of no spaces.
listP = "" # Variable will be set to 1 when there is a match.

INFILE = open(arg1, "r")
OUTFILE = open(arg2, "w")

# be sure to read separate sequences.
DNA = []

# Assume DNA sequences are of EQUAL length
n = 0
for line in INFILE:
    if (n==0):
        DNA.append(line.rstrip())
        n += 1
    elif (n==1):
        DNA.append(line.rstrip()[::-1])

    print "You input the sequence: ", line.rstrip()
    SeqLength = len(line.rstrip())

DNA = "".join(DNA)
print "Your joined DNA is: ", DNA
DNAlength = len(DNA)
local_range = SeqLength + 1
global_range = DNAlength + 1
#print (local_range)
#print (global_range)
legal = [[0 for x in range(1, global_range + 1)]for y in range(1, global_range + 1)]
#print (legal) # make sure this is correct

for i in range(1, local_range):
    for j in range(local_range, global_range):

        #print(j-i, minD)
        if (j-i > minD):
            if (DNA[i-1] == 'A') and (DNA[j-1] == 'A'):
                #print (DNA[i - 1], i - 1, j - 1)
                legal[i][j] = 1
                #OUTFILE.write("V(%d,%d) = 0 \n" % (i,j))
            if (DNA[i-1] == 'T') and (DNA[j-1] == 'T'):
                #print (DNA[i - 1], i - 1, j - 1)
                legal[i][j] = 1
                #OUTFILE.write("V(%d,%d) = 0 \n" % (i,j))
            if (DNA[i-1] == 'C') and (DNA[j-1] == 'C'):
                #print (DNA[i - 1], i - 1, j - 1)
                legal[i][j] = 1
                #OUTFILE.write("V(%d,%d) = 0 \n" % (i,j))
            if (DNA[i-1] == 'G') and (DNA[j-1] == 'G'):
                #print (DNA[i - 1], i - 1, j - 1)
                legal[i][j] = 1
                #OUTFILE.write("V(%d,%d) = 0 \n" % (i,j))
            legal[i][j] = legal[i][j]

# print(legal)
# Print out the Objective Function
OUTFILE.write("Maximize \n")

# Accumulate a list of P variables for our legal pairs.
for i in range(1, local_range):
    for j in range(local_range, global_range):
        #print (i,j, legal[i][j], DNA[i-1], DNA[j-1])
        if (legal[i][j] == 1):
            listP = listP + "+P(%d,%d) " % (i,j)

OUTFILE.write ("\nP \n")
OUTFILE.write ("\nsuch that \n")

# produce an equality that sets ILP variable P to the sum of the P(i,j) variables.
OUTFILE.write (listP + "- P = 0 \n\n")

# the following lines will now generate the inequalities to ensure that
# each nucleotide is paired to at most one nucleotide

for i in range(1,global_range):

    inequality = ""

    for j in range(1, local_range):
        if (legal[j][i]):
            inequality = inequality + " + P(%d,%d)" % (j,i)

    for j in range(local_range,global_range):
        if (legal[i][j]):
            inequality = inequality + " + P(%d,%d)" % (i,j)

    inequality = inequality + ' <= 1'
    OUTFILE.write (inequality)
    OUTFILE.write ("\n\n")

# Now we want to ensure that the lines do not cross in our model.
for h in range(1, local_range-1):
    for i in range(h+1, local_range):
        for j in range(local_range, global_range - 1):
            for k in range(j+1, global_range):
               if ((legal[h][j] == 1) and (legal[i][k])):
                    OUTFILE.write ("P(%d,%d) + P(%d,%d) <= 1 \n" % (h,j,i,k))

OUTFILE.write("\n")
OUTFILE.write ("binary \n")
for i in range(1, local_range):
   for j in range(local_range, global_range):
      if (legal[i][j]):
        OUTFILE.write ("P(%d,%d) \n" % (i,j))
OUTFILE.write("\n")
OUTFILE.write ("general\nP\n")
OUTFILE.write  ("end \n")
print "The ILP is in file %s" % arg2
INFILE.close()
