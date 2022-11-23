library(Rcpp)
sourceCpp("/home/david/CLionProjects/RQuaternion/RQuaternion.cpp")

paste("------------- Constructors --------------------")
y <- new(Quaternion,c(1,2,3,4))
x <- CreateIdentity()
x$data
y$data

paste("---------- Data Setters and Getters-----------")
x$data
x$data <- c(1,2,3,4)
x$data

paste("------------- Operations -----------------")
y <-Conjugate(y)
y$GetData()

y <-Inverse(y)
y$GetData()

a <-LerpUnclamped(x,y,0.5)
a$GetData()

z <- Lerp(x,y,0.5)
z$GetData()

Rotate <-RotateTowards(x,y,0.325)
Rotate$GetData()

b <- SlerpUnclamped(y,z,0.55)
b$GetData()

c <- Slerp(b,y,477)
c$GetData()