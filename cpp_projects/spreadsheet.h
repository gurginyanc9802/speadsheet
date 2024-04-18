#ifndef spreadsheet_h
#define spreadsheet_h

#include <initializer_list>
#include <iomanip>

#include "spreadsheet.h"
#include "cell.h"

class SpreadSheet {

public:

    SpreadSheet(); 
    SpreadSheet(std::size_t s); 
    SpreadSheet(std::size_t s1, std::size_t s2); 
    SpreadSheet(const SpreadSheet& rhv); 
    SpreadSheet(SpreadSheet&& rhv); 
    ~SpreadSheet(); 

private:
    class Column;
public:

    SpreadSheet& operator=(const SpreadSheet& rhv); 
    SpreadSheet& operator=(SpreadSheet&& rhv); 
    Column operator[](size_t pos);
    const Column operator[](size_t pos) const;

    void clear() noexcept;

    void mirrorH();
    void mirrorV();
    void mirrorD();
    void mirrorSD();


    void resizeRow(std::size_t s); 
    void resizeCol(std::size_t s); 
    void resize(std::size_t s1, std::size_t s2); 
    std::size_t get_row(); 
    std::size_t get_col(); 
    void rotate(int);

    void removeRow(size_t r);
    void removeRows(std::initializer_list<size_t> rs);
    void removeCol(size_t c);
    void removeCols(std::initializer_list<size_t> cs);

    SpreadSheet slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols);        

    std::size_t maxLen() const;
private:
    void rotate_right();
    void rotate_left();
    void if_square();

private:

    Cell** sheet;
    std::size_t row;
    std::size_t col;

};

class SpreadSheet::Column {
    private:
        Cell* col;
    public:
        explicit Column(Cell* col);
    public:
        Column() = delete;
        Column(const Column&) = delete;
        Column(Column&&) = delete;

        const Column& operator=(const Column&) = delete;
        const Column& operator=(Column&&) = delete;
    public:
        Cell& operator[](size_t pos);
        const Cell& operator[](size_t pos) const;
};

bool operator==(SpreadSheet sh1, SpreadSheet sh2); 
bool operator!=(SpreadSheet sh1, SpreadSheet sh2); 
std::ostream& operator<<(std::ostream& out, SpreadSheet sh);

#endif