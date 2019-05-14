from cs50 import get_float
import math

change = None
counter = 0
remainingChange = None

while True:
    change = get_float("Change owed: ")
    if change >= 0:
        break

if change >= 1:
    wholeNumber = math.trunc(change)
    counter = 4 * wholeNumber
    remainingChange = round(change - wholeNumber, 2)
else:
    remainingChange = change

while remainingChange > 0:
    if remainingChange >= .25:
        counter = counter + 1
        remainingChange = round(remainingChange - .25, 2)
    elif remainingChange < .25 and remainingChange >= .10:
        counter = counter + 1
        remainingChange = round(remainingChange - .10, 2)
    elif remainingChange < .10 and remainingChange >= .05:
        counter = counter + 1
        remainingChange = round(remainingChange - .05, 2)
    else:
        counter = counter + 1
        remainingChange = round(remainingChange - .01, 2)

print(counter)
