#include "OnlineShop.h"

int main(){
    OnlineShop* shop = OnlineShop::getInstance();
    shop->RunSystem();
    shop->CloseSystem();

    return 0;
}