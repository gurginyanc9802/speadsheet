#include "cell.h"

Cell::Cell() : str{""} {}

Cell::Cell(int a) : str(std::to_string(a)) {}

Cell::Cell(double a) : str(std::to_string(a)) {}

Cell::Cell(char val) : str(std::to_string(val)) {}

Cell::Cell(bool val) : str(val ? "true" : "false") {}

Cell::Cell(std::string a) : str{a} {}

Cell::Cell(const Cell& rhv) : str{rhv.str} {}

Cell::Cell(Cell&& rhv) : str{std::move(rhv.str)} {
    rhv.str = "";
}

Cell::Cell(const std::vector<int>& val) : isvector(true) {
    for (size_t i = 0; i < val.size(); ++i) {
        if (i != 0) {
            str += " "; 
        }
        str += std::to_string(val[i]); 
    }
}

Cell::~Cell() {}

const Cell& Cell::operator=(const Cell& rhv) {
    if (this != &rhv){
        str = rhv.str;
    }
    return *this;
}

const Cell& Cell::operator=(Cell&& rhv) {
    if (this != &rhv) {
        str = std::move(rhv.str);
        rhv.str = "";
    }
    return *this;
}

const Cell& Cell::operator=(int a) {
    str = std::to_string(a);
    return *this;
}

const Cell& Cell::operator=(double a) {
    str = std::to_string(a);
    return *this;
}

const Cell& Cell::operator=(bool val) {
    str = val ? "true" : "false";
    return *this;
}

const Cell& Cell::operator=(char val) {
    str = std::to_string(val);
    return *this;
}

const Cell& Cell::operator=(std::string a) {
    str = a;
    return *this;
}

const Cell& Cell::operator=(const std::vector<int>& val) {
    for (size_t i = 0; i < val.size(); ++i) {
        if (i != 0) {
            str += " "; 
        }
        str += std::to_string(val[i]); 
    }
    isvector = 1;
    return *this;
}

Cell::operator int() {
    return std::stoi(this->str);
}

Cell::operator double() {
    return std::stod(this->str);
}

Cell::operator char() {
    return str[0];
}

Cell::operator bool() {
    if (str == "")
        return false;
    return true;
}

Cell::operator std::vector<int>() {
    std::vector<int> result;
    std::string numString;
    for (char ch : str) {
        if (ch == ' ') {
            result.push_back(std::stoi(numString));
            numString.clear();
        } else {
            numString += ch;
        }
    }
    if (!numString.empty()) {
        result.push_back(std::stoi(numString));
    }
    return result;
}

Cell::operator std::string() {
    return str;
}

std::string Cell::get_cell() const {
    return str;
}

bool operator==(Cell c1, Cell c2) {
    return c1.get_cell() == c2.get_cell();
}

bool operator!=(Cell c1, Cell c2) {
    return !(c1 == c2);
}

std::ostream& operator<<(std::ostream& out, const Cell& cell) {
    out << cell.get_cell();
    return out;
}

std::istream& operator>>(std::istream& in, Cell& ob) {
    std::string st = "";
    in >> st;
    ob = st;
    return in;
}

