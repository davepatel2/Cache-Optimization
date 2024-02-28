#include <stdlib.h>
#include "matmul.h"

Matrix Allocate2ndMatrix(int height, int width, int init);

void matmul( float*, const float*, const float*, unsigned int, unsigned int, unsigned int);

////////////////////////////////////////////////////////////////////////////////
//! C = A * B
//! @param C          result matrix
//! @param A          matrix A
//! @param B          matrix B
//! @param hA         height of matrix A
//! @param wB         width of matrix B
////////////////////////////////////////////////////////////////////////////////

void matmul(float* C, const float* A, const float* B, unsigned int hA, 
    unsigned int wA, unsigned int wB)
{
  for (unsigned int i = 0; i < hA; i+=2)
    for (unsigned int j = 0; j < wB; j+=2) {
      double sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
      for (unsigned int k = 0; k < wA; ++k) {
        double a0 = A[i * wA + k];
        double a1 = A[(i + 1) * wA + k];
        double b0 = B[k * wB + j];
        double b1 = B[k * wB + (j + 1)];
        sum1 += a0 * b0;
        sum2 += a0 * b1;
        sum3 += a1 * b0;
        sum4 += a1 * b1;
      }
      C[i * wB + j] = (float)sum1;
      C[i * wB + (j + 1)] = (float)sum2;
      C[(i + 1) * wB + j] = (float)sum3;
      C[(i + 1) * wB + (j + 1)] = (float)sum4;
    }
}

// Allocate a matrix of dimensions height*width
Matrix Allocate2ndMatrix(int height, int width)
{
  Matrix M;
  M.width = M.pitch = width;
  M.height = height;
  int size = M.width * M.height;
  M.elements = NULL;

  M.elements = (float*) malloc(size*sizeof(float));

  for(unsigned int i = 0; i < M.height * M.width; i++)
  {
    M.elements[i] = (rand() / (float)RAND_MAX);
  }
  return M;
}

