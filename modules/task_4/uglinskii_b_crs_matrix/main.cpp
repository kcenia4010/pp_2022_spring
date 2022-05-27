// Copyright 2022 Uglinskii Bogdan
#include <gtest/gtest.h>
#include <time.h>

#include <iostream>
#include <vector>

#include "./crs_multiplication.h"

TEST(Multiplication_seq, crs_50x50_30) {
  MatrixCRS matrix_A = GenerateRandomMatrixCRS(50, 50, 30);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(50, 50, 30);

  MatrixCRS matrix_C;
  CRSMultiply(matrix_A, matrix_B, &matrix_C);

  std::vector<std::vector<double>> C;

  NormalMulty(ExpandMatrix(matrix_A), ExpandMatrix(matrix_B), &C);
  MatrixCRS crs_C;
  ConvertToCRS(C, &crs_C);
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, crs_C));
}

TEST(Multiplication_parallel, 3x3_4) {

  MatrixCRS matrix_A = GenerateRandomMatrixCRS(3, 3, 4);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(3, 3, 4);

  MatrixCRS matrix_C;
  auto t1 = clock();
  CRSMultiply(matrix_A, matrix_B, &matrix_C);
  auto t2 = clock();

  MatrixCRS C_std;
  auto t1_ = clock();
  CRSMultiplySTD(matrix_A, matrix_B, &C_std);
  auto t2_ = clock();
  std::cout << "NO STD time = " << static_cast<float>(t2 - t1) / CLOCKS_PER_SEC
            << "\nSTD time = " << static_cast<float>(t2_ - t1_) / CLOCKS_PER_SEC
            << "\nAcceleration = "
            << (static_cast<float>(t2 - t1) / CLOCKS_PER_SEC) /
                   (static_cast<float>(t2_ - t1_) / CLOCKS_PER_SEC)
            << "\n";
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, C_std));
}

TEST(Multiplication_parallel, 50x50_30) {

  MatrixCRS matrix_A = GenerateRandomMatrixCRS(50, 50, 30);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(50, 50, 30);

  MatrixCRS matrix_C;
  auto t1 = clock();
  CRSMultiply(matrix_A, matrix_B, &matrix_C);
  auto t2 = clock();

  MatrixCRS C_std;
  auto t1_ = clock();
  CRSMultiplySTD(matrix_A, matrix_B, &C_std);
  auto t2_ = clock();
  std::cout << "NO STD time = " << static_cast<float>(t2 - t1) / CLOCKS_PER_SEC
            << "\nSTD time = " << static_cast<float>(t2_ - t1_) / CLOCKS_PER_SEC
            << "\nAcceleration = "
            << (static_cast<float>(t2 - t1) / CLOCKS_PER_SEC) /
                   (static_cast<float>(t2_ - t1_) / CLOCKS_PER_SEC)
            << "\n";
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, C_std));
}

TEST(Multiplication_parallel, 200x200_350) {

  MatrixCRS matrix_A = GenerateRandomMatrixCRS(200, 200, 350);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(200, 200, 350);

  MatrixCRS matrix_C;
  auto t1 = clock();
  CRSMultiply(matrix_A, matrix_B, &matrix_C);
  auto t2 = clock();

  MatrixCRS C_std;
  auto t1_ = clock();
  CRSMultiplySTD(matrix_A, matrix_B, &C_std);
  auto t2_ = clock();
  std::cout << "NO STD time = " << static_cast<float>(t2 - t1) / CLOCKS_PER_SEC
            << "\nSTD time = " << static_cast<float>(t2_ - t1_) / CLOCKS_PER_SEC
            << "\nAcceleration = "
            << (static_cast<float>(t2 - t1) / CLOCKS_PER_SEC) /
                   (static_cast<float>(t2_ - t1_) / CLOCKS_PER_SEC)
            << "\n";
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, C_std));
}

TEST(Multiplication_parallel, 250x250_400) {

  MatrixCRS matrix_A = GenerateRandomMatrixCRS(250, 250, 400);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(250, 250, 400);

  MatrixCRS matrix_C;
  auto t1 = clock();
  CRSMultiply(matrix_A, matrix_B, &matrix_C);
  auto t2 = clock();

  MatrixCRS C_std;
  auto t1_ = clock();
  CRSMultiplySTD(matrix_A, matrix_B, &C_std);
  auto t2_ = clock();
  std::cout << "NO STD time = " << static_cast<float>(t2 - t1) / CLOCKS_PER_SEC
            << "\nSTD time = " << static_cast<float>(t2_ - t1_) / CLOCKS_PER_SEC
            << "\nAcceleration = "
            << (static_cast<float>(t2 - t1) / CLOCKS_PER_SEC) /
                   (static_cast<float>(t2_ - t1_) / CLOCKS_PER_SEC)
            << "\n";
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, C_std));
}

TEST(Multiplication_parallel, 300x300_2000) {

  MatrixCRS matrix_A = GenerateRandomMatrixCRS(300, 300, 2000);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(300, 300, 2000);

  MatrixCRS matrix_C;
  auto t1 = clock();
  CRSMultiply(matrix_A, matrix_B, &matrix_C);
  auto t2 = clock();

  MatrixCRS C_std;
  auto t1_ = clock();
  CRSMultiplySTD(matrix_A, matrix_B, &C_std);
  auto t2_ = clock();
  std::cout << "NO STD time = " << static_cast<float>(t2 - t1) / CLOCKS_PER_SEC
            << "\nSTD time = " << static_cast<float>(t2_ - t1_) / CLOCKS_PER_SEC
            << "\nAcceleration = "
            << (static_cast<float>(t2 - t1) / CLOCKS_PER_SEC) /
                   (static_cast<float>(t2_ - t1_) / CLOCKS_PER_SEC)
            << "\n";
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, C_std));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}