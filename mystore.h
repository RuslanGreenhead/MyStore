#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>
#include <functional>


//---------------------------------------Product architecture----------------------------------------//
class ProductInfo{
public:
    explicit ProductInfo(std::string info) : m_info(std::move(info)) {};
    std::string get_info() { return m_info; }

private:
    std::string m_info;
};

class Product{
public:
    explicit Product(ProductInfo& product_info) : m_product_info(product_info) {};
    virtual std::string get_info() { return m_product_info.get_info(); }
    virtual double get_price() = 0;

protected:
    ProductInfo& m_product_info;
};

class WeightProduct : public Product{
public:
    WeightProduct(ProductInfo& product_info, double cost_per_kg) :
            Product(product_info), m_price_per_kg(cost_per_kg) {};
    double get_price() override { return m_price_per_kg; }
    std::string get_info() override {
        std::stringstream oss;
        oss << std::noshowpoint << get_price();
        return m_product_info.get_info() + " : " + oss.str() + " per kg";
    }

private:
    double m_price_per_kg;
};

class AmountProduct : public Product{
public:
    AmountProduct(ProductInfo& product_info, double cost_per_one) :
            Product(product_info), m_price_per_one(cost_per_one) {};
    double get_price() override { return m_price_per_one; }
    std::string get_info() override {
        std::stringstream oss;
        oss << std::noshowpoint << get_price();
        return m_product_info.get_info() + " : " + oss.str() + " per one";
    }

private:
    double m_price_per_one;
};


//-----------------------------------------Position architecture--------------------------------------//

class Position{
public:
    explicit Position(const Product& product) : m_ptr_product(const_cast<Product *>(&product)){};
    Product* get_ptr_product() { return m_ptr_product; }
    virtual double get_cost() = 0;
    virtual double get_amount() = 0;

protected:
    Product* m_ptr_product;
};

class AmountPosition : public Position{
public:
    AmountPosition(const Product& product, size_t quantity) :
            Position(product), m_quantity(quantity) {};
    double get_cost() override { return m_ptr_product->get_price() * m_quantity; }
    double get_amount() override { return m_quantity; }

private:
    size_t m_quantity;
};

class WeightPosition : public Position{
public:
    WeightPosition(const Product& product, double weight) :
            Position(product), m_weight(weight) {};
    double get_cost() override { return m_ptr_product->get_price() * m_weight; }
    double get_amount() override { return m_weight; }

private:
    double m_weight;
};


//-----------------------------------------Order & Client----------------------------------------//

class Order{
public:
    Order() = default;
    void add_position(Position* ptr_pos) {
        for(auto& el : m_ptr_positions){  // <- Range-based loop with link
            if (el->get_ptr_product() == ptr_pos->get_ptr_product()){
                el = ptr_pos;
                return;
            }

            // Strategy if we will track not same Products but equal:
            /*
             if(*(el->get_ptr_product()) == *(ptr_pos->get_ptr_product())){
                el->m_quantity = ptr_pos->m_quantity;
             }
             */
        }
        m_ptr_positions.push_back(ptr_pos);
    }
    double get_cost(){
        double res = 0;
        for (auto el : m_ptr_positions){
            res += el->get_cost();
        }
        return res;
    }
    void get_info(){
        if (empty()){
            std::cout << "Order is empty" << std::endl;
            return;
        }
        double total = 0;
        std::cout << "Info about the order:" << std::endl;
        for(auto el : m_ptr_positions){
            std::cout << el->get_ptr_product()->get_info() << std::endl;
            std::cout << "\tAmount: " << el->get_amount() << std::endl;
            std::cout << "\tCost: " << el->get_cost() << std::endl;
            total += el->get_cost();
        }
        std::cout << "Total cost: " << total << std::endl;
    }
    bool empty() { return m_ptr_positions.empty(); }

private:
    std::vector<Position*> m_ptr_positions;
    void clear() { m_ptr_positions.clear(); }
    friend class Client;
};

class Client{
    class Balance{
    public:
        void add_money(double money) { m_money += money; }
        bool waste_money(double money) {
            if(m_money >= money) m_money -= money;
            else{ return false; }
            return true;
        }
    private:
        double m_money = 0;
    };

public:
    void earn_money(double money) { m_balance.add_money(money); }
    bool pay_and_receive_order(Order& order){
        if (not m_balance.waste_money(order.get_cost())){
            std::cout << "Sorry I ain't got no money..." << std::endl;
            return false;
        } else{
            order.clear();
            return true;
        }
    }

private:
    Balance m_balance;
};


//-----------------------------------------Dummy database----------------------------------------//

// << singleton >>
class PriceBase{
public:
    static PriceBase& instance(){
        static PriceBase obj;
        return obj;
    }
    WeightProduct get_weight_product_price(const std::string& name) { return m_products_weight_price.at(name); }
    AmountProduct get_amount_product_price(const std::string& name) { return m_products_amount_price.at(name); }
private:
    std::map<std::string, ProductInfo> m_products_info;
    std::map<std::string, WeightProduct> m_products_weight_price;
    std::map<std::string, AmountProduct> m_products_amount_price;
protected:
    PriceBase() {
        m_products_info = {
                { "Apple", ProductInfo("Green sweet apple") },
                { "Nuts", ProductInfo("Macadamia nut") },
                { "Pencil", ProductInfo("Red pencil with rubber") },
                { "Chair", ProductInfo("Wooden chair with armrests") },
        };
        m_products_weight_price = {
                { "Apple", WeightProduct(m_products_info.at("Apple"), 11.3) },
                { "Nuts", WeightProduct(m_products_info.at("Nuts"), 34.2) },
        };
        m_products_amount_price = {
                { "Pencil", AmountProduct(m_products_info.at("Pencil"), 5.7) },
                { "Chair", AmountProduct(m_products_info.at("Chair"), 75) },
        };
    }
};


//-----------------------------------------Utilities----------------------------------------//

/*bool greater_equal(double a, double b, ){
    return (a - b)
}*/