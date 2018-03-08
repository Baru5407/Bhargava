def main():
   prices = price()
   slips=slip()
   prices=price()
   calculate(slips,prices)
   
def slip():
   fp=open("slips.txt","r")
   s=fp.readlines()
   for i in range(0,len(s),1):
     s[i]=s[i].split()
   fp.close()
   return s
def price():
    fp=open("price.txt","r")
    p=fp.readlines()
    for i in range(0,len(p),1):
      p[i]=p[i].split()
    fp.close()
    return p
def calculate(slips,prices):
    out1 = []
    out2 = [0,0,0,0]
    for i in range(0, len(slips)):
      thisSlip = slips[i]
      spot = getSalesman(thisSlip[0], out1) 
      price = getProdPrice(thisSlip[1], prices) * int(thisSlip[2])
      out2[int(thisSlip[1]) - 1] += int(thisSlip[2])
      if(spot == -1):
        out1.append([thisSlip[0],0,0,0,0,0])
        #print(out1)
      out1[spot][int(thisSlip[1])] += int(thisSlip[2])
      #print(out1[spot])
      out1[spot][5] += price
      print(out1[spot][5])
    #done
    firstOut = open("salespersonPerformance.txt", "w")
    for i in range(0, len(out1)):
      firstOut.write(str.format("%s\t%d\t%d\t%d\t%d\t%d\n" % (out1[i][0], out1[i][1], out1[i][2], out1[i][3], out1[i][4], out1[i][5])))
    firstOut.close()
    secondOut = open("salability.txt", "w")
    for i in range(0, len(out2)):
      secondOut.write(str.format("%d\t%d\t%d\n" % (i+1, out2[i], int(out2[i]) * getProdPrice(str(i+1), prices))))
    secondOut.close()
			
			
def getProdPrice(num, prices):
  for i in range(0, len(prices)):
    if(num == prices[i][0]):
      return float(prices[i][1])
  return -1
	
def getSalesman(id, salesmen):
  for i in range(0, len(salesmen)):
    if(id == salesmen[i][0]):
      return i
  return -1
        
main()
