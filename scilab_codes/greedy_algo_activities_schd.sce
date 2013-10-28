//Author    : Praveen Kumar Pendyala
//Created   : 5th Oct.,2013
//Project   : EE 677: VLSI CAD course project - Greedy Algorithm for Activity scheduling
//Github    : https://github.com/praveendath92/EE-677_project

clc
clear
global startTime;
global endTime;

global fStartTime;  //Final list of activities start times
global fEndTime;    //Final list of activities end times
global fActsCount;  //Count of # of final activities

//Add activities here
//You may try copying more inputs in the comment into the array
startTime   = [0 2 4 3];   // 10 6 5 4 6 8 9 11 10 8 1 2 3 6 8 -More inputs
endTime     = [2 3 6 5];   // 11 7 9 7 10 10 10 13 11 13 11 6 13 14 18 -More inputs

if(size(startTime, 2) ~= size(endTime, 2))
    disp("Size mismatch !")
    disp("startTime and endTime matrix sizes should be same !")
    disp("Press CTRL+C to exit")
    while(1) end
end

//Initialising final activity time arrays and count
fStartTime = zeros(startTime);
fEndTime   = zeros(startTime);
fActsCount = 1;                 //# of final activities. Min is 1.

function swapVals(i, j)
    global startTime;
    global endTime;
    
    sTmp = startTime(i);    //Temperory variable for sorting. To hold startTime
    eTmp = endTime(i);      //Temperory variable for sorting. To hold endTime
    
    startTime(i) = startTime(j);
    endTime(i)  = endTime(j);
    
    startTime(j) = sTmp;
    endTime(j)  = eTmp;
endfunction


function sortByEndTime()
    global startTime;
    global endTime;
    
    curMin = endTime(1);    //Temp variable to hold min value
    curMinIn = 1;           //Index of the current minumum value
    
    for(i = 1 : size(endTime,2))
        curMin = endTime(i);
        curMinIn = i;
        for(j = i : size(endTime,2))
            if(endTime(j)<curMin)
                curMin = endTime(j);
                curMinIn = j;
            end
        end
        swapVals(i, curMinIn)
    end
endfunction


function displayActivities(sTime, eTime, dispSize)
    disp("Activity: (startTime, endTime)")
    for (i  = 1 :  dispSize)
        disp(string(i)+": ("+string(sTime(i))+", "+string(eTime(i))+")") 
    end
endfunction

function greedyActivitiesSelect()
    global startTime;
    global endTime;
    
    global fStartTime;
    global fEndTime;
    
    global fActsCount;
    
    //First activity in the sorted list will go to final list
    fStartTime(fActsCount) = startTime(1);
    fEndTime(fActsCount) = endTime(1);
    
    for(i = 1 : (size(startTime, 2)-1))
        if(endTime(i)<=startTime(i+1))
            fActsCount = fActsCount+1;
            fStartTime(fActsCount) = startTime(i+1);
            fEndTime(fActsCount) = endTime(i+1);
        end
    end
endfunction

//
//                      Main program begins
//

disp("Idea: ")
disp("1. Sort activities according to their end time")
disp("2. Now compare endTime of ith activity with startTime of (i+1)th activity")
disp("3. Form a new array of non- overlapping tasks using above logic")

disp("")
disp("Activity times (Before sorting)")
displayActivities(startTime, endTime, size(startTime,2))

disp("")
disp("Sorting according to end time of the activities")
sortByEndTime()

disp("")
disp("Activity times (After sorting)")
displayActivities(startTime, endTime, size(startTime,2))

disp("")
disp("Greedy activity selection by comparing startTime(i) and endTime(i-1)")
disp("Activity i passes the test if startTime(i) > endTime(i-1)")
greedyActivitiesSelect()

disp("")
disp("The optimum list of activities after greedy selection are")
displayActivities(fStartTime, fEndTime, fActsCount)


disp("In this case Greedy alogrithm actually works")
disp("So, this is the best solution to the problem")
