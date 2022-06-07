#include <iostream>
#include "mystore.h"

int main() {
    auto base = PriceBase::instance();
    Order ord1;
    std::cout << ord1.empty() << std::endl;
    ord1.add_position(&WeightPosition(base.get_weight_product_price("Apple"), 0.5))

    return 0;
}
