//
// Tests for mystore.h package
//

#pragma once

#include "mystore.h"

// Initial test from technical task
void test_1(){
    auto base = PriceBase::instance();
    Order ord1;
    std::cout << std::boolalpha << ord1.empty() << std::endl;

    auto pos1 = WeightPosition(std::make_unique<WeightProduct>(base.get_weight_product_price("Apple")), 0.5);
    ord1.add_position(&pos1);
    ord1.get_info();
    std::cout << std::endl;

    auto ap1 = base.get_amount_product_price("Pencil");
    auto pos2 = AmountPosition(std::make_unique<AmountProduct>(ap1), 2);
    ord1.add_position(&pos2);
    ord1.get_info();
    std::cout << std::endl;

    auto pos3 = WeightPosition(std::make_unique<WeightProduct>(base.get_weight_product_price("Apple")), 3);
    ord1.add_position(&pos3);
    ord1.get_info();
    std::cout << std::endl;

    Client Ivan;
    Ivan.pay_and_receive_order(ord1);
    Ivan.earn_money(10000);
    Ivan.pay_and_receive_order(ord1);
    ord1.get_info();
}

// Empty order
void test_2(){
    Order ord0;
    ord0.get_info();
    std::cout << std::endl;

    Client Vadim;
    Vadim.pay_and_receive_order(ord0);
    ord0.get_info();
    std::cout << std::endl;
};

// No rvalue ProductInfo passing to Product
/*void test_3(){
    ProductInfo info("information bout product");
    AmountProduct prod(ProductInfo("Temporary ProductInfo object"), 20);
    //AmountProduct prod(info, 30);
    //AmountPosition pos(prod, 5);
    Order ord1;
    //ord1.add_position(&pos);
    ord1.get_info();
}*/
