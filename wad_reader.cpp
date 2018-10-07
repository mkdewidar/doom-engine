// Code for reading WAD files. WAD files are the data file format used in DOOM.
// They store all of the data related to the game (levels, enemy placement, etc)
//
// Functions assume data is stored in big endian.
//
// Start indices are always inclusive.

#include <string>
#include "utilities.cpp"

// Reads and returns a copy of an unsigned 2 byte integer
// from the 'data' starting at 'startIndex'.
uint16_t ReadUnsignedShort(char* data, size_t startIndex) {
    uint16_t value = 0;
    // Turns out, chars are considered to be signed by default, so when used
    // in arithmetic, the char is promoted to a signed int, promotions maintain
    // value so if the char had a "negative" value the int will be negative
    // which will screw up with the end result when the OR is done.
    uint8_t* dataAsUnsigned = reinterpret_cast<uint8_t*>(data);

    if (IsSystemBigEndian()) {
        value = (value | dataAsUnsigned[startIndex]) << 8;
        value = (value | dataAsUnsigned[startIndex + 1]);
    } else {
        value = (value | dataAsUnsigned[startIndex + 1]) << 8;
        value = (value | dataAsUnsigned[startIndex]);
    }

    return value;
}

// Reads and returns a copy of a signed 2 byte integer
// from 'data' starting at 'startIndex'. This is the same logic
// as ReadUnsignedShort but the bytes are reinterpreted as signed.
int16_t ReadShort(char* data, size_t startIndex) {
    int16_t s = 0;
    return s | ReadUnsignedShort(data, startIndex);
}

// Reads and returns a copy of an unsigned 4 byte integer
// from 'data' starting at 'startIndex'.
uint32_t ReadUnsignedInt(char* data, size_t startIndex) {
    uint32_t value = 0;
    // Turns out, chars are considered to be signed by default, so when used
    // in arithmetic, the char is promoted to a signed int, promotions maintain
    // value so if the char had a "negative" value the int will be negative
    // which will screw up with the end result when the OR is done.
    uint8_t* dataAsUnsigned = reinterpret_cast<uint8_t*>(data);

    if (IsSystemBigEndian()) {
        value = (value | dataAsUnsigned[startIndex]) << 8;
        value = (value | dataAsUnsigned[startIndex + 1]) << 8;
        value = (value | dataAsUnsigned[startIndex + 2]) << 8;
        value = (value | dataAsUnsigned[startIndex + 3]);
    } else {
        value = (value | dataAsUnsigned[startIndex + 3]) << 8;
        value = (value | dataAsUnsigned[startIndex + 2]) << 8;
        value = (value | dataAsUnsigned[startIndex + 1]) << 8;
        value = (value | dataAsUnsigned[startIndex]);
    }

    return value;
}

// Reads and returns a copy of a signed 4 byte integer
// from 'data' starting at 'startIndex'. This is the same logic
// as ReadUnsignedInt but bytes are reinterpreted as signed.
int32_t ReadInt(char* data, size_t startIndex) {
    int32_t i = 0;
    return i | ReadUnsignedInt(data, startIndex);
}

// Reads and copies 'length' number of characters from 'sourceData'
// starting at 'startIndex' into the string object 'dest' replacing it in the process.
void ReadString(char* sourceData, size_t startIndex, size_t length, std::string& dest) {
    dest = std::string(sourceData + startIndex, length);
}
