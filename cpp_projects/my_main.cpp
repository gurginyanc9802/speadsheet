#include <iostream>

#include <vector>

#include <string>

#include "cell.h"

#include "spreadsheet.h"





int main() {

    // Create a spreadsheet with 3 rows and 4 columns

    SpreadSheet sheet(3, 4);



    // Fill the spreadsheet with some data

    for (std::size_t i = 0; i < sheet.get_row(); ++i) {

        for (std::size_t j = 0; j < sheet.get_col(); ++j) {

            sheet[i][j] = Cell(static_cast<int>(i * sheet.get_col() + j));

        }

    }



    // Print the original spreadsheet

    std::cout << "Original Spreadsheet:" << std::endl;

    std::cout << sheet << std::endl;



    // Test slicing

    SpreadSheet sliced = sheet.slice({0, 2}, {1, 3});

    std::cout << "Sliced Spreadsheet:" << std::endl;

    std::cout << sliced << std::endl;





    sheet.rotate(1);

    std::cout << "Rotated Left:" << std::endl;

    std::cout << sheet << std::endl;



    // Test mirroring

    sheet.mirrorH();

    std::cout << "Mirrored Horizontally:" << std::endl;

    std::cout << sheet << std::endl;



    sheet.mirrorV();

    std::cout << "Mirrored Vertically:" << std::endl;

    std::cout << sheet << std::endl;



    sheet.mirrorD();

    std::cout << "Mirrored Diagonally (/):" << std::endl;

    std::cout << sheet << std::endl;



    sheet.mirrorD();

    std::cout << "Mirrored Diagonally (\\):" << std::endl;

    std::cout << sheet << std::endl;



    // Test removing rows and columns

    sheet.removeRows({0});

    std::cout << "Removed Row 0:" << std::endl;

    std::cout << sheet << std::endl;



    sheet.removeCols({1});

    std::cout << "Removed Column 1:" << std::endl;

    std::cout << sheet << std::endl;



    sheet.resize(2, 2);

    std::cout << sheet << std::endl;



    sheet.resizeCol(3);

    std::cout << sheet << std::endl;



    return 0;

}