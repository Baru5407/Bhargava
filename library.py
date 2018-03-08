def main():
    mem=members()
    print("this is mem:",mem)
    invent=inventory()
    print(invent)
    checkou=checkout()
    print(checkou)
    newcheckout(mem,invent,checkou)
    membernew(mem,invent,checkou)
def members():
    fp=open("members.txt","r")
    member=fp.readlines()
    for i in range(0,len(member),1):
        member[i]=member[i].split()
    return member
def inventory():
    fp=open("inventory.txt","r")
    inven=fp.readlines()
    for i in range(0,len(inven),1):
        inven[i]=inven[i].split()
    return inven
def checkout():
     fp=open("checkout.txt","r")
     check=fp.readlines()
     for i in range(0,len(check),1):
         check[i]=check[i].split()
     return check
def newcheckout(mem,invent,checkou):
     d=0
     for i in range(0,len(mem),1):
      for j in range(0,len(invent),1):
       for k in range(1,len(checkou),1):
           if(checkou[0][0]==mem[i][0]):
            if(checkou[k][0]==invent[j][0]):
                if(int(invent[j][1])<3):
                    print("non checked items:",invent[j][3],invent[j][0])
                   
                else:
                     print("checked items\n",invent[j][3],invent[j][0])
                d=0

def membernew(mem,invent,checkou):
    sum=0
    for i in range(0,len(mem),1):
      #print(checkou[i])
      for j in range(0,len(invent),1):
       for k in range(1,len(checkou),1):
        
        if(checkou[k][0]==invent[j][0]):
         #print("hello")
         if(checkou[0][0]==mem[i][0]):
          #print("hello")
          if(int(invent[j][1])<3):   
                
                if(invent[j][2]=='C'):
                  
                  
                  sum=int(mem[i][2])+int(invent[j][1])
                  print( sum)
                elif(invent[j][2]=='D'):
                  print("hello")
                  
                  sum=int(mem[i][3])+int(invent[j][1])
                  print(sum)
                else:
                  sum=int(mem[i][4])+int(invent[j][1])
                  
                  print(sum)
                sum=0
                
             
               







main()
