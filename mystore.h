#pragma once

#include <iostream>


//------------------------------------All 'bout products-------------------------------------//
class ProductInfo{
public:
    ProductInfo(std::string info) : m_info(info) {};
    std::string get_info() { return m_info; }
private:
    std::string m_info;
};

class Product{
public:
    Product(ProductInfo product_info) : m_product_info(product_info) {};
    virtual std::string get_info() { return m_product_info.get_info(); }
    virtual double get_cost() = 0;
protected:
    ProductInfo m_product_info;
};

class WeightProduct : public Product{
    WeightProduct(ProductInfo product_info, double cost_per_kg) :
            Product(product_info), m_cost_per_kg(cost_per_kg) {};
    double get_cost() override { return m_cost_per_kg; }
    std::string get_info() override {return m_product_info.get_info() + " : " + std::to_string(get_cost()); }

private:
    double m_cost_per_kg;
};

class AmountProduct : public Product{
    AmountProduct(ProductInfo product_info, double cost_per_one) :
            Product(product_info), m_cost_per_one(cost_per_one) {};
    double get_cost() override { return m_cost_per_one; }
    std::string get_info() override {return m_product_info.get_info() + " : " + std::to_string(get_cost()); }

private:
    double m_cost_per_one;
};
