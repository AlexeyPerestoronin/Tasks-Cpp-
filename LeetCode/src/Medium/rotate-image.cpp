////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @brief   Solve the task: implement the `rotate`-method of `Solution`-class
/// @details https://leetcode.com/problems/rotate-image/
/// You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
/// You have to rotate the image in - place, which means you have to modify the input 2D matrix directly.
/// DO NOT allocate another 2D matrix and do the rotation.
///
/// Example 1:
///   Input:
///     1 2 3
///     4 5 6
///     7 8 9
///     matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
///   Output:
///     7 4 1
///     8 5 2
///     9 6 3
///     matrix = [[7, 4, 1], [8, 5, 2], [9, 6, 3]]
///
/// Example 2:
///   Input:
///     5   1  9 11
///     2   4  8 10
///     13  3  6  7
///     15 14 12 16
///     matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
///   Output:
///     15 13  2  5
///     14  3  4  1
///     12  6  8  9
///     16  7 10 11
///     matrix = [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
///
/// Constraints :
///
/// n == matrix.length == matrix[i].length
/// 1 <= n <= 20
/// - 1000 <= matrix[i][j] <= 1000
///
/// @author  St�phane Postollec: spostollec@aligntech.com
/// @date    31.10.2022
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <vector>

#include <gtest/gtest-param-test.h>
#include <gtest/gtest.h>

namespace {
using InputDataType = std::vector<std::vector<int>>;
using OutputDataType = InputDataType;
using TestDataType = std::tuple<InputDataType, OutputDataType>;

class Solution {
    public:
    void rotate(std::vector<std::vector<int>>& matrix) {
        // TODO: implement this method...
    }
};

struct TestSolution : Solution, testing::TestWithParam<TestDataType>
{
};

// clang-format off
  INSTANTIATE_TEST_SUITE_P(
      GeneralTestData,
      TestSolution,
      ::testing::Values(
          // from example
          TestDataType{ InputDataType{ {1,2,3},{4,5,6},{7,8,9} }, OutputDataType{ {7,4,1}, {8,5,2}, {9,6,3} } },
          TestDataType{ InputDataType{ {5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16} }, OutputDataType{ {15,13,2,5} ,{14,3,4,1},{12,6,8,9},{16,7,10,11} } }
          // additional
          // TODO: create additional tests...
  ));
// clang-format on

TEST_P(TestSolution, TestRotateMethod) {
    static const int minLength = 1;
    static const int maxLength = 20;
    static const int minVal = -1000;
    static const int maxVal = 1000;

    /// Check matrix restrictions lambda.
    /// n == matrix.length == matrix[i].length
    /// 1 <= n <= 20
    /// - 1000 <= matrix[i][j] <= 1000
    auto checkMatrixRestrictions = [](InputDataType& matrix) {
        const size_t nbRows = matrix.size();
        ASSERT_TRUE(nbRows >= minLength && nbRows <= maxLength);
        for (auto row = 0; row < nbRows; ++row) {
            const size_t nbCols = matrix[row].size();
            ASSERT_TRUE(nbCols >= minLength && nbCols <= maxLength);
            for (auto col = 0; col < nbCols; ++col) {
                const auto& val = matrix[row][col];
                ASSERT_TRUE(val >= minVal && val <= maxVal);
            }
        }
    };

    auto [inputData, outputData] = GetParam();
    // Check input and output matrices restrictions.
    checkMatrixRestrictions(inputData);
    checkMatrixRestrictions(outputData);
    // Rotate in-place input matrix
    rotate(inputData);
    // Check that input matrix restrictions are still correct after rotate method.
    checkMatrixRestrictions(inputData);

    // Check all values of rotated input matrix against output matrix ones.
    for (auto row = 0; row < inputData.size(); ++row)
        for (auto col = row; col < inputData[row].size(); ++col)
            ASSERT_EQ(inputData[row][col], outputData[row][col]);
}
} // namespace
