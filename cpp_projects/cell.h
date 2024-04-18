#ifndef cell_h
#define cell_h

#include <iostream>
#include <string>
#include <vector>

class Cell {

public:

    Cell();
    Cell(int a);
    Cell(double a);
    Cell(char val);
    Cell(bool val);
    Cell(std::string a);
    Cell(const Cell& rhv);
    Cell(Cell&& rhv);
    Cell(const std::vector<int>& val);
    ~Cell();

public:

    const Cell& operator=(const Cell& rhv);
    const Cell& operator=(Cell&& rhv);
    const Cell& operator=(int a);
    const Cell& operator=(double a);
    const Cell& operator=(bool val);
    const Cell& operator=(char val);
    const Cell& operator=(std::string a);
    const Cell& operator=(const std::vector<int>& val); 

    operator int();
    operator double();
    operator char();
    operator bool();
    operator std::vector<int>();
    operator std::string();
    
    std::string get_cell() const;

private:

    std::string str;
    bool isvector;

};

bool operator==(Cell c1, Cell c2);
bool operator!=(Cell c1, Cell c2);
std::ostream& operator<<(std::ostream& out, const Cell& cell);
std::istream& operator>>(std::istream& in, Cell& ob);

#endif