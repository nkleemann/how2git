"""
    Bruteforce Solution - Script for Autotool exercises using Hashing.

        - Gives your solution via bruteforcing
        - Tells you if your given solution is correct 
        - Automation of parameters with fixed insertion order
        - Automation of insertion order with fixed parameters
        

        Running the script:

            - Download script, save as "doubleHash.py"
            - Change things in script to match your exercise (see below) & PRESS SAVE 
            - Open Termimal / CMD.exe
            - Navigate to folder this file is saved in 
            - Type 'python2 <doubleHash.py>
            - If you don't have python2 installed
                -> https://www.python.org/download/releases/2.7.3/


    What you have to do:

        - Read the script and change all sections marked 
          with '# *' according to your exercise.
          This includes the following variables:
                - size (hashtable size)
                - given hashtable
                - wanted hashtable
                - function parameters for h1(x) (or function itself)
                - same for h2(x)
                - in InsertRand() function
                    - elements to insert (toInsert List)
                    - fixed insertions given by exercise
        

    I wrote this based on my exercise so you 
    may have to make changes. A lot. 

    Also you'll need a fast processor because bruteforcing
    is dumb. But some autotool exercises are too. ;)


    @ Niklas Kleemann 22.06.2017 
        
"""

import random


# Global verbousity.
# Change this to 0 if you want faster execution.
# Change this to 1 if you want to see autotool-like messages
# and hashtable status for every step.
beVerbous = 0


# Global size of hashtable # *
size = 15 

# Table given by instruction # *
WantedHashTable = [-1,    # 0
                   211,   # 1
                   86,    # 2
                   43,    # 3
                   165,   # 4
                   195,   # 5
                   -1,    # 6
                   196,   # 7  
                   218,   # 8
                   -1,    # 9
                   -1,    # 10
                   194,   # 11
                   76,    # 12
                   -1,    # 13
                   140]   # 14


# Declaring your hashTable (don't change here, see above)
hashTable = []

# We need to generate your given hashTable for each run from scratch,
# that's why we need a function to do so.
# Just add the values you are given at the right index
def genTable():
    hashTable[:] = []
    hashTable.extend(  
                  [-1,    # 0  
                   -1,    # 1
                   -1,    # 2
                   -1,    # 3
                   -1,    # 4
                   -1,    # 5
                   -1,    # 6
                   -1,    # 7  
                   -1,    # 8
                   -1,    # 9
                   -1,    # 10
                   194,   # 11
                    76,   # 12
                   -1,    # 13
                   140]   # 14
    )
    


# Prettyprint our hashtables
# printLevel 1 
def printTable():
    i = 0
    for el in hashTable:
        print "%i  %i\t\t%i" % (i, el, WantedHashTable[i])
        i += 1  
                          


# Parameters for hash functions:
# 
# h(x)  = nH + (mH * x) mod size
# h2(x) = ((nH2 + (mH2 * x)) mod modH2) mod size

# h(x)  # *
nH    = 4
mH    = 8

# h2(x) # *
nH2   = 10
mH2   = 6
modH2 = 12


# The actual hash functions # *
# Change them if needed 

def h(x):
    return (nH + (mH * x)) % size


def h2(x):
    return ((nH2 + (mH2 * x)) % modH2) % size


# Insertion into hashTable

