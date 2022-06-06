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


//--------------------------------------All 'bout position-----------------------------------//

class Position{
public:
    Position(Product& product) : m_ptr_product(&product){};
    Product* get_ptr_product() { return m_ptr_product; }
    virtual double get_cost() = 0;
    virtual double get_quantity() = 0;
protected:
    Product* m_ptr_product;
};

class AmountPosition : public Position{
public:
    AmountPosition(AmountProduct product, size_t amount) :
            Position(product), m_amount(amount) {};
    virtual double get_cost() override { return m_ptr_product->get_cost(); }
    virtual double get_quantity() override { return m_amount; }
private:
    size_t m_amount;
};

class WeightPosition : public Position{
public:
    WeightPosition(WeightProduct product, double weight) :
            Position(product), m_weight(weight) {};
    virtual double get_cost() override { return m_ptr_product->get_cost(); }
    virtual double get_quantity() override { return m_weight; }
private:
    double m_weight;
};
