#include <RcppEigen.h>
#include <Rcpp.h>

// [[Rcpp::depends(RcppEigen)]]

using Eigen::SimplicialLDLT;                // SimplicialLDLT decomposition function
using Eigen::MatrixXd;                  // variable size matrix, double precision
//using Eigen::SparseMatrix;       
// LDLt decomposition function
//using Eigen::VectorXd;
//typedef Eigen::Map<Eigen::MatrixXd> MapMatd; // Input: must be double

// [[Rcpp::export]]
MatrixXd inv_LDLT_sparse(MatrixXd &Vi) {
    typedef Eigen::SparseMatrix<double, Eigen::ColMajor, long long> SpMat;
    SpMat ViSp = Vi.sparseView(0.1, 0.5); //the paper filter out all matrix entries smaller than 0.05
    SimplicialLDLT<SpMat> ldlt(ViSp);
    // Check if LDLT factorization successfully completed
    if (ldlt.info() != Eigen::Success){
        std::cout << "Factorization not successful, ignore the result";
        //Add small lambda
        //ViSp.diagonal().array() += 1e-6;
        typedef Eigen::Triplet<double> T;
        std::vector<T> tripletList;
        tripletList.reserve(Vi.rows());
        for (int i = 0; i < ViSp.rows(); i++)
            tripletList.push_back(T(i,i,1e-6));
        SpMat DiagSp(ViSp.rows(), ViSp.rows());
        DiagSp.setFromTriplets(tripletList.begin(), tripletList.end());
        ViSp = ViSp + DiagSp;
        //std::cout << ViSp;
        SimplicialLDLT<SpMat> ldlt(ViSp);
    }
    if (ldlt.info() != Eigen::Success){
        std::cout << "Factorization not successful, ignore the result";
        //return()
    }
    ViSp.setIdentity();
    MatrixXd M = ldlt.solve(ViSp);
    //Rcpp::S4 Xout(Rcpp::wrap(ViSp));                      // Output: as S4 object
    return(M);
}