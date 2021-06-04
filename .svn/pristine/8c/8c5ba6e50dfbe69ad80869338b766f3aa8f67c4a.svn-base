#include <employees.h>

Employee::Employee(int type) : _type(type) {}
Developer::Developer() : Employee(1) {}
SalesManager::SalesManager() : Employee(2) {}

Employee::Employee(std::string name, int32_t _base_salary, int32_t _type) : _name(name), _base_salary(_base_salary), _type(_type) {}

SalesManager::SalesManager(std::string name, int32_t _base_salary, int32_t _sold_nm, int32_t _price) : Employee(name, _base_salary, 2), _sold_nm(_sold_nm), _price(_price) {}

Developer::Developer(std::string name, int32_t _base_salary, bool _has_bonus) : Employee(name, _base_salary, 1), _has_bonus(_has_bonus) {}

int SalesManager::salary() const {
    return _base_salary + _sold_nm * _price * 0.01;
}

int Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
}

void EmployeesArray::add(Employee *e) {
    employees.push_back(e);
}

int EmployeesArray::total_salary() const {
    int res = 0;
    for (size_t i = 0; i < employees.size(); i++) {
        res += employees[i]->salary();
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, EmployeesArray const& a) {
    for (size_t i = 0; i < a.employees.size(); i++) {
        os << i + 1 << ". ";
        os << *a.employees[i];
    }
    os << "== Total salary: " << a.total_salary() << "\n\n";
    return os;
}

std::istream& operator>> (std::istream& is, Employee& m) {
    m.read(is);
    return is;
}

std::ostream& operator<< (std::ostream& os, const Employee& m) {
    m.write(os);
    return os;
}

std::ifstream& operator>> (std::ifstream& is, Employee& m) {
    m.fread(is);
    return is;
}

std::ofstream& operator<< (std::ofstream& os, const Employee& m) {
    m.fwrite(os);
    return os;
}

void Developer::read(std::istream& is) {
    is >> _name >> _base_salary >> _has_bonus;
}

void Developer::write(std::ostream& os) const {
    os << "Developer\n" << "Name: " << _name << std::endl;
    os << "Base Salary: "<<  _base_salary << std::endl;
    os << "Has bonus: " << ((_has_bonus) ? '+' : '-') << std::endl;
}

void Employee::fread(std::ifstream& is) {
    char c = 0;
    do {
        is.read(&c, sizeof(char));
    if (c)
      _name += c;
    } while (c);
    is.read((char*) &_base_salary, sizeof(int32_t));
}

void Developer::fread(std::ifstream& is) {
    Employee::fread(is);
    is.read((char*) &_has_bonus, sizeof(bool));
}

void SalesManager::fread(std::ifstream& is) {
    Employee::fread(is);
    is.read((char*) &_sold_nm, sizeof(int32_t));
    is.read((char*) &_price, sizeof(int32_t));
}

void SalesManager::read(std::istream& is) {
    is >> _name >> _base_salary >> _sold_nm >> _price;
}

void SalesManager::write(std::ostream& os) const {
    os << "SalesManager\n" << "Name: " << _name << std::endl;
    os << "Base Salary: "<<  _base_salary << std::endl;
    os << "Sold items: " << _sold_nm << std::endl;
    os << "Item price: " << _price << std::endl;
}

void Employee::fwrite(std::ofstream& os) const {
    os.write((char*) &_type, sizeof(int32_t));
    os.write(_name.c_str(), sizeof(char) * (_name.size() + 1));
    os.write((char*) &_base_salary, sizeof(int32_t));
}

void Developer::fwrite(std::ofstream& os) const {
    Employee::fwrite(os);
    os.write((char*) &_has_bonus, sizeof(bool));
}

void SalesManager::fwrite(std::ofstream& os) const {
    Employee::fwrite(os);
    os.write((char*) &_sold_nm, sizeof(int32_t));
    os.write((char*) &_price, sizeof(int32_t));
}

int32_t EmployeesArray::get_size() const {
    return employees.size();
}

Employee* EmployeesArray::get(int index) const {
    return employees[index];
}

Employee* employee_factory(int type) {
    if (type == 1) {
        return new Developer();
    } else {
        return new SalesManager();
    }
}

Employee* Employee::create_from_istream(std::istream& in) {
    int type;
    in >> type;
    Employee* e = employee_factory(type);
    in >> *e;
    return e;
}

Employee* Employee::create_from_file(std::ifstream& in) {
    int type = 0;
    in.read((char*) &type, sizeof(int32_t));
    Employee* e = employee_factory(type);
    in >> *e;
    return e;
}


std::ofstream& operator<<(std::ofstream& os, EmployeesArray const& a) {
    int cur_size = a.employees.size();
    os.write((char*) &cur_size, sizeof(int32_t));
    for (int32_t i = 0; i < cur_size; i++) {
        os << *(a.employees[i]);
    }
    return os;
}

std::ifstream& operator>>(std::ifstream& is, EmployeesArray& a) {
    int32_t cur_size = 0;
    is.read((char*) &cur_size, sizeof(int32_t));
    for (int32_t i = 0; i < cur_size; i++) {
        a.employees.push_back(Employee::create_from_file(is));
    }
    return is;
}