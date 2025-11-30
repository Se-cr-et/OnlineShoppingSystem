#pragma once
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


// [Restriction]
// Because of an annoying restriction present in the project description
// I was forced to create a useless class named "Category", which provides
// inheritance to "Product". Otherwise product would have existed alone
// [/Restriction]


// Pretty much useless class
class Category{
private:
    string name;
    string description;
public:
    Category(string pName, string pDescription);
    string getName();
    string getDescription();
    virtual void display();
    virtual ~Category();
};


// Stores detail on each Product
class Product: public Category{
private:
    int productID;
    int price;
    int quantity;
public:
    Product(string pName, string pDescription, int pProductID, int pPrice, int pQuantity);
    int getProductID();
    int getPrice();
    int getQuantity();
    Product& operator--();
    void display() override;
    ~Product() override;
};


// Stores all the product that were added to the cart
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
class User{
private:
    static int userID;
    string username;
    Cart cart;
public:
    User(string uName);
    void checkout();
    ~User();
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
    Catalog& operator+=(Product& P);
    ~Catalog();
};


class Manager{
private:

public:
};


// Singleton Class
class OnlineShop{
private:
    OnlineShop();

    Catalog catalog();
    Cart cart();
    Order order();

    static OnlineShop* shopPtr;
public:
    static OnlineShop getInstance();
    void run();
};


class Order{

};
