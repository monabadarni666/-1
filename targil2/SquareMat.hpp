
// Email: badarnimona2@gmail.com

#include <iostream>

// Matrix namespace containing all square matrix functionality
namespace matrix_ops {

/**
 * @class SquareMat
 * @brief A square matrix implementation with various mathematical operations
 */
class SquareMat {
public:
    // =================== CONSTRUCTORS & RULE OF THREE =================== 
    
    // Default constructor - creates an empty matrix
    SquareMat();
    
    // Size constructor - creates a matrix of specified size (filled with zeros)
    explicit SquareMat(unsigned int dim);
    
    // Value constructor - creates a matrix filled with a specified value
    SquareMat(unsigned int dim, double initialValue);
    
    // Copy constructor
    SquareMat(const SquareMat& other);
    
    // Destructor
    ~SquareMat();
    
    // Assignment operator
    SquareMat& operator=(const SquareMat& other);
    
    // =================== ARITHMETIC OPERATORS =================== 
    
    // Matrix addition
    SquareMat operator+(const SquareMat& rhs) const;
    
    // Matrix subtraction
    SquareMat operator-(const SquareMat& rhs) const;
    
    // Unary negation (unary minus)
    SquareMat operator-() const;
    
    // Matrix multiplication
    SquareMat operator*(const SquareMat& rhs) const;
    
    // Scalar multiplication (matrix * scalar)
    SquareMat operator*(double scalar) const;
    
    // Scalar multiplication (scalar * matrix) - friend function
    friend SquareMat operator*(double scalar, const SquareMat& mat);
    
    // Element-wise multiplication
    SquareMat operator%(const SquareMat& rhs) const;
    
    // Modulo with scalar
    SquareMat operator%(int modulo) const;
    
    // Division by scalar
    SquareMat operator/(double divisor) const;
    
    // Power operator - raises matrix to a specified power
    SquareMat operator^(int exponent) const;
    
    // =================== INCREMENT/DECREMENT OPERATORS =================== 
    
    // Pre-increment operator (++mat)
    SquareMat& operator++();
    
    // Post-increment operator (mat++)
    SquareMat operator++(int);
    
    // Pre-decrement operator (--mat)
    SquareMat& operator--();
    
    // Post-decrement operator (mat--)
    SquareMat operator--(int);
    
    // =================== SPECIAL OPERATIONS =================== 
    
    // Transpose operator - swaps rows and columns
    SquareMat operator~() const;
    
    // Determinant operator - calculates the determinant of the matrix
    double operator!() const;
    
    // =================== COMPOUND ASSIGNMENT OPERATORS =================== 
    
    // Addition assignment
    SquareMat& operator+=(const SquareMat& rhs);
    
    // Subtraction assignment
    SquareMat& operator-=(const SquareMat& rhs);
    
    // Matrix multiplication assignment
    SquareMat& operator*=(const SquareMat& rhs);
    
    // Scalar multiplication assignment
    SquareMat& operator*=(double scalar);
    
    // Element-wise multiplication assignment
    SquareMat& operator%=(const SquareMat& rhs);
    
    // Modulo with scalar assignment
    SquareMat& operator%=(int modulo);
    
    // Division by scalar assignment
    SquareMat& operator/=(double divisor);
    
    // =================== COMPARISON OPERATORS =================== 
    
    // Equality operator (based on sum of elements)
    bool operator==(const SquareMat& rhs) const;
    
    // Inequality operator
    bool operator!=(const SquareMat& rhs) const;
    
    // Less than operator (based on sum of elements)
    bool operator<(const SquareMat& rhs) const;
    
    // Greater than operator
    bool operator>(const SquareMat& rhs) const;
    
    // Less than or equal operator
    bool operator<=(const SquareMat& rhs) const;
    
    // Greater than or equal operator
    bool operator>=(const SquareMat& rhs) const;
    
    // =================== ACCESSING ELEMENTS =================== 
    
    // Proxy class for accessing elements as mat[i][j]
    class Row {
    public:
        Row(double* rowPtr, unsigned int size);
        
        // Access element (modifiable)
        double& operator[](unsigned int col);
        
        // Access element (const)
        const double& operator[](unsigned int col) const;
        
    private:
        double* rowData;
        unsigned int rowSize;
    };
    
    // Row accessor (modifiable)
    Row operator[](unsigned int row);
    
    // Row accessor (const)
    const Row operator[](unsigned int row) const;
    
    // =================== HELPER METHODS =================== 
    
    // Get matrix dimension
    unsigned int getDimension() const;
    
    // Get sum of all elements (used for comparison operators)
    double getSum() const;
    
    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const SquareMat& mat);

private:
    // =================== PRIVATE DATA MEMBERS =================== 
    double** elements;    // 2D array to store the matrix elements
    unsigned int dimension;   // Matrix dimension (matrix is dimension x dimension)
    
    // =================== PRIVATE HELPER METHODS =================== 
    
    // Initialize matrix with zeros
    void init();
    
    // Free memory
    void cleanup();
    
    // Deep copy from another matrix
    void copyFrom(const SquareMat& source);
    
    // Helper method for determinant calculation
    double calculateDeterminant() const;
    
    // Create an identity matrix of the current dimension
    SquareMat createIdentity() const;
};

} 
