# RcppInv
Code and primary results for inversing large sparse matrix using Rcpp

**inv.cpp**: the C++ function for inverting large matrix using Rcpp LDLT (https://eigen.tuxfamily.org/dox/classEigen_1_1LDLT.html)

**InvSparse.cpp**: the C++ function for inverting large matrix using sparse cholesky decomposition Simplicial LDLT (https://eigen.tuxfamily.org/dox/classEigen_1_1SimplicialLDLT.html). As described in Results-overview of the method part in https://www.nature.com/articles/s41588-021-00954-4 , the GRM with all the small off-diagonal elements (for example, those <0.05) set to zero.

**yhatRenRcpp.R**: Jingchen's R code for getting yhat with the inverse function replaced with Rcpp sparse inverse function.

**DiagMul.cpp**: the C++ function based on Rcpp for matrix multiplication (diagonal matrix with a regular one), which is used in one part of **yhatRenRcpp.R** to save the running time. 
