#include <iostream>
#include "mystore.h"

int main() {
    /*auto base = PriceBase::instance();
    Order ord1;
    std::cout << ord1.empty() << std::endl;

    auto wp1 = base.get_weight_product_price("Apple");
    auto pos1 = WeightPosition(wp1, 0.5);
    ord1.add_position(&pos1);
    ord1.get_info();

    auto ap1 = base.get_amount_product_price("Pencil");
    auto pos2 = AmountPosition(ap1, 7);
    ord1.add_position(&pos2);
    ord1.get_info();

    auto ap2 = base.get_amount_product_price("Pencil");
    auto pos3 = AmountPosition(ap1, 2);
    ord1.add_position(&pos3);
    ord1.get_info();

    auto wp2 = base.get_weight_product_price("Apple");
    auto pos4 = WeightPosition(base.get_weight_product_price("Apple"), 0.5);
    ord1.add_position(&pos4);
    ord1.get_info();

    Client Ivan;
    Order ord2;
    Ivan.pay_and_receive_order(ord2);
    /*Ivan.pay_and_receive_order(ord1);
    Ivan.earn_money(10000);
    Ivan.pay_and_receive_order(ord1);
    ord1.get_info();*/

    ProductInfo info("information bout product");
    AmountProduct prod(ProductInfo("Information shit"), 20);
    //AmountProduct prod(info, 30);
    AmountPosition pos(prod, 5);
    Order ord1;
    ord1.add_position(&pos);
    ord1.get_info();



    return 0;
}
