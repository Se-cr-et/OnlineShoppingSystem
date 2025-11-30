#include "OnlineShop.h"


//
Category::Category(string pName, string pDescription) : name(pName), description(pDescription) {}

string Category::getName(){
    return name;
}

string Category::getDescription(){
    return description;
}

Category::~Category(){}
//



//
Product::Product(string pName, string pDescription, int pProductID, int pPrice, int pQuantity):
 Category(pName, pDescription), productID(pProductID), price(pPrice), quantity(pQuantity) {}

int Product::getProductID(){
    return productID;
}

int Product::getPrice(){
    return price;
}

int Product::getQuantity(){
    return quantity;
}

Product& Product::operator--(){
    quantity--;
    return *this;
}

Product::~Product(){}
//



//
Cart::Cart() {}

Cart& Cart::addProduct(Product& P, int pPrice){
    product.push_back(&P);
    productQuantity.push_back(pPrice);
    return *this;
}

void Cart::checkout_helper(fstream& _file){
    _file << "Name|";
    _file << "ProductID|";
    _file << "Price|";
    _file << "Quantity|";
    _file << "Amount|";
    _file << "\n";

    for (int i = 0; i < product.size(); i++){
        _file << product[i]->getName() << "|";
        _file << product[i]->getProductID() << "|";
        _file << product[i]->getPrice() << "|";
        _file << productQuantity[i] << "|";
        _file << productQuantity[i]*product[i]->getPrice() << "|";
        _file << "\n";
    }

    _file << "\nTotal Cost: ";
    int sum = 0;
    for (int i = 0; i < product.size(); i++){
        sum += productQuantity[i]*product[i]->getPrice();
    }
    _file << sum;
}

Cart::~Cart(){
    for (int i = 0; i < product.size(); i++){
        delete[] product[i];
    }
}
//



//
User::User(string uName): username(uName) {userID++;}

void User::checkout(){
    fstream file;
    file.open("UserCart" + to_string(userID) + ".txt", ios::out);

    if (file.is_open()){
        file << userID << "\n";
        cart.checkout_helper(file);
    }
}

User::~User(){}
//



//
Catalog::Catalog(){}
void Catalog::Save(){
    fstream file;
    file.open("Catalog.txt", ios::out);
    if (file.is_open()){
        for (int i = 0; i < category.size(); i++){
            file << category[i] << "|";
        }
        file << "\n";

        for (int i = 0; i < product.size(); i++){
            file << product[i]->getName() << "|";
            file << product[i]->getDescription() << "|";
            file << product[i]->getPrice() << "|";
            file << product[i]->getQuantity() << "|";
            file << "\n";
        }
    }
}
Catalog& Catalog::operator+=(Product& P){
    product.push_back(&P);
}
Catalog::~Catalog(){
    for (int i = 0; i < product.size(); i++){
        delete[] product[i];
    }
}

//



OnlineShop::OnlineShop(){}
OnlineShop OnlineShop::getInstance(){
    if (shopPtr == nullptr){
        shopPtr = new OnlineShop();
    }
    else{
        cout << "[SYSTEM ALREADY RUNNING]\n\n";
    }
}

