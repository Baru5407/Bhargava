import sys
def main():
   readfunction()
   
def readfunction():
    d=[]
    fp1=open(input("Enter file 1: "),"r")
    fp3=open(input("Enter file 2: "),"r")
    d+=fp1.readlines()
    d+=fp3.readlines()
    fp1.close
    fp3.close
    print(d)
   
    

main()
