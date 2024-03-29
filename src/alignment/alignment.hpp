//
// Created by notoraptor on 27/06/2019.
//

#ifndef VIDEORAPTOR_ALIGNMENT_HPP
#define VIDEORAPTOR_ALIGNMENT_HPP


#include "alignmentCommon.hpp"


extern "C" {
	void classifySimilarities(Sequence** sequences, int nbSequences, int from, int to, int width, int height, double* edges);
	void classifySimilaritiesDirected(Sequence** sequences, int nbSequences, int from, int to, int width, int height, bool* edges, double limit);
	void classifySimilaritiesSelected(Sequence** sequences, int nbSequences, int from, int to, int width, int height, double limit, int* edges);
	double compareSimilarSequences(const Sequence* p1, const Sequence* p2, int width, int height, int maximumDistanceScore);
};

#endif //VIDEORAPTOR_ALIGNMENT_HPP
