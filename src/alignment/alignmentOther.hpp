//
// Created by notoraptor-desktop on 09/08/2021.
//

#ifndef CYSAURUS_ALIGNMENTOTHER_HPP
#define CYSAURUS_ALIGNMENTOTHER_HPP

extern "C" {
	double batchAlignmentScore(const int* A, const int* B, int rows, int columns, int minVal, int maxVal, int gapScore);
	void compareMatrix(Sequence** sequences, int nbRows, int nbCols, int width, int height, double* edges);
};

#endif //CYSAURUS_ALIGNMENTOTHER_HPP
