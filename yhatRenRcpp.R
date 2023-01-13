library(Rcpp)
library(RcppEigen)
library(data.table)

setwd("/home/panwei/shared/LSimputedHDLtrait/")

loadRData <- function(fileName){
#loads an RData file, and returns it
    load(fileName)
    get(ls()[ls() != "fileName"])
}

#snp <- fread("snptest_select500.csv")
snp <- loadRData("batchsize20000/snptest1.RData")
snp <- apply(snp, 2, function(x) {scale(x, scale = F)})
#print(mean(snp[, 1]))
#print(sd(snp[, 1]))
#snp <- as.data.frame(snp)
p <- dim(snp)[2]

res <- replicate(p, NA)
for (i in 1:p){
    c <- snp[, i]
    cp <- t(c) %*% c
    res[i] <- 1/cp
}
sourceCpp("DiagMul.cpp")
#res1 <- diag(res)
#cxt <- res1 %*% t(snp)
cxt <- diag_mul(t(snp), res)
saveRDS(t(cxt), "X.RData")
print(mean(t(cxt)[, 1]))
print(sd(t(cxt)[, 1]))

##Use proper funciton to load GWAS summary statistics
beta <- read.table("batchsize20000/Summary statistics/betafinal.txt")
 
xxt <- t(cxt) %*% cxt
saveRDS(xxt, "XXt.RData")

t <- Sys.time()

sourceCpp("/home/panwei/wan01008/RcppInv/InvSparse.cpp")

xxtinv <- inv_LDLT_sparse(xxt)

print(Sys.time() - t)
saveRDS(xxtinv, "XXtInv.RData")

reg <- xxtinv %*% t(cxt)

yhat <- reg %*% as.matrix(beta)
##end recording time

##use proper function to save the result
saveRDS(yhat, "yhat.RData")
