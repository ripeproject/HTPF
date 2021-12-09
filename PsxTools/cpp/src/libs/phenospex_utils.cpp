
#include "phenospex_utils.hpp"

#include <cctype>

sScalePosition_t ScannerToScalePosition(int8_t block, int8_t col, int8_t row)
{
    // Check the scanner bounds
    if ((block < 1) || (block > 48)) return INVALID_SCALE_POSITION;
    if ((col < 1) || (col > 6)) return INVALID_SCALE_POSITION;
    if ((row < 1) || (row > 2)) return INVALID_SCALE_POSITION;

    sScalePosition_t result = INVALID_SCALE_POSITION;

    switch (block)
    {
    case 1: case 2: case 3: case 4:
        {
            result.col = (row == 2) ? 'A' : 'B';
            result.row = (block - 1) * 6 + col;
            break;
        }
        case 6: case 7: case 8: case 9:
        {
            result.col = (row == 2) ? 'A' : 'B';
            result.row = 24 + (block - 6) * 6 + col;
            break;
        }
        case 13: case 14: case 15: case 16:
        {
            result.col = (row == 2) ? 'C' : 'D';
            result.row = (block - 13) * 6 + col;
            break;
        }
        case 18: case 19: case 20: case 21:
        {
            result.col = (row == 2) ? 'C' : 'D';
            result.row = 24 + (block - 18) * 6 + col;
            break;
        }
        case 23:
        {
            result.col = (row == 2) ? 'C' : 'D';
            result.row = 48 + col;
            break;
        }
        case 25: case 26: case 27: case 28:
        {
            result.col = (row == 2) ? 'E' : 'F';
            result.row = (block - 25) * 6 + col;
            break;
        }
        case 30: case 31: case 32: case 33:
        {
            result.col = (row == 2) ? 'E' : 'F';
            result.row = 24 + (block - 30) * 6 + col;
            break;
        }
        case 35:
        {
            result.col = (row == 2) ? 'E' : 'F';
            result.row = 48 + col;
            break;
        }
        case 37: case 38: case 39: case 40:
        {
            result.col = (row == 2) ? 'G' : 'H';
            result.row = (block - 37) * 6 + col;
            break;
        }
        case 42: case 43: case 44: case 45:
        {
            result.col = (row == 2) ? 'G' : 'H';
            result.row = 24 + (block - 42) * 6 + col;
            break;
        }
    }

    return result;
}

sScalePosition_t ScannerToScalePosition(sScannerPosition_t pos)
{
    return ScannerToScalePosition(pos.block, pos.col, pos.row);
}



sScannerPosition_t ScaleToScannerPosition(char col, int8_t row)
{
    col = static_cast<char>(std::toupper(static_cast<unsigned char>(col)));

    // Check the scale bounds
    if ((col < 'A') || (col > 'H')) return INVALID_SCAN_POSITION;
    if (row<1) return INVALID_SCAN_POSITION;


    sScannerPosition_t result;

    result.col = row % 6;
    if (result.col == 0) result.col = 6;

    int b = (row / 6) + 1;
    if (b > 4) ++b;
    if (b > 9) ++b;

    if ((col == 'A') || (col == 'B') || (col == 'G') || (col == 'H'))
    {
        if (row>48) return INVALID_SCAN_POSITION;
        result.row = ((col == 'A') || (col == 'G')) ? 2 : 1;

        if ((col == 'G') || (col == 'H'))
        {
            result.block = b + 36;
        }
        else
        {
            result.block = b;
        }
    }
    else if ((col == 'C') || (col == 'D') || (col == 'E') || (col == 'F'))
    {
        if (row > 54) return INVALID_SCAN_POSITION;
        result.row = ((col == 'C') || (col == 'E')) ? 2 : 1;

        if ((col == 'E') || (col == 'F'))
        {
            result.block = b + 24;
        }
        else
        {
            result.block = b + 12;
        }
    }
    else
    {
        result = INVALID_SCAN_POSITION;
    }

    return result;
}

sScannerPosition_t ScaleToScannerPosition(sScalePosition_t pos)
{
    return ScaleToScannerPosition(pos.col, pos.row);
}
