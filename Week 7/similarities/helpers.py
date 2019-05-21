from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # split each file into lines
    a = a.split('\n')
    b = b.split('\n')
    # list to hold common lines
    commonList = []
    length = len(a)

    # loop thru the split lines
    for i in range(length):
        # try, except block to see if it exists in both.
        try:
            common = b.index(a[i])
            commonList.append(a[i])
        except:
            continue

    # remove duplicates from list if it exists.
    for i in range(len(commonList)):
        if i != commonList.index(commonList[i]):
            commonList.remove(commonList[i])

    # return the list with common lines
    return commonList


def sentences(a, b):
    """Return sentences in both a and b"""

    # get list of sentences.
    a = sent_tokenize(a)
    b = sent_tokenize(b)

    # list to hold common lines
    commonList = []
    length = len(a)

    # loop thru the split lines
    for i in range(length):
        # try, except block to see if it exists in both.
        try:
            common = b.index(a[i])
            commonList.append(a[i])
        except:
            continue

    # remove duplicates from list if it exists.
    for i in range(len(commonList)):
        if i != commonList.index(commonList[i]):
            commonList.remove(commonList[i])

    # return the list with common lines
    return commonList


def getSubStrings(n, list):
    # list for substrings.
    subStrings = []

    # loop thru argument and generate substrings
    for strings in list:
        leng = len(strings)
        for i in range(leng):
            if i + n > leng:
                break
            else:
                subStrings.append(strings[i:i+n])

    # return list of substrings
    return subStrings


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    # compares 2 files based on number of substrings of length n in common

    # split each file into lines
    a = a.split()
    b = b.split()

    # get substrings for both a and b
    aSubstring = getSubStrings(n, a)
    bSubstring = getSubStrings(n, b)

    # list for common substrings
    commonSubStrings = []

    # loop thru substring to get common substrings in A and B
    for substring in aSubstring:
        if substring in bSubstring:
            commonSubStrings.append(substring)

    # convert list to set and return it
    return set(commonSubStrings)
