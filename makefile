#Variables                                                                         
.RECIPEPREFIX = >                                                                  
                                                                                   
SHELL=bash                                                                         
MAKEFLAGS += --no-builtin-rules                                                    
                                                                                  
CXX = g++                                                                          
CFLAGS =-Wall -Wextra -g                                                           
                            
                                                                                   
#Rules                                                                             
main: main.o listen.o                                                                                                                                 
> $(CXX) $(CFLAGS) -o main main.o listen.o                                         
                                                                                   
main.o: main.cpp listen.h                                                    
> $(CXX) $(CFLAGS) -c main.cpp                                                     
                                                                                   
listen.o:                                                                          
> ${CXX} listen.cpp -c -o listen.o      

clean:
> rm  main main.o listen.o                                                                       
