from sys import argv, exit
from cs50 import get_string


def main():
    if not argv[1] or len(argv) > 2:
        print("Usage: python vigenere.py k")
        exit(1)

    length = len(argv[1])

    # loop thru argv[1] and check each letter
    for i in range(length):
        if not argv[1][i].isalpha():
            print("Usage: python vigenere.py k")
            exit(1)

    letters = 'abcdefghijklmnopqrstuvwxyz'

    # 2 lists for upper and lower case letters
    lowerCaseList = []
    upperCaseList = []

    # list for index of ciper key
    cipherList = []
    # cipher counter, cannot exceed length of list
    counter = 0

    for i in range(26):
        lowerCaseList.append(letters[i])
        upperCaseList.append(letters[i].upper())

    # get cipherList as list of ints
    for i in range(length):
        for j in range(26):
            if argv[1][i].lower() == lowerCaseList[j]:
                cipherList.append(j)

    # prompt user
    plainText = get_string("plaintext: ")

    print("ciphertext: ", end="")

    # loop thru the plainText
    for i in range(len(plainText)):
        if counter > length - 1:
            counter = 0
        if not plainText[i].isalpha():
            print(plainText[i], end="")
        elif plainText[i].isupper():
            upper = shiftAndReturnLetter(cipherList[counter], plainText[i], upperCaseList)
            counter += 1
            print(upper, end="")
        else:
            lower = shiftAndReturnLetter(cipherList[counter], plainText[i], lowerCaseList)
            counter += 1
            print(lower, end="")

    print()


def shiftAndReturnLetter(key, letter, list):
    cipher = None
    for i in range(26):
        if letter == list[i]:
            cipher = (i + key) % 26
            break
    return list[cipher]


if __name__ == "__main__":
    main()
