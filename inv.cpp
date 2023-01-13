#include <RcppEigen.h>

// [[Rcpp::depends(RcppEigen)]]

// A function to conduct LDLt decomposition of (sparse) matrix M, then find the inverse


using Eigen::Map;                       // 'maps' rather than copies
using Eigen::MatrixXd;                  // variable size matrix, double precision
using Eigen::VectorXd;                  // variable size vector, double precision
using Eigen::LDLT;                      // LDLt decomposition function

// [[Rcpp::export]]
MatrixXd getInverse(Map<MatrixXd> M) {
    LDLT<MatrixXd> ldlt(M);          // Compute the LDLt decomposition of M
    ldlt.compute(M);
    if (ldlt.info() != Eigen::Success){
        std::cout << "Factorization not successful, ignore the result";
    }
    MatrixXd b = MatrixXd::Identity(M.rows(), M.cols());
    return ldlt.solve(b);
}