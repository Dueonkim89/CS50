import crypt
from sys import argv, exit


def main():
    if not argv[1] or len(argv) > 2:
        print("Usage: python crack.py hash")
        exit(1)

    # inputted hash
    hash = argv[1]
    # salt from the hash
    salt = argv[1][0] + argv[1][1]
    # possible letters
    possibleLetters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    # starting point
    hashCombos = len(possibleLetters)

    # Loop and check the starting letters
    for i in range(hashCombos):
        guess = crypt.crypt(possibleLetters[i], salt)
        if guess == hash:
            print(combined)
            exit(0)

    # Returns 2704 permutations (already checked)
    firstPermutationList = createAndCheckPermutations(hash, possibleLetters, hashCombos, salt)
    # Return 140,608 permutations (already checked)
    secondPermutationList = createAndCheckPermutations(hash, firstPermutationList, len(firstPermutationList), salt)
    # Returns 7,311,616 permutations (already checked)
    thirdPermutationList = createAndCheckPermutations(hash, secondPermutationList, len(secondPermutationList), salt)
    # Returns 380,204,032 permutations (already checked)
    fourthPermutationList = createAndCheckPermutations(hash, thirdPermutationList, len(thirdPermutationList), salt)


def createAndCheckPermutations(hash, priorList, hashCombos, salt):
    # array of permutations to be returned
    PermutationList = []
    # possible letters
    possibleLetters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

    # loop and create combos
    for i in range(hashCombos):
        for j in range(52):
            combined = priorList[i] + possibleLetters[j]
            PermutationList.append(combined)
            guess = crypt.crypt(combined, salt)
            if guess == hash:
                print(combined)
                exit(0)
    return PermutationList


if __name__ == "__main__":
    main()
