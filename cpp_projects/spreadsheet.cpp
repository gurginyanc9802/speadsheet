#include "cell.h"
#include "spreadsheet.h"

SpreadSheet::SpreadSheet()
    : row(2),
    col(2)

{
    sheet = new Cell*[row];
    for(std::size_t i = 0; i < row; ++i) {
        sheet[i] = new Cell[col];
    }
}       

SpreadSheet::SpreadSheet(std::size_t s)
    : row(s), 
    col(s)
{
    sheet = new Cell*[row];
    for(std::size_t i = 0; i < row; ++i) {
        sheet[i] = new Cell[col];
    }
}

SpreadSheet::SpreadSheet(std::size_t s1, std::size_t s2)
    : row(s1), 
    col(s2)
{
    sheet = new Cell*[row];
    for(std::size_t i = 0; i < row; ++i) {
        sheet[i] = new Cell[col];
    }
}

SpreadSheet::SpreadSheet(const SpreadSheet& rhv)
    : row(rhv.row), 
    col(rhv.col)
{
    sheet = new Cell*[row];
    for(std::size_t i = 0; i < row; ++i) {
        sheet[i] = new Cell[col];
    }

    for(std::size_t i = 0; i < row; ++i) {
        for(std::size_t j = 0; j < col; ++j) {
            sheet[i][j] = rhv.sheet[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet&& rhv)
    : row(std::move(rhv.row)), 
    col(std::move(rhv.col))
{
    sheet = rhv.sheet;
    rhv.row = 0;
    rhv.col = 0;
    rhv.sheet = nullptr;        
}

SpreadSheet::~SpreadSheet() {
    clear();
}

SpreadSheet& SpreadSheet::operator=(const SpreadSheet& rhv) {
    if(this != &rhv) {
        clear();
        row = rhv.row;
        col = rhv.col;
        sheet = new Cell*[row];
        for(std::size_t i = 0; i < row; ++i) {
            sheet[i] = new Cell[col];
        }

        for(std::size_t i = 0; i < row; ++i) {
            for(std::size_t j = 0; j < col; ++j) {
                sheet[i][j] = rhv.sheet[i][j];
            }
        }
    }
    return *this;
}

SpreadSheet& SpreadSheet::operator=(SpreadSheet&& rhv) {
    if(this != &rhv) {
        clear();
        row = std::move(rhv.row);
        col = std::move(rhv.col);
        sheet = rhv.sheet;
        rhv.col = 0;
        rhv.row = 0;
        rhv.sheet = nullptr;
    }
    return *this;
}

void SpreadSheet::resizeRow(std::size_t s) {
    if(s == row) {
        return;
    }
    Cell** ptr = new Cell*[s];
    for(std::size_t i = 0; i < s; ++i) {
        ptr[i] = new Cell[col];
    }
    std::size_t min = s < row ? s : row;
    for(std::size_t i = 0; i < min; ++i) {
        for(std::size_t j = 0; j < col; ++j) {
            ptr[i][j] = sheet[i][j];
        }
    }
    std::size_t ncol = col;
    clear();
    sheet = ptr;
    row = s;
    col = ncol;
    ptr = nullptr;
}

void SpreadSheet::resizeCol(std::size_t s) {
    if(s == col) {
        return;
    }
    Cell** ptr = new Cell*[row];
    for(std::size_t i = 0; i < row; ++i) {
        ptr[i] = new Cell[s];
    }
    std::size_t min = s < col ? s : col;
    for(std::size_t i = 0; i < row; ++i) {
        for(std::size_t j = 0; j < min; ++j) {
            ptr[i][j] = sheet[i][j];
        }
    }
    std::size_t nrow = row;
    clear();
    sheet = ptr;
    col = s;
    row = nrow;
    ptr = nullptr;
}

void SpreadSheet::resize(std::size_t s1, std::size_t s2) {
    if(row == s1 && col == s2) {
        return;
    }
    if(row == s1) {
        resizeCol(s2);
        return;
    }
    if(col == s2) {
        resizeRow(s1);
        return;
    }
    Cell** ptr = new Cell*[s1];
    for(std::size_t i = 0; i < s1; ++i) {
        ptr[i] = new Cell[s2];
    }
    std::size_t minRow = s1 < row ? s1 : row;
    std::size_t minCol = s2 < col ? s2 : col;
    for(std::size_t i = 0; i < minRow; ++i) {
        for(std::size_t j = 0; j < minCol; ++j) {
            ptr[i][j] = sheet[i][j];
        }
    }
    clear();
    sheet = ptr;
    row = s1;
    col = s2;
    ptr = nullptr;
}

std::size_t SpreadSheet::get_row() {
    return row;
}

std::size_t SpreadSheet::get_col() {
    return col;
}

void SpreadSheet::clear() noexcept {
    if(sheet) {
        for(std::size_t i = 0; i < row; ++i) {
            delete[] sheet[i];
        }
        delete[] sheet;
        sheet = nullptr;
    }
    row = 0;
    col = 0;
}

bool operator==(SpreadSheet sh1, SpreadSheet sh2) {
    if(sh1.get_row() != sh2.get_row() && sh1.get_col() != sh2.get_col()) {
        return false;
    }
    for(std::size_t i = 0; i < sh1.get_row(); ++i) {
        for(std::size_t j = 0; j < sh1.get_col(); ++j) {
            if(sh1[i][j] != sh2[i][j]) {
                return false;
            }
        }
    }
    return true;
}



bool operator!=(SpreadSheet sh1, SpreadSheet sh2) {
    return !(sh1 == sh2);
}

std::ostream& operator<<(std::ostream& out, SpreadSheet sheet) {
    const int width = 23 > sheet.maxLen() ? 23 : sheet.maxLen(); 
    const char fillChar = ' ';
    for (int i = 0; i < sheet.get_col(); ++i) {
        out << std::setw(width) << std::setfill('_') << '_';
    }
    out << std::endl;
    for (std::size_t i = 0; i < sheet.get_row(); ++i) {
        for (std::size_t j = 0; j < sheet.get_col(); ++j) {
            out << "|";
            out << std::setw(width - 2) << std::setfill(fillChar) << sheet[i][j];
        }
        out << "|" << std::endl;
        for (int j = 0; j < sheet.get_col(); ++j) {
            out << std::setw(width) << std::setfill('_') << '_';
        }
        out << std::endl;
    }
    return out;
}

std::size_t SpreadSheet::maxLen() const {
    std::size_t maxCellSize = 0;
    for (std::size_t i = 0; i < row; ++i) {
        for (std::size_t j = 0; j < col; ++j) {
            std::size_t cellSize = sheet[i][j].get_cell().size();
            maxCellSize = std::max(maxCellSize, cellSize);
        }
    }
    return maxCellSize;
}

void SpreadSheet::rotate(int n){
    if (n > 0) {
        n = n % 4;
        switch (n) {
            case 0:
                return;
            case 2:
                rotate_right();
            case 1:
                rotate_right();
                return;
            case 3:
                rotate_left();
                return;
        }
    }
    n = n % 4 + 4;
    rotate(n);
}

void SpreadSheet::rotate_right() {
    if (row == col){
        if_square();
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col/2; ++j) {
            Cell tmp = sheet[i][j];
            sheet[i][j] = sheet[i][col - j - 1];
            sheet[i][col - j - 1] = tmp;
        }
    }
        return;
    }

    Cell** ptr = new Cell*[col];
    for (int i = 0; i < col; ++i) {
        ptr[i] = new Cell[row];
    }

    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            ptr[i][j] = sheet[j][i]; 
        }
    }

    for (int i = 0; i < row; ++i) {
        delete[] sheet[i];
    }
    delete[] sheet;
    sheet = ptr;
    int tmp = row;
    row = col;
    col = tmp;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col/2; ++j) {
            Cell tmp = sheet[i][j];
            sheet[i][j] = sheet[i][col - j - 1];
            sheet[i][col - j - 1] = tmp;
        }
    }
}

