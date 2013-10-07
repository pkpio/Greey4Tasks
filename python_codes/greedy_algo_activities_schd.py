# -*- coding: utf-8 -*-
"""
Author  : Praveen Kumar
Created : 05/10/2013
Project : EE 677: VLSI CAD course project - Greedy Algorithm for Activity scheduling
Github  : https://github.com/praveendath92/EE-677_project
"""
import operator

#Modify the values of the activities here
###################################
startTimes = [0,2,4,3]
endTimes = [2,3,6,5]
###################################


#End program if the sizes of startTime and endTime mismatch
if(len(startTimes) != len(endTimes)):
   print("Error ! \nLengths of the startTime and endTime mismatch ! \nPlease modify them and try again !")
   
#If they match continue
else:

    ####    Defining activity object    #####
    
    class activity:
        def __init__(self):
            self.start = 0
            self.end = 0
            

            
    ####     Defining global variables   ####
            
    global activities
    activities =  [ activity() for i in range(len(startTimes))]

    #This one is to hold sorted activities
    global sortActs
    sortActs =  [ activity() for i in range(len(startTimes))]

    #And this one to hold to the final choice of activities
    global finalActs
    finalActs =  [ activity() for i in range(len(startTimes))]

    #no. of activities in the finalActs list
    global length
    length = 1 #min. length in 1

    

    ####        Functions       #####
    
    #converts the activity times from a list to objects
    #This helps in better using the power of OPP - Object Oriented Programming
    def listToObjects() :
        for i in range(len(startTimes)):
            activities[i].start = startTimes[i]
            activities[i].end = endTimes[i]
        print("converted ! \n\n")

    def sortActivities() :
        i = 0
        for activity in (sorted(activities, key=operator.attrgetter('end'))):
            sortActs[i].start = activity.start
            sortActs[i].end = activity.end
            i = i+1
        print("sorted ! \n\n")

    def printActivities(activs, length) :
        print("\nActivity: (startTime, endTime)")
        for i in range(length):
            print("Activity "+format(i+1)+": ("+format(activs[i].start)+", "+format(activs[i].end)+")")
        print("\n\n")

    def greedyAlgoFilter():
        global length
        #The first activity in the sorted list always goes to final list
        finalActs[0] = sortActs[0]
        for i in range(len(sortActs)-1):
            if(sortActs[i].end <= sortActs[i+1].start):
                finalActs[length] = sortActs[i+1]
                length = length+1
        print("Successfully applied !\n\n")



    #############       Main program        ############
    print("Idea: ")
    print("1. Sort activities according to their end time")
    print("2. Now compare endTime of ith activity with startTime of (i+1)th activity")
    print("3. Form a new list of non- overlapping tasks using above logic\n\n")

    print("Converting the activites from 2 lists notation to list of objects notation")
    print("This helps in better using the power of Python's OPP - Object Oriented Programming")
    listToObjects()

    print("Activity times (Before sorting)")
    printActivities(activities, len(activities))

    print("Sorting according to end time of the activities")
    sortActivities()

    print("Activity times (After sorting)")    
    printActivities(sortActs, len(sortActs))

    print("Applying Greedy activity selection by comparing startTime(i) and endTime(i-1)")
    print("Activity i passes the test if startTime(i) > endTime(i-1)")
    greedyAlgoFilter()

    print("The optimum list of activities after greedy selection are")  
    printActivities(finalActs, length)

    print("In this case Greedy alogrithm actually works")
    print("So, this is the best solution to the problem")
    
