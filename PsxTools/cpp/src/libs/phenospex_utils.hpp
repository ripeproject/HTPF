
#pragma once

#include <cstdint>

struct sScannerPosition_t
{
	int8_t block;
	int8_t col;
	int8_t row;

	sScannerPosition_t() : block(-1), col(-1), row(-1)
	{}

	sScannerPosition_t(int8_t b, int8_t c, int8_t r) : block(b), col(c), row(r)
	{}
};

inline bool operator ==(const sScannerPosition_t& lhs, const sScannerPosition_t& rhs)
{
	return (lhs.block == rhs.block) && (lhs.col == rhs.col) && (lhs.row == rhs.row);
}

const sScannerPosition_t INVALID_SCAN_POSITION = sScannerPosition_t();


struct sScalePosition_t
{
	char col;
	int8_t row;

	sScalePosition_t() : col(' '), row(-1)
	{}

	sScalePosition_t(char c, int8_t r) : col(c), row(r)
	{}
};

inline bool operator ==(const sScalePosition_t& lhs, const sScalePosition_t& rhs)
{
	return (lhs.col == rhs.col) && (lhs.row == rhs.row);
}

const sScalePosition_t INVALID_SCALE_POSITION = sScalePosition_t();


sScalePosition_t ScannerToScalePosition(int8_t block, int8_t col, int8_t row);
sScalePosition_t ScannerToScalePosition(sScannerPosition_t pos);

sScannerPosition_t ScaleToScannerPosition(char col, int8_t row);
sScannerPosition_t ScaleToScannerPosition(sScalePosition_t pos);
