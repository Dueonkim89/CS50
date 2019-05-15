from cs50 import get_int

def main():
    number = None
    length = None
    sum = 0

    while True:
        number = get_int("Number: ")
        if number >= 0:
            break

    length = len(str(number))

    if length < 13 or length > 16:
        print("INVALID")
        return False

    sum = sumOfDigits(number, length)

    if sum % 10 != 0:
        print("INVALID")
        return False

    # check if AMEX
    if ((length == 15 and str(number)[0] == '3') and (str(number)[1] == '4' or str(number)[1] == '7')):
        print("AMEX")
        return True

    # check if VISA
    if ((length == 13 or length == 16) and (str(number)[0] == '4')):
        print("VISA")
        return True

    # check if MasterCard
    if ((length == 16 and str(number)[0] == '5') and (str(number)[1] == '1' or str(number)[1] == '2' or
      str(number)[1] == '3' or str(number)[1] == '4' or str(number)[1] == '5')):
        print("MASTERCARD")
        return True

    # else invalid
    print("INVALID")


def sumOfDigits(numb, length):
    sum = 0
    # convert to string
    stringz = str(numb)
    # reverse the string
    stringz = stringz[::-1]
    # get the sum of the digits
    for i in range(length):
        if i % 2 != 0:
            digit = int(stringz[i]) * 2
            # if 2 digit number
            digitInString = str(digit)
            if len(digitInString) == 2:
                # add first and second number of digit
                sum = sum + int(digitInString[0]) + int(digitInString[1])
            else:
                sum += digit
        else:
            sum += int(stringz[i])
    return sum


if __name__ == "__main__":
    main()
