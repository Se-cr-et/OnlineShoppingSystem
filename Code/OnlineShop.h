#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Catalog; 

// General Class, Used by: [Cart, Catalog]
class Product{
private:
    static int productCount;
    int productID;
    string name;
    string category;
    int price;
    int quantity;
public:
    Product(string pName, string pCategory, int pPrice, int pQuantity);
    int getProductID();
    string getName();
    string getCategory();
    int getPrice();
    int getQuantity();
    Product& operator--();
    ~Product();
};


// General Class, Children: [User, Manager]
class Person{
protected:
    string username;
    string password;
public:
    Person(string uName, string uPassword);
    string getUsername();
    string getPassword();
    virtual void display() = 0;
    virtual ~Person();
};


// Cart
class Cart{
private:
    vector<int> productQuantity;
    vector<Product*> product;
public:
    Cart();
    Cart& addProduct(Product& P, int pQuantity);
    void removeProduct(Product& P, int _prodID);
    Product* searchProduct(int _prodID);
    void loggingCart(fstream& _file);
    void reloggingCart(fstream& _file, Catalog& Catalog);
    void checkout_helper(fstream& _file);
    ~Cart();
};


// User
class User: public Person{
private:
    static int userCount;
    int userID;
    Cart cart;
public:
    User(string uName, string uPassword);
    void display() override;
    int getUserID();
    void addProduct(Product& P, int pQuantity);
    void removeProduct(Product& P, int prodID);
    void loggingUser(fstream& _file);
    void reloggingUser(fstream& _file, Catalog& Catalog);
    void storeCart();
    void checkout();
    ~User() override;
};



// Catalog
class Catalog{
private:
    vector<string> category;
    vector<Product*> product;
public:
    Catalog();
    void loggingCatalog(fstream& _file);
    Product* searchProduct(int proID);
    int searchProductIndex(int _proID);
    void reloggingCatalog(fstream& _file);
    void categoryDisplay();
    void unfilteredDisplay();
    void filteredDisplay(string Categor);
    Catalog& operator+=(string C);
    Catalog& operator+=(Product& P);
    Catalog& operator-=(string C);
    Catalog& operator-=(int _prodID);
    ~Catalog();
};


// Manager
class Manager: public Person{
private:
    static int managerCount;
    int managerID;
public:
    Manager(string uName, string uPassword);
    int getManagerID();
    void loggingManager(fstream& _file);
    void reloggingManager(fstream& _file);
    void display() override;
    ~Manager() override;
};



// Singleton Class
class OnlineShop{
private:
    Catalog catalog;
    vector<User*> user;
    vector<Manager*> manager;

    static OnlineShop* shopPtr;

    OnlineShop();
public:
    static OnlineShop* getInstance();
    void addCategory(string C);
    void addProduct(Product& P);
    void addUser(User* U);
    void addManager(Manager* M);
    void RunSystem();
    void CloseSystem();
    ~OnlineShop();
};