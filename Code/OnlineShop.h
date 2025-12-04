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
    // Deals with Products in Cart
    Product* searchProduct(int _prodID);
      // Also helper methods
    Cart& addProduct_helper(Product& P, int pQuantity);
    void removeProduct_helper(Product& P, int _prodID);

    // Data Persistence
    void loggingCart(fstream& _file);
    void reloggingCart(fstream& _file, Catalog& Catalog);

    // Helper Methods for User Class
    void viewCart_helper();
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

    // Deals with Products in Cart
    void addProduct(Product& P, int pQuantity);
    void removeProduct(Product& P, int prodID);

    // Data Persistence
    void loggingUser(fstream& _file);
    void reloggingUser(fstream& _file, Catalog& Catalog);

    // Cart Terminal View and Receipt Creation
    void viewCart();
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

    // Product Search
    Product* searchProduct(int proID);
    int searchProductIndex(int _proID);

    // Menu Display Utilities
    void categoryDisplay();
    void unfilteredDisplay();
    void filteredDisplay(string Categor);

    // Data Persistence
    void loggingCatalog(fstream& _file);
    void reloggingCatalog(fstream& _file);

    // Category Operations
    Catalog& operator+=(string C);
    Catalog& operator-=(string C);

    // Product Operations
    Catalog& operator+=(Product& P);
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
    void display() override;

    // Data Persistence
    void loggingManager(fstream& _file);
    void reloggingManager(fstream& _file);
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

    // System Operations
    void addCategory(string C);
    void addProduct(Product& P);
    void addUser(User* U);
    void addManager(Manager* M);

    // System Booting
    void RunSystem();
    void CloseSystem();
    ~OnlineShop();
};