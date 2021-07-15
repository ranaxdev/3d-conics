#include <iostream>
#include "Harness.h"

class App : public conics::Harness{
public:
    void render(float currentTime) override {
    }
};

int main(){
    App* a = new App;
    a->run(a);
    return 0;
}
