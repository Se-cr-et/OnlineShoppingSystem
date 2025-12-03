#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


// General Class, Used by: [Cart, Catalog]
class Product{
private:
    string name;
    string description;
    string category;
    int productID;
    int price;
    int quantity;
public:
    Product(string pName, string pDescription, int pProductID, int pPrice, int pQuantity);
    string getName();
    string getDescription();
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
    Product& searchProduct(int _prodID);
    void loggingCart(fstream& _file);
    void reloggingCart(fstream& _file);
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
    void loggingUser(fstream& _file);
    void reloggingUser(fstream& _file);
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
    void displayUsers();
    void displayManager();
    void RunSystem();
    void CloseSystem();
    ~OnlineShop();
};