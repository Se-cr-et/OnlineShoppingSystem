#pragma once
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;




// General Class, Used by: [Cart, Catalog]
class Product{
private:
    string name;
    string description;
    int productID;
    int price;
    int quantity;
public:
    Product(string pName, string pDescription, int pProductID, int pPrice, int pQuantity);
    string getName();
    string getDescription();
    int getProductID();
    int getPrice();
    int getQuantity();
    Product& operator--();
    ~Product();
};


// General Class, Children: [User, Manager]
class Person{
private:
    string username;
public:
    Person(string uName);
    virtual ~Person();
};


// Cart
class Cart{
private:
    vector<int> productQuantity;
    vector<Product*> product;
public:
    Cart();
    Cart& addProduct(Product& P, int pPrice);
    void checkout_helper(fstream& file);
    ~Cart();
};


// User
class User: public Person{
private:
    static int userID;
    Cart cart;
public:
    User(string uName);
    void checkout();
    ~User() override;
};
int User::userID = 0;



// Catalog
class Catalog{
private:
    vector<string> category;
    vector<Product*> product;
public:
    Catalog();
    void Save();
    Catalog& operator+=(string C);
    Catalog& operator+=(Product& P);
    ~Catalog();
};


// Manager
class Manager: public Person{
private:
    static int managerID;
public:
    Manager(string uName);
    ~Manager() override;
};
int Manager::managerID = 0;



// Singleton Class
class OnlineShop{
private:
    Catalog catalog;
    vector<User*> user;
    vector<Manager*> manager;

    static OnlineShop* shopPtr;

    OnlineShop();
public:
    static OnlineShop& getInstance();
    void addCategory(string C);
    void addProduct(Product& P);
    void run();
    ~OnlineShop();
};