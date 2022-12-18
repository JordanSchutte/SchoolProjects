import re
import string
from collections import Counter # imported to count frequency of words in file                              

def read_File():
    ticket = open("project_three_input_file.txt") #creates object that opens text file
    products = ticket.read().split() #creates object that holds each line info from ticket object
    
    uniqueProduct = sorted(set(products))

    for word in uniqueProduct:
        print("----------------------")
        print("\n")
        print(word, " : ",products.count(word))
        print("\n")
        print("----------------------")
    

    ticket.close() #closes ticket object to prevent memory issues

def locate_Total_Product_Amount(v):#Takes a string from C++ user input
    ticket = open("CS210_Project_Three_Input_File")
    products = ticket.read().split() #creates object that holds each line info from ticket object
    uniqueProduct = sorted(set(products)) #sorts the items
    ticket.close() #closes ticket object to prevent memory issues

    tot = 0 #number to be sent back to C++
    totInventory = 0 #counts amount of times loop iterates --  used to determine if item not 

    for word in uniqueProduct: #finds the element in unique_Product that is the requested string from user
        tempString = word
        totInventory += 1
        if (tempString == v):
            tot = products.count(word)
        if (tempString != v and totInventory == len(uniqueProduct)):
            return -1 # this determined that item from user input was not present in file
    return tot

def read_AND_Write_File():
    ticket = open("CS210_Project_Three_Input_File")
    data = open("frequency.dat", "w")
    products = ticket.read().split() #creates object that holds each line info from ticket object
    uniqueProduct = sorted(set(products)) #sorts the items

    #writes the data to the .dat file
    for word in uniqueProduct:
        data.write(word)
        data.write(" ")
        data.write(str(products.count(word)))
        data.write("\n")
    
    data.close() #close file

    histoData = open("frequency.dat", "r") # read .dat file
    productData = histoData.readlines() # read lines so each product is matches with frequency amount


    #temp variables used for nested for loops
    tempFreq = 0
    tempProduct = ""

    #reads and prepares data from .dat file for histogram
    for line in productData:
        tempInt = 0
        tempString = line.split() #splits product name and frequency
        for word in tempString:
            tempInt += 1
            if (tempInt == 1):
                tempProduct = word #product
                print(tempProduct, end = " ")
            if (tempInt == 2):
                tempFreq = int(word) #frequency of product
        

        #creates Histogram
        for i in range(tempFreq):
            print("+", end = "")
        print("\n")
        print("------------------------------------")
        print("\n")
