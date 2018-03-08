def main():
   
    
    print("main menu:\n  Welcome to the Python Movie Database!Main menu:\n 1: display all movies \n 2:  display shortest movie \n 3:  display longest movie \n 4:  display oldest movie \n 5:  display newest movie \n  6:  display movies by rating \n 0:  quit the program")
    optiom=int(input("main menu:enter ur choice"))
    movies=populateMovies()  
    for i in range(len(movies)):
      movies[i]=movies[i].split(",")
      #print("hi:",movies[i])
    options(optiom,movies)
    
def populateMovies():
    fp=open("movies.txt","r")
    d=fp.readlines()
    return d
def options(option,movies):
    
    while(option!=0):
        if(option==1):
            one(movies)
        elif(option==2):
            two(movies)
        elif(option==3):
            three(movies)
        elif(option==4):
            four(movies)
        elif(option==5):
            five(movies)
        else:
            six(movies)
        print("main menu:\n  Welcome to the Python Movie Database!Main menu:\n 1: display all movies \n 2:  display shortest movie \n 3:  display longest movie \n 4:  display oldest movie \n 5:  display newest movie \n  6:  display movies by rating \n 0:  quit the program")
        option=int(input("main menu:enter ur choice"))
        

def one(movies):
      print("list of movies:",movies)
def two(movies):
      if(movies[0][3]<movies[1][3] and movies[0][3]<movies[2][3]):
        print("shortest movie is:",movies[0][0])
      elif(movies[1][3]<movies[2][3] and movies[0][3]<movies[1][3] ):
        print("shortest movie is:",movies[1][0])
      else:
        print("shortest movie is:",movies[2][0])
def three(movies):
      if(movies[0][3] > movies[1][3] and movies[0][3]>movies[2][3]):
        print("longest movie is:",movies[0][0])
      elif(movies[1][3]>movies[2][3] and movies[1][3]>movies[0][3] ):
        print("longest movie is:",movies[1][0])
      else:
        print("longest movie is:",movies[2][0])
def four(movies):
      if(movies[0][2]<movies[1][2] and movies[0][2]<movies[2][2]):
        print("oldest movie is:",movies[0][1])
      elif(movies[1][2]<movies[2][2] and movies[0][2]<movies[1][2] ):
        print("oldest movie is:",movies[1][0])
      else:
        print("oldest movie is:",movies[2][0])
def five(movies):
      if(movies[0][2]>movies[1][2] and movies[0][2]>movies[2][2]):
        print("newest movie is:",movies[0][0])
      elif(movies[1][2]>movies[2][2] and movies[0][2]>movies[1][2] ):
        print("newest movie is:",movies[1][0])
      else:
        print("newest movie is:",movies[2][0])
def six(movies):
      userrating=input("enter user rating")
      print(userrating)
      for i in range(len(movies)):
        if(userrating==movies[i][4]):
                print(movies[i])

        
      


main()
