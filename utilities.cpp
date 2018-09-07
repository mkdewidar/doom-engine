// Determines whether the current processor architecture is big or little endian.
// This is done by making an array of bytes, then reading them from memory as an int, which 
// tells us about the order the processor reads information from memory aka endianness.
//
// In memory the data would be like this:
//                                      address 10 | 0x01
//                                      address 11 | 0x00
// On a little endian architecture, the data at 10 is placed in the lower end of the register
//     and the data at 11 is placed at the upper end giving 0x0001
//
// On a big endian architecture, the data at 10 is placed at the upper rend of the register
//     and the data at 11 is placed at the lower end giving the number 0x0100
bool IsSystemBigEndian() {
    uint8_t a[2] = { 0x01, 0x00 };

    uint16_t aAsInt = *(uint16_t*)a;
    if ( aAsInt == 1 ) {
        return false;
    } else {
        return true;
    }
}

