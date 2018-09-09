// Code for reading WAD files. WAD files are the data file format used in DOOM.
// They store all of the data related to the game (levels, enemy placement, etc)
// Functions assume data is stored in big endian.

#include "utilities.cpp"

// Reads and returns a copy of a signed 2 byte integer
// from the given data starting at the given index.
int16_t ReadShort(char* dataArray, size_t startIndex) {
    // upper and lower byte of the end result
    uint8_t lowerByte;
    uint8_t upperByte;

    // depending on endianness, either the first byte in the data is the
    // lower half or the upper half of the 2 bytes
    if (IsSystemBigEndian()) {
        upperByte = dataArray[startIndex];
        lowerByte = dataArray[startIndex + 1];
    } else {
        lowerByte = dataArray[startIndex];
        upperByte = dataArray[startIndex + 1];
    }

    // copying the upper half into a cleared out int
    // then shifting it to leave the lower half empty for the lower byte
    return ((0 | upperByte) << 8) | lowerByte;
}

// Reads and returns a copy of an unsigned 2 byte integer
// from the given data starting at the given index. This is the same logic
// as ReadShort but the bytes are reinterpreted as unsigned.
uint16_t ReadUnsignedShort(char* dataArray, size_t startIndex) {
    return 0u | ReadShort(dataArray, startIndex);
}