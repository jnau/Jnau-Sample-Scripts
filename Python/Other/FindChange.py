#This program is meant for those who want the fewest number
#of bills possible when withdrawing money.

Amount = int(input('How much money do you wish to withdraw:')) #enter amt of money to withdraw.
num_hundred = int(Amount / 100) #amt of hundred dollar bills.
num_fifties = int((Amount % 100) / 50) #amt of fifty dollar bills.
num_twenties = int(((Amount % 100) % 50) / 20) #amt of twenty dollar bills.
num_tens = int((((Amount % 100) %50) % 20) / 10) #amt of ten dollar bills.
num_fives = int((((Amount % 100) % 20) % 10) / 5) #amt of five dollar bills.
num_ones = int((((Amount % 100) % 20) % 10) % 5) #amt of one dollar bills

print("You received: ")
print((num_hundred, "hundreds.")\n(num_fifties, "fifties.")\n(num_twenties,"twenties.")\n(num_tens, "tens.")\n(num_fives, "fives.")\n(num_ones, "ones.")\n) 
