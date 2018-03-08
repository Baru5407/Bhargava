def main():
    a=customer()
    print(a)
    b=products()
    print(b)
    c=orders()
    print(c)
    c=manupulation(a,b,c)
    print(c)
    output(c)
    #print(g)
   
  
def customer():
    fp=open("customers.txt","r")
    d=fp.readlines()
    for i in range(len(d)):
       d[i]=d[i].split()
    return d
def products():
    fp=open("products.txt","r")
    product=fp.readlines()
    for i in range(len(product)):
     product[i]=product[i].split()
    return product
def orders():
    fp=open("orders.txt","r")
    order=fp.readlines()
    for i in range(len(order)):
      order[i]=order[i].split()
    return order
def manupulation(list1,list2,list3):
    discounted=0
    cours=[]
    d=0
    
    for i in range(0,len(list1),1):
     for j in range(0,len(list3),1):
      for k in range(0,len(list2),1):
       quantity=float(list2[k][2])*int(list3[j][2])
       if(list1[i][2]=='YES'):
        d=quantity*0.10
       discounted = quantity - d
       if (list1[i][0]) == (list3[j][0]) and (list3[j][1]==list2[k][0]):   
        cours.append([list1[i][1], list2[k][1],list2[k][2],list3[j][2],discounted,d])
       discount=0
       d=0
    return cours
def output(cours):
   fout=open("a.txt","w")
   for i in range(0,len(cours),1):
    thisLine = str("%s\t %s\t%s\t%s\t%.lf\t%.lf\n" % (cours[i][0], cours[i][1], cours[i][2], cours[i][3],cours[i][4],cours[i][5]))
    fout.write(thisLine)
   fout.close()
  
   b=0
   f=[]
   k=[]
   
   cours = sorted(cours,key=lambda new: new[2], reverse=True)
   print(cours)
   for i in range(0, len(cours)):
      spot = -1
      for j in range(0, len(f)):
         if(cours[i][0] == f[j][0]):
            spot = j
            break
      if(spot == -1):
         f.append([cours[i][0],cours[i][4]])
      else:
         f[j][1] += cours[i][4]
      spot = -1
   print(f)
   

    
     
main()
