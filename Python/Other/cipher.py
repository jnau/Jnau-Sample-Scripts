#this code is going to mimic a cesarian cipiher
phrase = input('Please enter a string to be ciphered: ')
#phrase is our string that we want to be ciphered
shift = "" #to have a variable that we can input
n = -1 #n equals an arbitrary number so break doesn't remove n
while True:
    shift = str(input('Please enter a shift amount between 0 and 25: '))
    if shift.isdigit():
        #now we know input is an integer so cast it to int
        n = int(shift) #change into an integer to check the number

        #check for between 0 and 25
        if n>=0 and n<=25:
            break #break out of loop if input is valid

shift = int(shift) #change into an integer to shift the amount

result = '' #same deal as shift seen above
for char in phrase: 
    x = ord(char)#using the ord function to order the chars to their ascii values

    if char.isalpha():
        x = x + shift

        offset = 65 #offset number start for characters
        if char.islower(): #if its lower than that, offset it by 97
            offset = 97

        while x < offset: #26 letters in the alphabet
            x+= 26

        while x > offset+25:
            x -= 26

        result += chr(x) #using chr to then give the new ascii value
    else:
        result += chr(x)
        
print (result) #print the result
