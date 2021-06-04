#ifndef LAB11_EMPLOYEES_H_INCLUDED
#define LAB11_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

class Employee {
public:
    Employee();
    Employee(int type);
    Employee(std::string name, int32_t _base_salary, int type);
    ~Employee();
    virtual int salary() const = 0;
    virtual void write(std::ostream& os) const = 0;
    virtual void read(std::istream &is) = 0;
    virtual void fwrite(std::ofstream& os) const = 0;
    virtual void fread(std::ifstream &is) = 0;
    static Employee* create_from_istream(std::istream& in);
    static Employee* create_from_file(std::ifstream& in);
    friend std::istream& operator>> (std::istream& is, Employee& m);
    friend std::ostream& operator<< (std::ostream& os, const Employee& m);
    friend std::ifstream& operator>> (std::ifstream& is, Employee& m);
    friend std::ofstream& operator<< (std::ofstream& os, const Employee& m); 
protected:
    std::string _name;
    int32_t _base_salary;
    int32_t _type;
};

class Developer : public Employee {
public:
    Developer();
    Developer(std::string name, int32_t _base_salary, bool _has_bonus); 
    int salary() const;
    void write(std::ostream& os) const;
    void read(std::istream &is) ;
    void fwrite(std::ofstream& os) const;
    void fread(std::ifstream &is);
private:
    bool _has_bonus;
};

class SalesManager : public Employee {
public:
    SalesManager();
    SalesManager(std::string name, int32_t _base_salary, int32_t _sold_nm, int32_t _price);    
    int salary() const;
    void write(std::ostream& os) const;
    void read(std::istream &is);
    void fwrite(std::ofstream& os) const;
    void fread(std::ifstream &is);
private:
    int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
    void add(Employee *e);
    int total_salary() const;
    int32_t get_size() const;
    Employee* get(int index) const;

    friend std::ifstream& operator >>(std::ifstream& in, EmployeesArray & a);
    friend std::ofstream& operator <<(std::ofstream& out, EmployeesArray const & a);
    friend std::ostream& operator <<(std::ostream& out, EmployeesArray const & a);
protected:
    std::vector<Employee*> employees;
};

#endif
