// Email: badarnimona2@gmail.com

#include "SquareMat.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <cmath>  // For fabs()

using namespace matrix_ops;
using namespace std;

/**
 * A simple test framework for matrix operations
 */
class MatrixTester {
private:
    unsigned int passed = 0;
    unsigned int failed = 0;
    vector<string> failedTests;
    
    void displayResult(const string& testName, bool success) {
        cout << testName << ": ";
        
        if (success) {
            cout << "\033[1;32mPASSED\033[0m" << endl;  // Green
            passed++;
        } else {
            cout << "\033[1;31mFAILED\033[0m" << endl;  // Red
            failed++;
            failedTests.push_back(testName);
        }
    }
    
public:
    void printSeparator() {
        cout << "\n------------------------------------------------\n" << endl;
    }
    
    void printHeader(const string& title) {
        printSeparator();
        cout << "\033[1;36m" << title << "\033[0m" << endl;
        printSeparator();
    }
    
    void runTest(const string& testName, bool condition) {
        displayResult(testName, condition);
    }
    
    template<typename T>
    void assertEqual(const string& testName, const T& actual, const T& expected) {
        bool success = (actual == expected);
        displayResult(testName, success);
        
        if (!success) {
            cout << "  Expected: " << expected << endl;
            cout << "  Actual:   " << actual << endl;
        }
    }
    
    void printSummary() {
        printSeparator();
        cout << "\033[1;33mTEST SUMMARY\033[0m" << endl;
        cout << "Total tests: " << (passed + failed) << endl;
        cout << "Passed:      " << passed << endl;
        cout << "Failed:      " << failed << endl;
        
        if (failed > 0) {
            cout << "\nFailed tests:" << endl;
            for (const auto& test : failedTests) {
                cout << "  - " << test << endl;
            }
            cout << endl;
        } else {
            cout << "\n\033[1;32mAll tests passed!\033[0m" << endl;
        }
    }
};

// Helper function to check if two matrices are equal element-by-element
bool matricesEqual(const SquareMat& m1, const SquareMat& m2, double epsilon = 1e-6) {
    if (m1.getDimension() != m2.getDimension()) {
        return false;
    }
    
    for (unsigned int i = 0; i < m1.getDimension(); i++) {
        for (unsigned int j = 0; j < m1.getDimension(); j++) {
            if (std::abs(m1[i][j] - m2[i][j]) > epsilon) {
                return false;
            }
        }
    }
    
    return true;
}

