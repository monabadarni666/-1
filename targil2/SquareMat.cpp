// Email: badarnimona2@gmail.com

#include "SquareMat.hpp"
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <sstream>

namespace matrix_ops {

//==============================================================================
// CONSTRUCTORS & DESTRUCTOR
//==============================================================================

SquareMat::SquareMat() : elements(nullptr), dimension(0) {
    // Empty matrix constructor
}

SquareMat::SquareMat(unsigned int dim) : elements(nullptr), dimension(dim) {
    init();
}

SquareMat::SquareMat(unsigned int dim, double initialValue) : elements(nullptr), dimension(dim) {
    init();
    
    // Fill with initial value
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            elements[i][j] = initialValue;
        }
    }
}

SquareMat::SquareMat(const SquareMat& other) : elements(nullptr), dimension(0) {
    copyFrom(other);
}

SquareMat::~SquareMat() {
    cleanup();
}

//==============================================================================
// PRIVATE HELPER METHODS
//==============================================================================

void SquareMat::init() {
    if (dimension == 0) {
        elements = nullptr;
        return;
    }
    
    // Allocate memory for rows
    elements = new double*[dimension];
    
    // Allocate memory for columns and initialize to zero
    for (unsigned int i = 0; i < dimension; i++) {
        elements[i] = new double[dimension]();  // () initializes to zero
    }
}

void SquareMat::cleanup() {
    if (elements) {
        for (unsigned int i = 0; i < dimension; i++) {
            delete[] elements[i];
        }
        delete[] elements;
        elements = nullptr;
    }
}

void SquareMat::copyFrom(const SquareMat& source) {
    // Clean up existing data if any
    cleanup();
    
    // Copy dimension
    dimension = source.dimension;
    
    // Allocate new memory
    init();
    
    // Copy elements
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            elements[i][j] = source.elements[i][j];
        }
    }
}

double SquareMat::calculateDeterminant() const {
    // Handle special cases
    if (dimension == 0) {
        return 0.0;
    }
    
    if (dimension == 1) {
        return elements[0][0];
    }
    
    if (dimension == 2) {
        return elements[0][0] * elements[1][1] - elements[0][1] * elements[1][0];
    }
    
    // For larger matrices, use cofactor expansion along the first row
    double det = 0.0;
    int sign = 1;
    
    for (unsigned int j = 0; j < dimension; j++) {
        // Create a submatrix by removing first row and current column
        SquareMat subMatrix(dimension - 1);
        
        for (unsigned int row = 1; row < dimension; row++) {
            unsigned int subCol = 0;
            
            for (unsigned int col = 0; col < dimension; col++) {
                if (col == j) continue;  // Skip the current column
                
                subMatrix[row - 1][subCol] = elements[row][col];
                subCol++;
            }
        }
        
        // Add this term to the determinant
        det += sign * elements[0][j] * subMatrix.calculateDeterminant();
        
        // Alternate sign for next cofactor
        sign = -sign;
    }
    
    return det;
}

SquareMat SquareMat::createIdentity() const {
    SquareMat identity(dimension);
    
    for (unsigned int i = 0; i < dimension; i++) {
        identity.elements[i][i] = 1.0;
    }
    
    return identity;
}

//==============================================================================
// ASSIGNMENT OPERATOR
//==============================================================================

SquareMat& SquareMat::operator=(const SquareMat& other) {
    if (this != &other) {
        copyFrom(other);
    }
    return *this;
}

//==============================================================================
// ACCESSOR METHODS
//==============================================================================

unsigned int SquareMat::getDimension() const {
    return dimension;
}

double SquareMat::getSum() const {
    double sum = 0.0;
    
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            sum += elements[i][j];
        }
    }
    
    return sum;
}

//==============================================================================
// ROW ACCESS IMPLEMENTATION
//==============================================================================

SquareMat::Row::Row(double* rowPtr, unsigned int size) : rowData(rowPtr), rowSize(size) {
}

double& SquareMat::Row::operator[](unsigned int col) {
    if (col >= rowSize) {
        throw std::out_of_range("Column index out of range");
    }
    return rowData[col];
}

