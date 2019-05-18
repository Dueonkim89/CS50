
from cs50 import get_string
from sys import argv, exit


def main():
    if not argv[1] or len(argv) > 2:
        print("Usage: python bleep.py dictionary")
        exit(1)

    # to hold unique badwords in file
    badWords = set()

    # read file and store all the bad words
    file = open(argv[1], "r")
    for word in file:
        badWords.add(word.rstrip("\n"))

    # get user prompt
    text = get_string("What message would you like to censor?\n")

    # get string in list format
    listFormat = text.split()
    length = len(listFormat)

    # list to store new output
    newOutPut = []

    # boolean flag
    found = False

    # loop thru the list and check if it is in bad words set
    for i in range(length):
        for badWord in badWords:
            if badWord == listFormat[i].lower():
                censored = '*' * len(badWord)
                newOutPut.append(censored)
                found = True
                break
        if not found:
            newOutPut.append(listFormat[i])
        found = False

    print(" ".join(newOutPut))


if __name__ == "__main__":
    main()