void SpreadSheet::if_square() {
    for (int i = 0; i < row; ++i) {
        for (int j = i + 1; j < col; ++j) {
            Cell tmp = sheet[j][i];
            sheet[j][i] = sheet[i][j];
            sheet[i][j] = tmp;
        }
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col/2; ++j) {
            Cell tmp = sheet[i][j];
            sheet[i][j] = sheet[i][col - j - 1];
            sheet[i][col - j - 1] = tmp;
        }
    }
}

void SpreadSheet::rotate_left() {
    if (row == col){
        if_square();
    for (int i = 0; i < row/2; ++i) {
        for (int j = 0; j < col; ++j) {
            Cell tmp = sheet[i][j];
            sheet[i][j] = sheet[row - 1 - i][j];
            sheet[row - 1 - i][j] = tmp;
        }
    }
        return;
    }
    
    Cell** ptr = new Cell*[col];
    for (int i = 0; i < col; ++i) {
        ptr[i] = new Cell[row];
    }

    for (int i = 0; i < col; ++i) {
        for (int j = 0; j < row; ++j) {
            ptr[i][j] = sheet[j][i]; 
        }
    }

    for (int i = 0; i < row; ++i) {
        delete[] sheet[i];
    }
    delete[] sheet;
    sheet = ptr;
    int tmp = row;
    row = col;
    col = tmp;

    for (int i = 0; i < row/2; ++i) {
        for (int j = 0; j < col; ++j) {
            Cell tmp = sheet[i][j];
            sheet[i][j] = sheet[row - 1 - i][j];
            sheet[row - 1 - i][j] = tmp;
        }
    }
}

