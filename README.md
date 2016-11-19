#Multivariate linear regression in C

This implements the gradient descent algorithm. Not really production ready in any way and far from optimal, but makes it easy to see what's going on.

##Build

  make

##Usage

  ./lreg.o sam.csv 0.001 1


  - sam.csv - source file
  - 0.001 - learning rate (alpha)
  - 1 - number of features
