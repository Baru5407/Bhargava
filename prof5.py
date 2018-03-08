def main():
   slips=slip()
   print("this is sliops",slips)
   prices=price()
   print(prices)
   calculate(slips,prices)
   
def slip():
   fp=open("slips.txt","r")
   s=fp.readlines()
   for i in range(0,len(s),1):
     s[i]=s[i].split()
   return s
def price():
    fp=open("price.txt","r")
    p=fp.readlines()
    for i in range(0,len(p),1):
      p[i]=p[i].split()
    return p
def calculate(slips,prices):
    product1=0
    found=True
    #product2=0
    #product3=0
    #product4=0
    for i in range(0,len(slips)):
      d=0
      #for j in range(0,len(slips),1):
    if(slips[i][0]==slips[i][0]):
        if(found=='True'):
           print(slips[i][0])
           if(slips[i][1]==slips[i][1]):
            print(slips[i][2])
            #print(d)
    product1=0
    
        



main()
