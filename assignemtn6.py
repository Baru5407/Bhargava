def main():
    
    fp=open("coursegrade.txt","r")
    d=fp.readlines()
    for i in range(len(d)):
     d[i]=d[i].split()
    print(d)
    cal(d)
    tr(d)
def cal(d):
    sum=0
    count=0
    for i in range(1,len(d)):
     for j in range(1,len(d)):
        
         sum+=int(d[0][j])
         print("sum is",sum)
         count+=1
         sum=sum/count
         print("for loop",sum)
         break
    #sum=sum/count
    #print("sum is",sum)
def tr(list):
      sum=sum(list)
      print("this is :",sum)

        
        
     
    
main()
