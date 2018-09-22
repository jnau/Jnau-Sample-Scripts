#this program will allow the user to play "hangman"


#these are the global variables we wil be using
num_wrong = 0
question_marks = ""
guess_letters = ""


def get_secret_word(): #to obtain the secret word
    global question_marks
    
    while True:
        question = ("Please enter a word to be guessed\nthat does not contain ? or white space: ")
        secret_word = input(question).lower()#.strip()
        
        invalid_characters = [' ', '?'] #if a space or ? in word, it is invalid
        if not any(x in secret_word for x in invalid_characters):
            question_marks = "".join(len(secret_word) * "?")
            return secret_word
        
# end of get_secret_word()

secret_word = get_secret_word() #global variable

def get_guess(): #function to obtain a valid guess
    global guess_letters
    global num_wrong
    global secret_word
    global question_marks

    guess = ""

    while True:
        guess = input("Please enter your next guess: ").lower().strip()
        invalid_characters = [' ', '?']
        
        if any(x in guess for x in invalid_characters):
            continue
        elif len(guess) > 1:
            print("You can only guess a single character.")
            continue
        elif len(guess) == 0:
            print ("You must enter a guess.")
            continue
        elif any(x in guess for x in guess_letters):
            print("You already guessed the character: ", guess)
            continue
        else:
            guess_letters += guess
            break

    # at this point we have a valid guess
    # this snippet of code replaces the '?' at the correct position with the valid guess letter
    # first see if the guess is in the secret word
    if secret_word.count(guess):
        # if so, replace the proper question marks with the guessed letter
        question_marks = list(question_marks)
        for i in range(len(secret_word)):
            if secret_word[i] == guess:
                question_marks[i] = guess
    else:
        # if not, then the guess was wrong
        num_wrong = num_wrong + 1
    
    question_marks = "".join(question_marks)
    
    return guess
# end of get_guess()

def display_guesses(): #display what the user has guessed so far
    global guess_letters
    sorted_letters = ", ".join(sorted(guess_letters))
    print("So far you have guessed: ", sorted_letters)
    return
# end of display_guesses()

def display_marks(): #display the masked word with question marks
    global question_marks
    print(question_marks)
    return
# end of display_marks()

def display_hangman():
    global num_wrong
    
    if num_wrong == 1:
        print(' |')
    elif num_wrong == 2:
        print(' |')
        print(' 0')
    elif num_wrong == 3:
        print(' |')
        print(' 0')
        print(' |')
    elif num_wrong == 4:
        print(' |')
        print(' 0')
        print('/|')
    elif num_wrong == 5:
        print(' |')
        print(' 0')
        print('/|\\')
    elif num_wrong == 6:
        print(' |')
        print(' 0')
        print('/|\\')
        print('/')
    elif num_wrong == 7:
        print(' |')
        print(' 0')
        print('/|\\')
        print('/ \\')
    return

# end of display_hangman()

def is_game_over(): 
    global num_wrong
    global question_marks
    global secret_word
    global guess_letters
    
    # returns False if num_wrong == 7 or question_mark == secret_word
    
    if (num_wrong == 7):
        display_hangman()
        print("You failed to guess the secret word:", secret_word)
        return False
    elif (question_marks == secret_word):
        print("You correctly guessed the secret word:", secret_word)
        return False
    else:
        #print("game is continuing...")
        return True

def main():
    global secret_word
    global question_marks
    
    print(30 * "\n")
    print(question_marks)
    print("So far you have guessed:")
    get_guess()
    
    while is_game_over():
        display_hangman()
        display_marks()
        display_guesses() 
        get_guess()
        
main()