def Insert(x):
    
    # Show Element to be inserted 
    # Show Output of h(x) & h2(x)
    
    if beVerbous:
        print "**** EXECUTING INSERT ****"

        print "Trying  %i\n" % x
        print "x     = %i" % x
        print "h(x)  = %i" % h(x)
        print "h2(x) = %i" % h2(x)

    # Element at Position we want to insert at
    AtWntdPos = hashTable[h(x)]


    # Field is empty 
    if (AtWntdPos == -1):

        print "\nWas empty, Inserting %i at %i" % (x, h(x))
        # Insert x 
        hashTable[h(x)] = x

    # Or contains x
    elif (AtWntdPos == x):
        # Nothing to do
        if beVerbous:
            print "\nContains %i" % x


    # Field is not empty (Start handling collision)
    else:

        # Calculate JUMP value
        JUMP = h2(x)
        # DEBUG
        # print "Jumpval: %i" % JUMP

        # Used for breaking out of infinite loop
        haveSeen = hashTable[(h(x))]

        # Start Iterating
        while (1):

            # Next Adress & new Position to jump to
            jmpdADR = (h(x) + JUMP) % size
            AtNewPos  = hashTable[jmpdADR]

            # We begin jumping adresses
            if beVerbous:
                print "\nProbe at adress %i" % jmpdADR

            # New Cell is empty
            if (AtNewPos == -1):
                print "\nWas empty, Inserting %i at %i" % (x, jmpdADR)
                hashTable[jmpdADR] = x
                break

            # New Cell allready contains x
            elif (AtNewPos == x):
                if beVerbous:
                    print "Contains %i" % x
                break

            # Handle infinite loop
            elif (haveSeen == AtNewPos):
                print "\nBad hash2; causing infinite loop"
                break
            

            # Cell is not free
            if beVerbous:
                print "Contains %i" % AtNewPos

            # Updating Jump counter
            JUMP = (JUMP + h2(x)) % size
            # DEBUG
            # print "LOOP JUMPVAL: %i" % JUMP
    
    if beVerbous:
        # Show tables
        printTable()
        print "******** FINISHED ********\n"



#          Bruteforcing functions


# Bruteforcing Parameters of first hash function
# nUp, nLO... nH lower and upper bound, etc..

def randH(nLO, nUP, mLO, mUP):
    global nH
    global mH
    
    nH = random.randrange(nLO, nUP+1)
    mH = random.randrange(mLO, mUP+1)


# Bruteforcing Parameters of sec. hash function
# n2Up, n2LO... nH2 lower and upper bound, etc..

def randH2(n2LO, n2UP, m2LO, m2UP, modLO, modUP):
    global nH2
    global mH2
    global modH2
    
    nH2   = random.randrange(n2LO,  n2UP+1)
    mH2   = random.randrange(m2LO,  m2UP+1)
    modH2 = random.randrange(modLO, modUP+1)


# Show your Solution

def logSolution():
    print "\n! Found solution !\nYour hash functions:"

    print "h(x)  = %i + %i * x mod %i" % (nH, mH, size)
    print "h2(x) = ((%i + (%i * x)) mod %i) mod %i" % (nH2, mH2, modH2, size)


# Bruteforcing Insertion Order
# Depending on your exercise you will have
# a set of fixed inserts. Mine are marked
# with "# /"

def InsertRand():

    # Making it easier for you to see beginning of 
    # new insertion sequence
    
    print "\n\n\t\t-~-~-~-~ START INSERTION SEQUENCE -~-~-~-~\n\n"


    # Values you have to insert
    # Delete all values in here and enter
    # those you you have to insert manually.
    # Order doesn't matter since we pick them randomly.
    toInsert = [86, 43, 218, 195] # *

    # / 
    Insert(165) # *

    # 3 Random picks
    for i in range(0, 3):
        Insert(toInsert.pop(random.randint(0, len(toInsert)-1)))
        
    # /
    Insert(211) # *

    # One random pick left
    Insert(toInsert.pop(random.randint(0, len(toInsert)-1)))

    #Insert(195)
    Insert(196)






#          Program Entry Point


# Generate our table
genTable()

# Iterating until we find the solution
while (hashTable != WantedHashTable):

    # New Try, generate new table
    genTable()

    # Randomize first hash function
    # Parameters greater than size wouldn't make
    # sense because we 'mod' them away - anyway.
    randH(0,size, 1,size)

    # Randomize second hash function
    randH2(0,size, 1,size, 1,size)

    # Execute random insertion order
    InsertRand()



# Found solution, print hash functions
# All you have to do now is trace back the insertion 
# order from program output and cp/paste.
logSolution()



# Bye!