SpreadSheet::Column SpreadSheet::operator[](size_t pos) {
    return Column{sheet[pos]};
}

const SpreadSheet::Column SpreadSheet::operator[](size_t pos) const {
    return Column(sheet[pos]);
}

Cell& SpreadSheet::Column::operator[](size_t pos) {
    return col[pos];
}

const Cell& SpreadSheet::Column::operator[](size_t pos) const {
    return col[pos];
}

SpreadSheet::Column::Column(Cell* col) : col{col} {}

void SpreadSheet::mirrorH() {
    for (int i = 0; i < row / 2; ++i) {
        for (int j = 0; j < col; ++j) {
            std::swap(sheet[i][j], sheet[row - i - 1][j]);
        }
    }
}

void SpreadSheet::mirrorV() {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col / 2; ++j) {
            std::swap(sheet[i][j], sheet[i][col - 1 - j]);
        }
    }
}

void SpreadSheet::mirrorD() {
    Cell** sh = new Cell*[col];
    for(int i = 0; i < col; ++i){
        sh[i] = new Cell[row];
    }
    for(int i = 0; i < col; ++i) {
        for(int j = 0; j < row; ++j) {
            sh[i][j] = sheet[j][i];
        }
    }
    for(int i = 0; i < row; ++i) {
        delete[] sheet[i];
    }
    delete[] sheet;
    sheet = sh;
    std::swap(row, col);
}

void SpreadSheet::mirrorSD() {
    rotate_left();
    mirrorV();
}

void SpreadSheet::removeRow(size_t r) {
    delete[] sheet[r];
    for(int i = r; i < row - 1; ++i) {
        sheet[i] = sheet[i + 1];
    }
    --row;
}

void SpreadSheet::removeCol(size_t c) {
    Cell** tmp = new Cell*[row];
    for(int i = 0; i < row; ++i) {
        tmp[i] = new Cell[col - 1];
    }
    for(int i = 0; i < row; ++i) {
        int k = 0;
        for(int j = 0; j < col; ++j) {
            if(j == c) {
                continue;
            }
            tmp[i][k] = sheet[i][j];
            ++k;
        }
    }
    std::size_t newrow = row;
    std::size_t newcol = col - 1;
    clear();
    row = newrow;
    col = newcol;
    sheet = tmp;
    tmp = nullptr;
}

void SpreadSheet::removeRows(std::initializer_list<size_t> rs) {
    int count = 0;
    for (auto elem : rs) {
        elem -= count;
        removeRow(elem);
        ++count;
    }
}

void SpreadSheet::removeCols(std::initializer_list<size_t> cs) {
    int count = 0;
    for (auto elem : cs) {
        elem -= count;
        removeCol(elem);
        ++count;
    }
}

SpreadSheet SpreadSheet::slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols) {
    SpreadSheet newsheet(rows.size(), cols.size());
    std::size_t rindex = 0;
    for (auto i : rows) {
        std::size_t cindex = 0;\
        for (auto j : cols) {
            newsheet.sheet[rindex][cindex] = sheet[i][j];
            ++cindex;
        }
        ++rindex;
    }
    return newsheet;
}      


