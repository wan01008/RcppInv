#include <RcppEigen.h>

// [[Rcpp::depends(RcppEigen)]]

using Eigen::MatrixXd;                      // LDLt decomposition function
using Eigen::VectorXd;

// [[Rcpp::export]]
MatrixXd diag_mul(MatrixXd &m, VectorXd &d) {
    MatrixXd B = d.asDiagonal() * m;
    return(B);
}