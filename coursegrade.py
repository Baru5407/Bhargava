def main():
   d= CourseGrad()
   f=StudentGrade()
   print(d)
   print(f)
   g=course(d,f)
   #tr(d)
   #gradavg(g)
   #print("sum is:",g)
   #averageData(d)


def averageData(Lst):
  avg = 0
  print("list: ", Lst)
  for i in range(0, len(Lst), 1):
    for j in range(1, len(Lst), 1):
         avg += int(Lst[i][j])
    print("Avg: ", avg/len(Lst))
    avg = 0
   
def CourseGrad():
    fp=open("coursegrade.txt","r")
    coursegrade=fp.readlines()
    for i in range(len(coursegrade)):
     coursegrade[i]=coursegrade[i].split()
     
    return coursegrade
def StudentGrade():
    fp=open("studentgrade.txt","r")
    studentrecord=fp.readlines()
    for i in range(len(studentrecord)):
        studentrecord[i]=studentrecord[i].split()
    return studentrecord
def course(list,list1):
    newList = []
    count=0
    for i in  range(0,len(list),1):
     sum=0
     for j in range(1,len(list),1): 
         sum=sum+int(list[i][j])
         
         avg=sum/(len(list)-1)
     
     if(avg>=90):
         grd = "A"
     elif(avg>=80):
         grd = "B"
     elif(avg>=70):
         grd = "C"
     else:
         grd = "D"
     #print("%s %s\t%.1f\t%s" % (list[i][0], getName(list1, list[i][0]), avg, grd))
     newList.append([list[i][0], getName(list1, list[i][0]), avg, grd])
     avg=0
    
    #print(newList)
    newList = sorted(newList,key=lambda new: new[2], reverse=True)
    print(newList)
    fout=open("course.txt","w")
    for i in range(0, len(newList)):
       thisLine = str("%s %s\t%.1f\t%s\n" % (newList[i][0], newList[i][1], newList[i][2], newList[i][3]))
       fout.write(thisLine)
    fout.close()
    m=credithours(list,list1,newList)
    print(m)
    gpa(newList,m,list1)
def getName(ls, id):
   for i in range(0, len(ls)):
      if id == ls[i][0]:
         return ls[i][1]
   return "NO NAME FOUND"
def credithours(list,list1,nl):
   #sum=3
   bh=0
   final=[]
   print(nl)
   #for i in range (0,len(list1),1):
   #sum=3
   for i in range(0,len(list1),1):
    sum=3
    tookClass = False
    for j in range(0,len(nl),1):
     if(list1[i][0]==nl[j][0]):
        #if(list[i][0]==list1[j][0]):
         sum=sum+int(list1[i][2])
        #print(sum)
        
         #print(nl[j][0],list1[i][1],sum)
         tookClass = True
         final.append([nl[j][0],list1[i][1],sum])
         gpa(list,list1,nl,final,sum)
         break
    if(not tookClass):
         final.append([list1[i][0],list1[i][1],list1[i][2]])
   return final
def gpa(list,list1,nl,final,sum):
   for i in range(0,len(list1),1):
    print(list1[i][3])
    for j in range (0,len(nl),1):
     if(nl[j][3]=='A'):
         bh=int(list1[i][2])*float(list1[i][3])+3*(4.0)
         bh=bh/sum
         print("gpa is ",bh)
     elif((nl[j][3]=='B')):
         bh=int(list1[i][2])*float(list1[i][3])+3*(3.0)
         bh=bh/sum
         print("gpa is ",bh)
     elif((nl[j][3]=='C')):
         bh=int(list1[i][2])*float(list1[i][3])+3*(2.0)
         bh=bh/sum
         print("gpa is ",bh)
     else:
         bh=int(list1[i][2])*float(list1[i][3])+3*(1.0)
         bh=bh/sum
         print("gpa is ",bh)
    
     
      
   
   
        
main()
