#include "bitset.h"

#include <stdlib.h>
#include <assert.h>

typedef unsigned int word;

typedef struct bitset {
    word* words;
    unsigned int numberOfWords;
} internalBitset;

enum { WORD_SIZE = sizeof(word) * 8 };

unsigned int WordIndex(unsigned int b) {
    return b / WORD_SIZE;
}

unsigned int WordOffset(unsigned int b) {
    return b % WORD_SIZE;
}

BitSet CreateBitSet(unsigned int numberOfBits) {
    BitSet bitset = malloc(sizeof(internalBitset));
    bitset->numberOfWords = (numberOfBits / WORD_SIZE) + 1;
    bitset->words = malloc(sizeof(word) * bitset->numberOfWords);

    for (unsigned int i = 0; i < bitset->numberOfWords; ++i) {
        bitset->words[i] = 0;
    }

    return bitset;
}

void FreeBitSet(BitSet bitset) {
    free(bitset->words);
    free(bitset);
}

void SetBit(BitSet bitSet, unsigned int b) {
    bitSet->words[WordIndex(b)] |= 1 << WordOffset(b);
}

void ClearBit(BitSet bitSet, unsigned int b) {
    bitSet->words[WordIndex(b)] &= ~(1 << WordOffset(b));
}

unsigned int GetBit(BitSet bitSet, unsigned int b) {
    return bitSet->words[WordIndex(b)] & (1 << WordOffset(b));
}

void ClearAll(BitSet bitSet) {
    for (unsigned int i = 0; i < bitSet->numberOfWords; ++i) {
        bitSet->words[i] = 0;
    }
}

void SetAll(BitSet bitSet) {
    for (unsigned int i = 0; i < bitSet->numberOfWords; ++i) {
        SetBit(bitSet, i);
    }
}

unsigned int CompareBitSets(BitSet first, BitSet second) {
    assert(first->numberOfWords == second->numberOfWords);
    assert(first->numberOfWords <= 2);

    unsigned int runningTotal = 0;

    for (unsigned int i = 0; i < first->numberOfWords; ++i) {
        //Logical or together so any shared bits are 1 in the result. Shift each word
        //by its offset.
        runningTotal += (first->words[i] & second->words[i]) << (WORD_SIZE * i);
    }

    return runningTotal;
}

unsigned int IntValueOfBitSet(BitSet bitset) {
    unsigned int runningTotal = 0;

    for (unsigned int i = 0; i < bitset->numberOfWords; ++i) {
        //Logical or together so any shared bits are 1 in the result. Shift each word
        //by its offset.
        runningTotal += (bitset->words[i] << (WORD_SIZE * i));
    }

    return runningTotal;
}
