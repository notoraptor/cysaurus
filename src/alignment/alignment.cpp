//
// Created by notoraptor on 27/06/2019.
//

#include <algorithm>
#include "alignment.hpp"

void classifySimilarities(
		Sequence** sequences, int nbSequences, int iFrom, int iTo, int width, int height, double* edges) {
	iTo = std::min(iTo, nbSequences);
	int maximumDistanceScore = SIMPLE_MAX_PIXEL_DISTANCE * width * height;
	for (int i = iFrom; i < iTo; ++i) {
		#pragma omp parallel for default(none) shared(sequences, i, nbSequences, width, height, maximumDistanceScore, edges)
		for (int j = i + 1; j < nbSequences; ++j) {
			edges[i * nbSequences + j] = compareFaster(sequences[i], sequences[j], width, height, maximumDistanceScore);
		}
	}
}

void classifySimilaritiesDirected(
		Sequence** sequences, int nbSequences, int iFrom, int iTo, int width, int height, bool* edges, double limit) {
	iTo = std::min(iTo, nbSequences);
	int maximumDistanceScore = SIMPLE_MAX_PIXEL_DISTANCE * width * height;
	for (int i = iFrom; i < iTo; ++i) {
#pragma omp parallel for default(none) shared(sequences, i, nbSequences, width, height, maximumDistanceScore, edges, limit)
		for (int j = i + 1; j < nbSequences; ++j) {
			if (edges[i * nbSequences + j])
				edges[i * nbSequences + j] = compareFaster(sequences[i], sequences[j], width, height, maximumDistanceScore) >= limit;
		}
	}
}

void classifySimilaritiesSelected(
		Sequence** sequences, int nbSequences, int iFrom, int iTo, int width, int height, double limit, int* edges) {
	iTo = std::min(iTo, nbSequences);
	int maximumDistanceScore = SIMPLE_MAX_PIXEL_DISTANCE * width * height;
	for (int i = iFrom; i < iTo; ++i) {
		int nb = edges[i * nbSequences];
#pragma omp parallel for default(none) shared(sequences, i, nb, nbSequences, width, height, maximumDistanceScore, limit, edges)
		for (int j = 1; j < nb; ++j) {
			int k = edges[i * nbSequences + j];
			edges[i * nbSequences + j] *= compareFaster(sequences[i], sequences[k], width, height, maximumDistanceScore) >= limit;
		}
	}
}

