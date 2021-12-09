
//#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch_all.hpp>
#include "../src/libs/phenospex_utils.hpp"


TEST_CASE( "Simple verification of scanner to scale conversions", "[verificaton]" )
{
    sScannerPosition_t scanner_pos;
    scanner_pos.block = 1;
    scanner_pos.col = 1;
    scanner_pos.row = 1;

    auto result = ScannerToScalePosition(scanner_pos);
    REQUIRE(((result.col == 'B') && (result.row == 1)));

    auto pos = ScaleToScannerPosition(result);
    REQUIRE((pos == scanner_pos));

    // 43:05:02
    scanner_pos.block = 43;
    scanner_pos.col = 5;
    scanner_pos.row = 2;

    result = ScannerToScalePosition(scanner_pos);
    REQUIRE(((result.col == 'G') && (result.row == 35)));

    pos = ScaleToScannerPosition(result);
    REQUIRE((pos == scanner_pos));
}

