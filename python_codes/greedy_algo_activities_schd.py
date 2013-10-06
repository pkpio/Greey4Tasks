# -*- coding: utf-8 -*-
"""
Author  : Praveen Kumar
Created : 05/10/2013
Project : EE 677: VLSI CAD course project - Greedy Algorithm for Activity scheduling
Github  : https://github.com/praveendath92/EE-677_project
"""
from array import array

startTimes = array('l', [1,2,3])

class activity:
    def __init__(self):
        self.start = 0
        self.end = 0

def addTwo(a,b) :
    c = a+b
    return c
#End of function definition

activities =  [ activity() for i in range(29)]

a = 2
b = 3
c = addTwo(a,b)
print(c)
