#include "OnlineShop.h"

int main(){
    int task;
    OnlineShop* shop = OnlineShop::getInstance();
    shop->addUser(new User("Ali"));
    shop->addManager(new Manager("Hamza"));
    shop->addUser(new User("Junaid"));
    shop->addManager(new Manager("Sheikh"));
    shop->displayUsers();
    shop->displayManager();
    shop->CloseSystem();

    return 0;
}