int main() {
    MatrixTester tester;
    
    cout << "\033[1;35m=======================================\033[0m" << endl;
    cout << "\033[1;35m SQUARE MATRIX OPERATIONS DEMONSTRATOR \033[0m" << endl;
    cout << "\033[1;35m=======================================\033[0m" << endl;
    
    try {
        // Constructor tests
        tester.printHeader("CONSTRUCTOR TESTS");
        
        // Default constructor
        SquareMat emptyMatrix;
        tester.assertEqual("Default constructor dimension", emptyMatrix.getDimension(), 0u);
        
        // Size constructor
        SquareMat sizedMatrix(3);
        tester.assertEqual("Size constructor dimension", sizedMatrix.getDimension(), 3u);
        
        // Test that elements are initialized to zero
        bool allZeros = true;
        for (unsigned int i = 0; i < 3; i++) {
            for (unsigned int j = 0; j < 3; j++) {
                if (sizedMatrix[i][j] != 0.0) {
                    allZeros = false;
                    break;
                }
            }
        }
        tester.runTest("Size constructor initializes to zeros", allZeros);
        
        // Value constructor
        SquareMat valuedMatrix(3, 5.5);
        tester.assertEqual("Value constructor creates matrix of right size", valuedMatrix.getDimension(), 3u);
        
        // Test that all elements have the right value
        bool allCorrectValue = true;
        for (unsigned int i = 0; i < 3; i++) {
            for (unsigned int j = 0; j < 3; j++) {
                if (valuedMatrix[i][j] != 5.5) {
                    allCorrectValue = false;
                    break;
                }
            }
        }
        tester.runTest("Value constructor initializes with correct value", allCorrectValue);
        
        // Copy constructor
        SquareMat original(2, 3.0);
        SquareMat copy(original);
        tester.runTest("Copy constructor creates equal matrix", matricesEqual(original, copy));
        
        // Test that it's a deep copy
        original[0][0] = 99.0;
        tester.runTest("Copy constructor creates a deep copy", copy[0][0] == 3.0);
        
        // Assignment operator
        SquareMat assigned = original;
        tester.runTest("Assignment operator creates equal matrix", matricesEqual(original, assigned));
        
        // Test that it's a deep copy
        original[0][1] = 88.0;
        tester.runTest("Assignment operator creates a deep copy", assigned[0][1] == 3.0);
        
        // Basic Matrix Creation Display
        tester.printHeader("DISPLAYING MATRICES");
        
        // Create test matrices
        SquareMat identityMatrix(3);
        for (unsigned int i = 0; i < 3; i++) {
            identityMatrix[i][i] = 1.0;
        }
        
        SquareMat sequentialMatrix(3);
        for (unsigned int i = 0; i < 3; i++) {
            for (unsigned int j = 0; j < 3; j++) {
                sequentialMatrix[i][j] = static_cast<double>(i * 3 + j + 1);
            }
        }
        
        cout << "Identity Matrix (3x3):" << endl;
        cout << identityMatrix << endl << endl;
        
        cout << "Sequential Matrix (values 1-9):" << endl;
        cout << sequentialMatrix << endl << endl;
        
        // Basic Arithmetic Operations
        tester.printHeader("BASIC ARITHMETIC OPERATIONS");
        
        SquareMat matA(2, 3.0);
        SquareMat matB(2, 2.0);
        
        cout << "Matrix A (all 3.0):" << endl << matA << endl << endl;
        cout << "Matrix B (all 2.0):" << endl << matB << endl << endl;
        
        // Addition
        SquareMat additionResult = matA + matB;
        cout << "A + B:" << endl << additionResult << endl << endl;
        
        SquareMat expectedAdd(2, 5.0);
        tester.runTest("Matrix addition", matricesEqual(additionResult, expectedAdd));
        
        // Subtraction
        SquareMat subtractionResult = matA - matB;
        cout << "A - B:" << endl << subtractionResult << endl << endl;
        
        SquareMat expectedSub(2, 1.0);
        tester.runTest("Matrix subtraction", matricesEqual(subtractionResult, expectedSub));
        
        // Unary Minus
        SquareMat negation = -matA;
        cout << "-A:" << endl << negation << endl << endl;
        
        SquareMat expectedNeg(2, -3.0);
        tester.runTest("Matrix negation", matricesEqual(negation, expectedNeg));
        
        // Matrix Multiplication
        SquareMat identityMul = matA * identityMatrix.operator[](0)[0];
        cout << "A * Identity:" << endl << identityMul << endl << endl;
        tester.runTest("Matrix * Identity = Matrix", matricesEqual(identityMul, matA));
        
        SquareMat mulResult = matA * matB;
        cout << "A * B:" << endl << mulResult << endl << endl;
        
        // For 2x2 matrix with all 3.0 * 2x2 matrix with all 2.0
        // Each element should be 3.0 * 2.0 * 2 = 12.0
        SquareMat expectedMul(2, 12.0);
        tester.runTest("Matrix multiplication", matricesEqual(mulResult, expectedMul));
        
        // Scalar Multiplication
        SquareMat scalarMul = matA * 2.0;
        cout << "A * 2.0:" << endl << scalarMul << endl << endl;
        
        SquareMat expectedScalarMul(2, 6.0);
        tester.runTest("Matrix * scalar", matricesEqual(scalarMul, expectedScalarMul));
        
        // Scalar Multiplication (reversed)
        SquareMat scalarMulReversed = 2.0 * matA;
        cout << "2.0 * A:" << endl << scalarMulReversed << endl << endl;
        tester.runTest("scalar * Matrix", matricesEqual(scalarMulReversed, expectedScalarMul));
        
        // Element-wise Multiplication
        SquareMat elementWiseResult = matA % matB;
        cout << "A % B (element-wise):" << endl << elementWiseResult << endl << endl;
        
        SquareMat expectedElementWise(2, 6.0);  // 3.0 * 2.0 = 6.0
        tester.runTest("Element-wise multiplication", matricesEqual(elementWiseResult, expectedElementWise));
        
        // Division by Scalar
        SquareMat divResult = matA / 3.0;
        cout << "A / 3.0:" << endl << divResult << endl << endl;
        
        SquareMat expectedDiv(2, 1.0);
        tester.runTest("Matrix / scalar", matricesEqual(divResult, expectedDiv));
        
        // Modulo with Scalar
        SquareMat modResult = matA % 2;
        cout << "A % 2:" << endl << modResult << endl << endl;
        
        SquareMat expectedMod(2, 1.0);  // 3 % 2 = 1
        tester.runTest("Matrix % scalar", matricesEqual(modResult, expectedMod));
        
        // Special Operations
        tester.printHeader("SPECIAL OPERATIONS");
        
        // Create a test matrix with distinct values
        SquareMat testMatrix(3);
        testMatrix[0][0] = 1; testMatrix[0][1] = 2; testMatrix[0][2] = 3;
        testMatrix[1][0] = 4; testMatrix[1][1] = 5; testMatrix[1][2] = 6;
        testMatrix[2][0] = 7; testMatrix[2][1] = 8; testMatrix[2][2] = 9;
        
        cout << "Test Matrix:" << endl << testMatrix << endl << endl;
        
        // Transpose
        SquareMat transposed = ~testMatrix;
        cout << "Transposed Test Matrix:" << endl << transposed << endl << endl;
        
        // Verify transpose
        bool transposeCorrect = true;
        for (unsigned int i = 0; i < 3; i++) {
            for (unsigned int j = 0; j < 3; j++) {
                if (testMatrix[i][j] != transposed[j][i]) {
                    transposeCorrect = false;
                    break;
                }
            }
        }
        tester.runTest("Transpose operation", transposeCorrect);
        
        // Determinant
        double detValue = !testMatrix;
        cout << "Determinant of Test Matrix: " << detValue << endl << endl;
        tester.assertEqual("Determinant of singular matrix", detValue, 0.0);
        
        // Create a matrix with known non-zero determinant
        SquareMat detMatrix(3);
        detMatrix[0][0] = 1; detMatrix[0][1] = 2; detMatrix[0][2] = 3;
        detMatrix[1][0] = 0; detMatrix[1][1] = 4; detMatrix[1][2] = 5;
        detMatrix[2][0] = 1; detMatrix[2][1] = 0; detMatrix[2][2] = 6;
        
        double nonZeroDet = !detMatrix;
        cout << "Matrix with non-zero determinant:" << endl << detMatrix << endl;
        cout << "Determinant: " << nonZeroDet << endl << endl;
        tester.assertEqual("Determinant of non-singular matrix", nonZeroDet, 22.0);
        
        // Power operator
        tester.printHeader("POWER OPERATIONS");
        
        // Identity to any power is identity
        SquareMat identityPower = identityMatrix ^ 5;
        cout << "Identity ^ 5:" << endl << identityPower << endl << endl;
        tester.runTest("Identity^n = Identity", matricesEqual(identityPower, identityMatrix));
        
        // Matrix to power 1 is itself
        SquareMat powerOne = matA ^ 1;
        cout << "A ^ 1:" << endl << powerOne << endl << endl;
        tester.runTest("Matrix^1 = Matrix", matricesEqual(powerOne, matA));
        
        // Matrix to power 0 is identity
        SquareMat powerZero = matA ^ 0;
        cout << "A ^ 0:" << endl << powerZero << endl << endl;
        
        SquareMat expectedPowerZero(2);
        expectedPowerZero[0][0] = expectedPowerZero[1][1] = 1.0;
        tester.runTest("Matrix^0 = Identity", matricesEqual(powerZero, expectedPowerZero));
        
        // Matrix to power 2
        SquareMat powerTwo = matA ^ 2;
        cout << "A ^ 2:" << endl << powerTwo << endl << endl;
        
        SquareMat expectedPowerTwo = matA * matA;
        tester.runTest("Matrix^2 = Matrix*Matrix", matricesEqual(powerTwo, expectedPowerTwo));
        
        // Increment/Decrement Operations
        tester.printHeader("INCREMENT/DECREMENT OPERATIONS");
        
        // Pre-increment
        SquareMat preIncMatrix(2, 5.0);
        cout << "Original Matrix:" << endl << preIncMatrix << endl;
        
        // Store pointer address for comparison
        const SquareMat* preIncMatrixPtr = &preIncMatrix;
        SquareMat& preIncResultRef = ++preIncMatrix;
        const SquareMat* preIncResultPtr = &preIncResultRef;
        cout << "After ++Matrix:" << endl << preIncMatrix << endl;
        cout << "Return value of ++Matrix:" << endl << preIncResultRef << endl << endl;
        
        SquareMat expectedPreInc(2, 6.0);
        tester.runTest("Pre-increment modifies matrix", matricesEqual(preIncMatrix, expectedPreInc));
        tester.runTest("Pre-increment returns modified matrix", matricesEqual(preIncResultRef, expectedPreInc));
        tester.runTest("Pre-increment returns reference to same matrix", preIncMatrixPtr == preIncResultPtr);
        
        // Post-increment
        SquareMat postIncMatrix(2, 5.0);
        cout << "Original Matrix:" << endl << postIncMatrix << endl;
        
        SquareMat postIncResult = postIncMatrix++;
        cout << "Result of Matrix++:" << endl << postIncResult << endl;
        cout << "Matrix after post-increment:" << endl << postIncMatrix << endl << endl;
        
        SquareMat expectedPostIncOriginal(2, 5.0);
        SquareMat expectedPostIncModified(2, 6.0);
        tester.runTest("Post-increment returns original value", matricesEqual(postIncResult, expectedPostIncOriginal));
        tester.runTest("Post-increment modifies matrix", matricesEqual(postIncMatrix, expectedPostIncModified));
        
        // Pre-decrement
        SquareMat preDecMatrix(2, 5.0);
        cout << "Original Matrix:" << endl << preDecMatrix << endl;
        
        SquareMat preDecResult = --preDecMatrix;
        cout << "After --Matrix:" << endl << preDecMatrix << endl;
        cout << "Return value of --Matrix:" << endl << preDecResult << endl << endl;
        
        SquareMat expectedPreDec(2, 4.0);
        tester.runTest("Pre-decrement modifies matrix", matricesEqual(preDecMatrix, expectedPreDec));
        tester.runTest("Pre-decrement returns modified matrix", matricesEqual(preDecResult, expectedPreDec));
        
        // Post-decrement
        SquareMat postDecMatrix(2, 5.0);
        cout << "Original Matrix:" << endl << postDecMatrix << endl;
        
        SquareMat postDecResult = postDecMatrix--;
        cout << "Result of Matrix--:" << endl << postDecResult << endl;
        cout << "Matrix after post-decrement:" << endl << postDecMatrix << endl << endl;
        
        SquareMat expectedPostDecOriginal(2, 5.0);
        SquareMat expectedPostDecModified(2, 4.0);
        tester.runTest("Post-decrement returns original value", matricesEqual(postDecResult, expectedPostDecOriginal));
        tester.runTest("Post-decrement modifies matrix", matricesEqual(postDecMatrix, expectedPostDecModified));
        
        // Comparison Operations
        tester.printHeader("COMPARISON OPERATIONS");
        
        // Create matrices with different sums for testing
        SquareMat sumMatrixA(2);
        sumMatrixA[0][0] = 1; sumMatrixA[0][1] = 2;
        sumMatrixA[1][0] = 3; sumMatrixA[1][1] = 4;
        // Sum = 10
        
        SquareMat sumMatrixB(2);
        sumMatrixB[0][0] = 4; sumMatrixB[0][1] = 3;
        sumMatrixB[1][0] = 2; sumMatrixB[1][1] = 1;
        // Sum = 10
        
        SquareMat sumMatrixC(2);
        sumMatrixC[0][0] = 5; sumMatrixC[0][1] = 6;
        sumMatrixC[1][0] = 7; sumMatrixC[1][1] = 8;
        // Sum = 26
        
        cout << "Matrix A (sum=10):" << endl << sumMatrixA << endl;
        cout << "Matrix B (sum=10):" << endl << sumMatrixB << endl;
        cout << "Matrix C (sum=26):" << endl << sumMatrixC << endl << endl;
        
        cout << "Testing equality comparisons..." << endl;
        tester.assertEqual("A == B (same sum)", sumMatrixA == sumMatrixB, true);
        tester.assertEqual("A != C (different sum)", sumMatrixA != sumMatrixC, true);
        
        cout << "\nTesting ordering comparisons..." << endl;
        tester.assertEqual("A < C", sumMatrixA < sumMatrixC, true);
        tester.assertEqual("C > A", sumMatrixC > sumMatrixA, true);
        tester.assertEqual("A <= B (equal)", sumMatrixA <= sumMatrixB, true);
        tester.assertEqual("A >= B (equal)", sumMatrixA >= sumMatrixB, true);
        tester.assertEqual("A <= C (less than)", sumMatrixA <= sumMatrixC, true);
        tester.assertEqual("C >= A (greater than)", sumMatrixC >= sumMatrixA, true);
        
        // Compound Assignment Operations
        tester.printHeader("COMPOUND ASSIGNMENT OPERATIONS");
        
        // Addition assignment
        SquareMat addAssignMatrix(2, 3.0);
        SquareMat addAssignOther(2, 2.0);
        
        cout << "Original Matrix:" << endl << addAssignMatrix << endl;
        addAssignMatrix += addAssignOther;
        cout << "After Matrix += Other:" << endl << addAssignMatrix << endl << endl;
        
        SquareMat expectedAddAssign(2, 5.0);
        tester.runTest("Addition assignment", matricesEqual(addAssignMatrix, expectedAddAssign));
        
        // Subtraction assignment
        SquareMat subAssignMatrix(2, 5.0);
        SquareMat subAssignOther(2, 2.0);
        
        cout << "Original Matrix:" << endl << subAssignMatrix << endl;
        subAssignMatrix -= subAssignOther;
        cout << "After Matrix -= Other:" << endl << subAssignMatrix << endl << endl;
        
        SquareMat expectedSubAssign(2, 3.0);
        tester.runTest("Subtraction assignment", matricesEqual(subAssignMatrix, expectedSubAssign));
        
        // Multiplication assignment
        SquareMat mulAssignMatrix(2, 3.0);
        SquareMat mulAssignOther(2, 2.0);
        
        cout << "Original Matrix:" << endl << mulAssignMatrix << endl;
        mulAssignMatrix *= mulAssignOther;
        cout << "After Matrix *= Other:" << endl << mulAssignMatrix << endl << endl;
        
        SquareMat expectedMulAssign(2, 12.0);  // Each element is 3.0*2.0 + 3.0*2.0 = 12.0
        tester.runTest("Multiplication assignment", matricesEqual(mulAssignMatrix, expectedMulAssign));
        
        // Scalar multiplication assignment
        SquareMat scalarMulAssignMatrix(2, 3.0);
        
        cout << "Original Matrix:" << endl << scalarMulAssignMatrix << endl;
        scalarMulAssignMatrix *= 2.0;
        cout << "After Matrix *= 2.0:" << endl << scalarMulAssignMatrix << endl << endl;
        
        SquareMat expectedScalarMulAssign(2, 6.0);
        tester.runTest("Scalar multiplication assignment", matricesEqual(scalarMulAssignMatrix, expectedScalarMulAssign));
        
        // Element-wise multiplication assignment
        SquareMat elemMulAssignMatrix(2, 3.0);
        SquareMat elemMulAssignOther(2, 2.0);
        
        cout << "Original Matrix:" << endl << elemMulAssignMatrix << endl;
        elemMulAssignMatrix %= elemMulAssignOther;
        cout << "After Matrix %= Other:" << endl << elemMulAssignMatrix << endl << endl;
        
        SquareMat expectedElemMulAssign(2, 6.0);  // 3.0 * 2.0 = 6.0
        tester.runTest("Element-wise multiplication assignment", matricesEqual(elemMulAssignMatrix, expectedElemMulAssign));
        
        // Modulo assignment
        SquareMat modAssignMatrix(2, 5.0);
        
        cout << "Original Matrix:" << endl << modAssignMatrix << endl;
        modAssignMatrix %= 3;
        cout << "After Matrix %= 3:" << endl << modAssignMatrix << endl << endl;
        
        SquareMat expectedModAssign(2, 2.0);  // 5 % 3 = 2
        tester.runTest("Modulo assignment", matricesEqual(modAssignMatrix, expectedModAssign));
        
        // Division assignment
        SquareMat divAssignMatrix(2, 6.0);
        
        cout << "Original Matrix:" << endl << divAssignMatrix << endl;
        divAssignMatrix /= 2.0;
        cout << "After Matrix /= 2.0:" << endl << divAssignMatrix << endl << endl;
        
        SquareMat expectedDivAssign(2, 3.0);
        tester.runTest("Division assignment", matricesEqual(divAssignMatrix, expectedDivAssign));
        
        // Exception Handling
        tester.printHeader("EXCEPTION HANDLING");
        
        cout << "Testing exceptions for invalid operations..." << endl;
        
        // Mismatched dimensions
        bool caughtMismatchedDimensions = false;
        try {
            SquareMat m1(2, 1.0);
            SquareMat m2(3, 2.0);
            SquareMat result = m1 + m2;  // Should throw exception
        } catch (const std::invalid_argument& e) {
            caughtMismatchedDimensions = true;
            cout << "Caught exception for mismatched dimensions: " << e.what() << endl;
        }
        tester.runTest("Exception for mismatched dimensions", caughtMismatchedDimensions);
        
        // Division by zero
        bool caughtDivisionByZero = false;
        try {
            SquareMat m(2, 1.0);
            SquareMat result = m / 0.0;  // Should throw exception
        } catch (const std::invalid_argument& e) {
            caughtDivisionByZero = true;
            cout << "Caught exception for division by zero: " << e.what() << endl;
        }
        tester.runTest("Exception for division by zero", caughtDivisionByZero);
        
        // Out of bounds access
        bool caughtOutOfBounds = false;
        try {
            SquareMat m(2, 1.0);
            /* Access an out-of-bounds element to trigger exception */
            m[5][0];  // Should throw exception
        } catch (const std::out_of_range& e) {
            caughtOutOfBounds = true;
            cout << "Caught exception for out of bounds access: " << e.what() << endl;
        }
        tester.runTest("Exception for out of bounds access", caughtOutOfBounds);
        
        // Print test summary
        tester.printSummary();
        
    } catch (const std::exception& e) {
        cerr << "\n\033[1;31mERROR: Unexpected exception caught: " << e.what() << "\033[0m" << endl;
        return 1;
    }
    
    return 0;
}
