//
// Created by notoraptor-desktop on 09/08/2021.
//

#include <algorithm>
#include <vector>
#include "alignmentCommon.hpp"
#include "alignmentOther.hpp"


double alignmentScore(std::vector<double>& matrix, const int* a, const int* b, int columns, double interval, int gapScore) {
	int sideLength = columns + 1;
	int matrixSize = sideLength * sideLength;
	for (int i = 0; i < sideLength; ++i) {
		matrix[i] = i * gapScore;
	}
	for (int i = 1; i < sideLength; ++i) {
		matrix[i * sideLength] = i * gapScore;
		for (int j = 1; j < sideLength; ++j) {
			matrix[i * sideLength + j] = std::max(
					matrix[(i - 1) * sideLength + (j - 1)] + 2 * ((interval - abs(a[i - 1] - b[j - 1])) / interval) - 1,
					std::max(
							matrix[(i - 1) * sideLength + j] + gapScore,
							matrix[i * sideLength + (j - 1)] + gapScore
					)
			);
		}
	}
	return matrix[matrixSize - 1];
}

double batchAlignmentScore(const int* A, const int* B, int rows, int columns, int minVal, int maxVal, int gapScore) {
	int sideLength = columns + 1;
	int matrixSize = sideLength * sideLength;
	std::vector<double> matrix(matrixSize, 0);
	double interval = maxVal - minVal;
	double totalScore = 0;
	for (int i = 0; i < rows; ++i)
		totalScore += alignmentScore(matrix, A + i * columns, B + i * columns, columns, interval, gapScore);
	return totalScore;
}

void compareMatrix(Sequence** sequences, int nbRows, int nbCols, int width, int height, double* edges) {
	int nbSequences = nbRows + nbCols;
	int maximumDistanceScore = SIMPLE_MAX_PIXEL_DISTANCE * width * height;
	for (int i = 0; i < nbRows; ++i) {
		#pragma omp parallel for default(none) shared(sequences, i, nbRows, nbCols, nbSequences, width, height, maximumDistanceScore, edges)
		for (int j = nbRows; j < nbSequences; ++j) {
			edges[i * nbCols + j - nbRows] = compareFaster(sequences[i], sequences[j], width, height, maximumDistanceScore);
		}
	}
}
