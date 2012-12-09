/**
 * bitset.h
 */
#ifndef BITSET_HEADER_SEEN
#define BITSET_HEADER_SEEN

typedef struct bitset* BitSet;

BitSet CreateBitSet(unsigned int numberOfBits);
void FreeBitSet(BitSet bitset);

unsigned int CompareBitSets(BitSet first, BitSet second);
unsigned int IntValueOfBitSet(BitSet bitset);
void SetBit(BitSet bitSet, unsigned int b);
void ClearBit(BitSet bitSet, unsigned int b);
unsigned int GetBit(BitSet bitSet, unsigned int b);
void ClearAll(BitSet bitSet);
void SetAll(BitSet bitSet);

#endif