const double& SquareMat::Row::operator[](unsigned int col) const {
    if (col >= rowSize) {
        throw std::out_of_range("Column index out of range");
    }
    return rowData[col];
}

SquareMat::Row SquareMat::operator[](unsigned int row) {
    if (row >= dimension) {
        throw std::out_of_range("Row index out of range");
    }
    return Row(elements[row], dimension);
}

const SquareMat::Row SquareMat::operator[](unsigned int row) const {
    if (row >= dimension) {
        throw std::out_of_range("Row index out of range");
    }
    return Row(elements[row], dimension);
}

//==============================================================================
// BASIC ARITHMETIC OPERATORS
//==============================================================================

SquareMat SquareMat::operator+(const SquareMat& rhs) const {
    if (dimension != rhs.dimension) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    
    SquareMat result(dimension);
    
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            result.elements[i][j] = elements[i][j] + rhs.elements[i][j];
        }
    }
    
    return result;
}

SquareMat SquareMat::operator-(const SquareMat& rhs) const {
    if (dimension != rhs.dimension) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }
    
    SquareMat result(dimension);
    
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            result.elements[i][j] = elements[i][j] - rhs.elements[i][j];
        }
    }
    
    return result;
}

SquareMat SquareMat::operator-() const {
    SquareMat result(dimension);
    
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            result.elements[i][j] = -elements[i][j];
        }
    }
    
    return result;
}

SquareMat SquareMat::operator*(const SquareMat& rhs) const {
    if (dimension != rhs.dimension) {
        throw std::invalid_argument("Matrix dimensions must match for multiplication");
    }
    
    SquareMat result(dimension);
    
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            // Calculate dot product of row i and column j
            double sum = 0.0;
            for (unsigned int k = 0; k < dimension; k++) {
                sum += elements[i][k] * rhs.elements[k][j];
            }
            result.elements[i][j] = sum;
        }
    }
    
    return result;
}

SquareMat SquareMat::operator*(double scalar) const {
    SquareMat result(dimension);
    
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            result.elements[i][j] = elements[i][j] * scalar;
        }
    }
    
    return result;
}

SquareMat operator*(double scalar, const SquareMat& mat) {
    return mat * scalar;  // Reuse existing matrix * scalar operation
}

SquareMat SquareMat::operator%(const SquareMat& rhs) const {
    if (dimension != rhs.dimension) {
        throw std::invalid_argument("Matrix dimensions must match for element-wise multiplication");
    }
    
    SquareMat result(dimension);
    
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            result.elements[i][j] = elements[i][j] * rhs.elements[i][j];
        }
    }
    
    return result;
}

SquareMat SquareMat::operator%(int modulo) const {
    SquareMat result(dimension);
    
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            result.elements[i][j] = static_cast<double>(static_cast<int>(elements[i][j]) % modulo);
        }
    }
    
    return result;
}

SquareMat SquareMat::operator/(double divisor) const {
    if (std::abs(divisor) < 1e-10) {
        throw std::invalid_argument("Division by zero");
    }
    
    SquareMat result(dimension);
    
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            result.elements[i][j] = elements[i][j] / divisor;
        }
    }
    
    return result;
}

SquareMat SquareMat::operator^(int exponent) const {
    if (exponent < 0) {
        throw std::invalid_argument("Negative exponents not supported");
    }
    
    if (dimension == 0) {
        throw std::invalid_argument("Cannot raise empty matrix to a power");
    }
    
    // Special case: power = 0 returns identity matrix
    if (exponent == 0) {
        return createIdentity();
    }
    
    // Special case: power = 1 returns the matrix itself
    if (exponent == 1) {
        return *this;
    }
    
    // Binary exponentiation for efficiency
    if (exponent % 2 == 0) {
        // A^(2n) = (A^n)^2
        SquareMat half = (*this) ^ (exponent / 2);
        return half * half;
    } else {
        // A^(2n+1) = A * (A^n)^2
        SquareMat half = (*this) ^ (exponent / 2);
        return (*this) * half * half;
    }
}

//==============================================================================
// INCREMENT/DECREMENT OPERATORS
//==============================================================================

