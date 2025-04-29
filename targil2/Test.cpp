// Email: badarnimona2@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "SquareMat.hpp"
#include <cmath>
#include <stdexcept>

using namespace matrix_ops;

// Helper function to check if two matrices are equal element-wise
bool matrixEqual(const SquareMat& m1, const SquareMat& m2, double epsilon = 1e-9) {
    // Use std::abs to ensure proper scoping
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

TEST_SUITE("SquareMat Class Tests") {
    
    //--------------------------------------------------------------------------
    // Constructor Tests
    //--------------------------------------------------------------------------
    TEST_CASE("Constructors") {
        SUBCASE("Default constructor") {
            SquareMat m;
            CHECK(m.getDimension() == 0);
        }
        
        SUBCASE("Size constructor") {
            SquareMat m(3);
            CHECK(m.getDimension() == 3);
            
            // Should initialize to zero
            for (unsigned int i = 0; i < 3; i++) {
                for (unsigned int j = 0; j < 3; j++) {
                    CHECK(m[i][j] == 0.0);
                }
            }
        }
        
        SUBCASE("Value constructor") {
            SquareMat m(2, 3.5);
            CHECK(m.getDimension() == 2);
            
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(m[i][j] == 3.5);
                }
            }
        }
        
        SUBCASE("Copy constructor") {
            SquareMat original(2, 2.5);
            SquareMat copy(original);
            
            CHECK(copy.getDimension() == original.getDimension());
            CHECK(matrixEqual(copy, original));
            
            // Modify original to ensure deep copy
            original[0][0] = 9.9;
            CHECK(copy[0][0] == 2.5);
        }
    }
    
    //--------------------------------------------------------------------------
    // Assignment Operator Test
    //--------------------------------------------------------------------------
    TEST_CASE("Assignment operator") {
        SquareMat m1(2, 1.0);
        SquareMat m2(3, 2.0);
        
        m1 = m2;
        
        CHECK(m1.getDimension() == 3);
        CHECK(matrixEqual(m1, m2));
        
        // Test deep copy
        m2[0][0] = 9.9;
        CHECK(m1[0][0] == 2.0);
        
        // Self-assignment
        m1 = m1;
        CHECK(m1.getDimension() == 3);
    }
    
    //--------------------------------------------------------------------------
    // Basic Arithmetic Operators
    //--------------------------------------------------------------------------
    TEST_CASE("Basic arithmetic operations") {
        SUBCASE("Addition") {
            SquareMat m1(2, 1.0);
            SquareMat m2(2, 2.0);
            SquareMat result = m1 + m2;
            
            CHECK(result.getDimension() == 2);
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(result[i][j] == 3.0);
                }
            }
            
            // Check exception for mismatched dimensions
            SquareMat m3(3, 1.0);
            CHECK_THROWS_AS(m1 + m3, std::invalid_argument);
        }
        
        SUBCASE("Subtraction") {
            SquareMat m1(2, 5.0);
            SquareMat m2(2, 2.0);
            SquareMat result = m1 - m2;
            
            CHECK(result.getDimension() == 2);
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(result[i][j] == 3.0);
                }
            }
            
            // Check exception for mismatched dimensions
            SquareMat m3(3, 1.0);
            CHECK_THROWS_AS(m1 - m3, std::invalid_argument);
        }
        
        SUBCASE("Unary negation") {
            SquareMat m(2, 3.0);
            SquareMat result = -m;
            
            CHECK(result.getDimension() == 2);
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(result[i][j] == -3.0);
                }
            }
        }
        
        SUBCASE("Matrix multiplication") {
            SquareMat m1(2);
            m1[0][0] = 1.0; m1[0][1] = 2.0;
            m1[1][0] = 3.0; m1[1][1] = 4.0;
            
            SquareMat m2(2);
            m2[0][0] = 5.0; m2[0][1] = 6.0;
            m2[1][0] = 7.0; m2[1][1] = 8.0;
            
            SquareMat result = m1 * m2;
            
            // Expected result:
            // [1*5 + 2*7, 1*6 + 2*8] = [19, 22]
            // [3*5 + 4*7, 3*6 + 4*8] = [43, 50]
            CHECK(result[0][0] == 19.0);
            CHECK(result[0][1] == 22.0);
            CHECK(result[1][0] == 43.0);
            CHECK(result[1][1] == 50.0);
            
            // Check exception for mismatched dimensions
            SquareMat m3(3, 1.0);
            CHECK_THROWS_AS(m1 * m3, std::invalid_argument);
        }
        
        SUBCASE("Scalar multiplication (matrix * scalar)") {
            SquareMat m(2, 3.0);
            SquareMat result = m * 2.0;
            
            CHECK(result.getDimension() == 2);
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(result[i][j] == 6.0);
                }
            }
        }
        
        SUBCASE("Scalar multiplication (scalar * matrix)") {
            SquareMat m(2, 3.0);
            SquareMat result = 2.0 * m;
            
            CHECK(result.getDimension() == 2);
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(result[i][j] == 6.0);
                }
            }
        }
        
        SUBCASE("Element-wise multiplication") {
            SquareMat m1(2, 3.0);
            SquareMat m2(2, 2.0);
            SquareMat result = m1 % m2;
            
            CHECK(result.getDimension() == 2);
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(result[i][j] == 6.0);
                }
            }
            
            // Check exception for mismatched dimensions
            SquareMat m3(3, 1.0);
            CHECK_THROWS_AS(m1 % m3, std::invalid_argument);
        }
        
        SUBCASE("Modulo with scalar") {
            SquareMat m(2);
            m[0][0] = 5.0; m[0][1] = 6.0;
            m[1][0] = 7.0; m[1][1] = 8.0;
            
            SquareMat result = m % 3;
            
            CHECK(result[0][0] == 2.0);  // 5 % 3 = 2
            CHECK(result[0][1] == 0.0);  // 6 % 3 = 0
            CHECK(result[1][0] == 1.0);  // 7 % 3 = 1
            CHECK(result[1][1] == 2.0);  // 8 % 3 = 2
        }
        
        SUBCASE("Division by scalar") {
            SquareMat m(2, 6.0);
            SquareMat result = m / 2.0;
            
            CHECK(result.getDimension() == 2);
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(result[i][j] == 3.0);
                }
            }
            
            // Check exception for division by zero
            CHECK_THROWS_AS(m / 0.0, std::invalid_argument);
        }
    }
    
    //--------------------------------------------------------------------------
    // Power Operator
    //--------------------------------------------------------------------------
    TEST_CASE("Power operator") {
        SUBCASE("Power 0") {
            // Any matrix to power 0 should be identity
            SquareMat m(2, 3.0);
            SquareMat result = m ^ 0;
            
            CHECK(result.getDimension() == 2);
            CHECK(result[0][0] == 1.0);
            CHECK(result[0][1] == 0.0);
            CHECK(result[1][0] == 0.0);
            CHECK(result[1][1] == 1.0);
        }
        
        SUBCASE("Power 1") {
            // Any matrix to power 1 should be itself
            SquareMat m(2, 3.0);
            SquareMat result = m ^ 1;
            
            CHECK(matrixEqual(result, m));
        }
        
        SUBCASE("Power 2") {
            // Matrix to power 2 should be matrix * matrix
            SquareMat m(2);
            m[0][0] = 1.0; m[0][1] = 2.0;
            m[1][0] = 3.0; m[1][1] = 4.0;
            
            SquareMat result = m ^ 2;
            SquareMat expected = m * m;
            
            CHECK(matrixEqual(result, expected));
        }
        
        SUBCASE("Power with identity matrix") {
            // Identity matrix to any power is still identity
            SquareMat identity(2);
            identity[0][0] = identity[1][1] = 1.0;
            
            SquareMat result = identity ^ 5;
            CHECK(matrixEqual(result, identity));
        }
        
        SUBCASE("Power with exceptions") {
            SquareMat m(2, 1.0);
            
            // Negative power
            CHECK_THROWS_AS(m ^ (-1), std::invalid_argument);
            
            // Empty matrix
            SquareMat empty;
            CHECK_THROWS_AS(empty ^ 2, std::invalid_argument);
        }
    }
    
    //--------------------------------------------------------------------------
    // Increment/Decrement Operators
    //--------------------------------------------------------------------------
    TEST_CASE("Increment and decrement operators") {
        SUBCASE("Pre-increment") {
            SquareMat m(2, 3.0);
            SquareMat& result = ++m;
            
            // Check values were incremented
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(m[i][j] == 4.0);
                }
            }
            
            // Check reference equality
            CHECK(&result == &m);
        }
        
        SUBCASE("Post-increment") {
            SquareMat m(2, 3.0);
            SquareMat result = m++;
            
            // Check original values in returned copy
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(result[i][j] == 3.0);
                }
            }
            
            // Check matrix was incremented
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(m[i][j] == 4.0);
                }
            }
        }
        
        SUBCASE("Pre-decrement") {
            SquareMat m(2, 3.0);
            SquareMat& result = --m;
            
            // Check values were decremented
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(m[i][j] == 2.0);
                }
            }
            
            // Check reference equality
            CHECK(&result == &m);
        }
        
        SUBCASE("Post-decrement") {
            SquareMat m(2, 3.0);
            SquareMat result = m--;
            
            // Check original values in returned copy
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(result[i][j] == 3.0);
                }
            }
            
            // Check matrix was decremented
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(m[i][j] == 2.0);
                }
            }
        }
    }
    
    //--------------------------------------------------------------------------
    // Special Operations: Transpose and Determinant
    //--------------------------------------------------------------------------
    TEST_CASE("Special operations: transpose and determinant") {
        SUBCASE("Transpose") {
            SquareMat m(3);
            for (unsigned int i = 0; i < 3; i++) {
                for (unsigned int j = 0; j < 3; j++) {
                    m[i][j] = static_cast<double>(i * 3 + j + 1);  // 1-9
                }
            }
            
            SquareMat transposed = ~m;
            
            // Check transposed elements
            for (unsigned int i = 0; i < 3; i++) {
                for (unsigned int j = 0; j < 3; j++) {
                    CHECK(transposed[i][j] == m[j][i]);
                }
            }
        }
        
        SUBCASE("Determinant of small matrices") {
            // 1x1 matrix
            SquareMat m1(1);
            m1[0][0] = 5.0;
            CHECK(!m1 == 5.0);
            
            // 2x2 matrix
            SquareMat m2(2);
            m2[0][0] = 1.0; m2[0][1] = 2.0;
            m2[1][0] = 3.0; m2[1][1] = 4.0;
            // det = 1*4 - 2*3 = 4 - 6 = -2
            CHECK(!m2 == -2.0);
            
            // Empty matrix
            SquareMat empty;
            CHECK(!empty == 0.0);
        }
        
        SUBCASE("Determinant of 3x3 matrix") {
            SquareMat m(3);
            // Create a 3x3 matrix with determinant = 0
            m[0][0] = 1.0; m[0][1] = 2.0; m[0][2] = 3.0;
            m[1][0] = 4.0; m[1][1] = 5.0; m[1][2] = 6.0;
            m[2][0] = 7.0; m[2][1] = 8.0; m[2][2] = 9.0;
            
            CHECK(!m == 0.0);
            
            // Create a 3x3 matrix with non-zero determinant
            SquareMat m2(3);
            m2[0][0] = 2.0; m2[0][1] = -3.0; m2[0][2] = 1.0;
            m2[1][0] = 2.0; m2[1][1] = 0.0;  m2[1][2] = -1.0;
            m2[2][0] = 1.0; m2[2][1] = 4.0;  m2[2][2] = 5.0;
            
            CHECK(std::abs(!m2 - 49.0) < 1e-9);
        }
    }
    
    //--------------------------------------------------------------------------
    // Element Access
    //--------------------------------------------------------------------------
    TEST_CASE("Element access") {
        SquareMat m(2);
        
        // Set elements
        m[0][0] = 1.0; m[0][1] = 2.0;
        m[1][0] = 3.0; m[1][1] = 4.0;
        
        // Check values
        CHECK(m[0][0] == 1.0);
        CHECK(m[0][1] == 2.0);
        CHECK(m[1][0] == 3.0);
        CHECK(m[1][1] == 4.0);
        
        // Check out of bounds exceptions
        CHECK_THROWS_AS(m[5][0], std::out_of_range);
        CHECK_THROWS_AS(m[0][5], std::out_of_range);
        
        // Check const access
        const SquareMat constM = m;
        CHECK(constM[0][0] == 1.0);
        CHECK(constM[1][1] == 4.0);
        CHECK_THROWS_AS(constM[5][0], std::out_of_range);
    }
    
    //--------------------------------------------------------------------------
    // Comparison Operators
    //--------------------------------------------------------------------------
    TEST_CASE("Comparison operators") {
        // These matrices have the same sum (1+2+3+4 = 10)
        SquareMat m1(2);
        m1[0][0] = 1.0; m1[0][1] = 2.0;
        m1[1][0] = 3.0; m1[1][1] = 4.0;
        
        SquareMat m2(2);
        m2[0][0] = 4.0; m2[0][1] = 3.0;
        m2[1][0] = 2.0; m2[1][1] = 1.0;
        
        // This matrix has a different sum (5+6+7+8 = 26)
        SquareMat m3(2);
        m3[0][0] = 5.0; m3[0][1] = 6.0;
        m3[1][0] = 7.0; m3[1][1] = 8.0;
        
        SUBCASE("Equality and inequality") {
            CHECK(m1 == m2);  // Same sum
            CHECK_FALSE(m1 != m2);
            
            CHECK(m1 != m3);  // Different sum
            CHECK_FALSE(m1 == m3);
        }
        
        SUBCASE("Less than and greater than") {
            CHECK(m1 < m3);  // 10 < 26
            CHECK_FALSE(m3 < m1);
            
            CHECK(m3 > m1);  // 26 > 10
            CHECK_FALSE(m1 > m3);
            
            CHECK_FALSE(m1 < m2);  // Equal sums
            CHECK_FALSE(m1 > m2);
        }
        
        SUBCASE("Less than or equal and greater than or equal") {
            CHECK(m1 <= m2);  // Equal sums
            CHECK(m1 >= m2);
            
            CHECK(m1 <= m3);  // 10 <= 26
            CHECK_FALSE(m1 >= m3);
            
            CHECK(m3 >= m1);  // 26 >= 10
            CHECK_FALSE(m3 <= m1);
        }
    }
    
    //--------------------------------------------------------------------------
    // Compound Assignment Operators
    //--------------------------------------------------------------------------
    TEST_CASE("Compound assignment operators") {
        SUBCASE("Addition assignment") {
            SquareMat m1(2, 3.0);
            SquareMat m2(2, 2.0);
            
            m1 += m2;
            
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(m1[i][j] == 5.0);  // 3.0 + 2.0 = 5.0
                }
            }
            
            // Check exception for mismatched dimensions
            SquareMat m3(3, 1.0);
            CHECK_THROWS_AS(m1 += m3, std::invalid_argument);
        }
        
        SUBCASE("Subtraction assignment") {
            SquareMat m1(2, 5.0);
            SquareMat m2(2, 2.0);
            
            m1 -= m2;
            
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(m1[i][j] == 3.0);  // 5.0 - 2.0 = 3.0
                }
            }
            
            // Check exception for mismatched dimensions
            SquareMat m3(3, 1.0);
            CHECK_THROWS_AS(m1 -= m3, std::invalid_argument);
        }
        
        SUBCASE("Matrix multiplication assignment") {
            SquareMat m1(2);
            m1[0][0] = 1.0; m1[0][1] = 2.0;
            m1[1][0] = 3.0; m1[1][1] = 4.0;
            
            SquareMat m2(2);
            m2[0][0] = 5.0; m2[0][1] = 6.0;
            m2[1][0] = 7.0; m2[1][1] = 8.0;
            
            SquareMat expected = m1 * m2;
            m1 *= m2;
            
            CHECK(matrixEqual(m1, expected));
            
            // Check exception for mismatched dimensions
            SquareMat m3(3, 1.0);
            CHECK_THROWS_AS(m1 *= m3, std::invalid_argument);
        }
        
        SUBCASE("Scalar multiplication assignment") {
            SquareMat m(2, 3.0);
            m *= 2.0;
            
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(m[i][j] == 6.0);  // 3.0 * 2.0 = 6.0
                }
            }
        }
        
        SUBCASE("Element-wise multiplication assignment") {
            SquareMat m1(2, 3.0);
            SquareMat m2(2, 2.0);
            
            m1 %= m2;
            
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(m1[i][j] == 6.0);  // 3.0 * 2.0 = 6.0
                }
            }
            
            // Check exception for mismatched dimensions
            SquareMat m3(3, 1.0);
            CHECK_THROWS_AS(m1 %= m3, std::invalid_argument);
        }
        
        SUBCASE("Modulo with scalar assignment") {
            SquareMat m(2);
            m[0][0] = 5.0; m[0][1] = 6.0;
            m[1][0] = 7.0; m[1][1] = 8.0;
            
            m %= 3;
            
            CHECK(m[0][0] == 2.0);  // 5 % 3 = 2
            CHECK(m[0][1] == 0.0);  // 6 % 3 = 0
            CHECK(m[1][0] == 1.0);  // 7 % 3 = 1
            CHECK(m[1][1] == 2.0);  // 8 % 3 = 2
        }
        
        SUBCASE("Division by scalar assignment") {
            SquareMat m(2, 6.0);
            m /= 2.0;
            
            for (unsigned int i = 0; i < 2; i++) {
                for (unsigned int j = 0; j < 2; j++) {
                    CHECK(m[i][j] == 3.0);  // 6.0 / 2.0 = 3.0
                }
            }
            
            // Check exception for division by zero
            CHECK_THROWS_AS(m /= 0.0, std::invalid_argument);
        }
    }
}
