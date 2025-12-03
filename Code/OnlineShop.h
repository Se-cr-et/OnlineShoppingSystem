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
    string name;
    string category;
    int productID;
    int price;
    int quantity;
public:
    Product(int pProductID, string pName, int pPrice, int pQuantity);
    string getName();
    string getCategory();
    int getProductID();
    int getPrice();
    int getQuantity();
    Product& operator--();
    ~Product();
};


// General Class, Children: [User, Manager]
class Person{
protected:
    string username;
public:
    Person(string uName);
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
    User(string uName);
    void display() override;
    int getUserID();
    string getUsername();
    void addProduct(Product& P, int pQuantity);
    void removeProduct(Product& P, int prodID);
    void loggingUser(fstream& _file);
    void reloggingUser(fstream& _file, Catalog& Catalog, int ID);
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
    void reloggingCatalog(fstream& _file);
    void categoryDisplay();
    void normalDisplay();
    void searchDisplay(string Categor);
    void Save();
    Catalog& operator+=(string C);
    Catalog& operator+=(Product& P);
    ~Catalog();
};


// Manager
class Manager: public Person{
private:
    static int managerCount;
    int managerID;
public:
    Manager(string uName);
    void loggingManager(fstream& _file);
    void reloggingManager(fstream& _file, int ID);
    void display() override;
    int getManagerID();
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