SquareMat& SquareMat::operator++() {
    // Pre-increment: adds 1 to all elements
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            elements[i][j] += 1.0;
        }
    }
    return *this;
}

SquareMat SquareMat::operator++(int) {
    // Post-increment: return original, then increment
    SquareMat original(*this);
    ++(*this);
    return original;
}

SquareMat& SquareMat::operator--() {
    // Pre-decrement: subtracts 1 from all elements
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            elements[i][j] -= 1.0;
        }
    }
    return *this;
}

SquareMat SquareMat::operator--(int) {
    // Post-decrement: return original, then decrement
    SquareMat original(*this);
    --(*this);
    return original;
}

//==============================================================================
// SPECIAL OPERATIONS
//==============================================================================

SquareMat SquareMat::operator~() const {
    // Transpose operation
    SquareMat result(dimension);
    
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            result.elements[i][j] = elements[j][i];
        }
    }
    
    return result;
}

double SquareMat::operator!() const {
    // Determinant calculation
    return calculateDeterminant();
}

//==============================================================================
// COMPOUND ASSIGNMENT OPERATORS
//==============================================================================

SquareMat& SquareMat::operator+=(const SquareMat& rhs) {
    if (dimension != rhs.dimension) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            elements[i][j] += rhs.elements[i][j];
        }
    }
    
    return *this;
}

SquareMat& SquareMat::operator-=(const SquareMat& rhs) {
    if (dimension != rhs.dimension) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }
    
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            elements[i][j] -= rhs.elements[i][j];
        }
    }
    
    return *this;
}

SquareMat& SquareMat::operator*=(const SquareMat& rhs) {
    *this = *this * rhs;
    return *this;
}

SquareMat& SquareMat::operator*=(double scalar) {
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            elements[i][j] *= scalar;
        }
    }
    
    return *this;
}

SquareMat& SquareMat::operator%=(const SquareMat& rhs) {
    if (dimension != rhs.dimension) {
        throw std::invalid_argument("Matrix dimensions must match for element-wise multiplication");
    }
    
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            elements[i][j] *= rhs.elements[i][j];
        }
    }
    
    return *this;
}

SquareMat& SquareMat::operator%=(int modulo) {
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            elements[i][j] = static_cast<double>(static_cast<int>(elements[i][j]) % modulo);
        }
    }
    
    return *this;
}

SquareMat& SquareMat::operator/=(double divisor) {
    if (std::abs(divisor) < 1e-10) {
        throw std::invalid_argument("Division by zero");
    }
    
    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension; j++) {
            elements[i][j] /= divisor;
        }
    }
    
    return *this;
}

//==============================================================================
// COMPARISON OPERATORS
//==============================================================================

bool SquareMat::operator==(const SquareMat& rhs) const {
    // Matrices are equal if the sum of their elements is the same
    return std::abs(getSum() - rhs.getSum()) < 1e-10;
}

bool SquareMat::operator!=(const SquareMat& rhs) const {
    return !(*this == rhs);
}

bool SquareMat::operator<(const SquareMat& rhs) const {
    return getSum() < rhs.getSum();
}

bool SquareMat::operator>(const SquareMat& rhs) const {
    return getSum() > rhs.getSum();
}

bool SquareMat::operator<=(const SquareMat& rhs) const {
    return getSum() <= rhs.getSum();
}

bool SquareMat::operator>=(const SquareMat& rhs) const {
    return getSum() >= rhs.getSum();
}

//==============================================================================
// OUTPUT OPERATOR
//==============================================================================

std::ostream& operator<<(std::ostream& os, const SquareMat& mat) {
    for (unsigned int i = 0; i < mat.dimension; i++) {
        os << "[";
        for (unsigned int j = 0; j < mat.dimension; j++) {
            os << std::fixed << std::setprecision(2) << mat.elements[i][j];
            
            if (j < mat.dimension - 1) {
                os << ", ";
            }
        }
        os << "]";
        
        if (i < mat.dimension - 1) {
            os << std::endl;
        }
    }
    
    return os;
}

} // namespace matrix_ops
