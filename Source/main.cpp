#include <iostream>
#include "Harness.h"

class App : public conics::Harness{

};

int main(){
    App* a = new App;
    a->run(a);
    return 0;
}
