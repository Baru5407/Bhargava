#concepts: Variables,conditionals,user input,functions,loops
#game:promt the user for a max number(int)
#     the program will creatre a secret number within 0-max
#      the prigram will outpyt statitics aboyt guessing number
#n     the user gusses untill they find the number or excedd maxgguesses
#     output is determined by how many guesses it takes to finds secret nujmver

import random
import math
def main()
    #gert inout for max bound of secret number
    ubound=int(input("give upper bound:")
    #genarate secret number
    Rnum=random.randrange(0,ubound)
    print("\n max number of gusses:",(2*finlog(ubound)))
    print("avg numer of guesses:",findlog(ubound))
    print("lucky number of guesses:lessthan:",findlog(ubound))
    print("min number of guess is 1")
    print("\n lets play!")
    gameLoop(ubound, Rnum,(2*finlog(ubound)))
    #function used to find ceil binary lg if number
    #input:int
    #output:int
def findlog(num)
    #convert log base10 to bin log(base2_
    return math.ceil(math.log(num)/math.log(2))
               #ceil is used to for upper boundry value
        
   #end
