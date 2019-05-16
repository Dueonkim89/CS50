from sys import argv
from cs50 import get_string


def main():
    letters = 'abcdefghijklmnopqrstuvwxyz'
    # 2 lists for upper and lower case letters
    lowerCaseList = []
    upperCaseList = []

    length = len(str(letters))
    key = None

    print(argv[1])

    if len(argv) != 2 or not argv[1]:
        print("Usage: python caesar.py k")
        return 1

    try:
        key = int(argv[1])
    except:
        print("Ciper key must be an integer!")
        return 1

    for i in range(length):
        lowerCaseList.append(letters[i])
        upperCaseList.append(letters[i].upper())

    # prompt user for string input
    plainText = get_string("plaintext: ")

    print("ciphertext: ", end="")

    # loop thru the plainText
    for i in range(len(plainText)):
        if not plainText[i].isalpha():
            print(plainText[i], end="")
        elif plainText[i].isupper():
            upper = shiftAndReturnLetter(key, plainText[i], upperCaseList)
            print(upper, end="")
        else:
            lower = shiftAndReturnLetter(key, plainText[i], lowerCaseList)
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
