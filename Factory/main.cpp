#include "FactoryMethod.h"
#include <iostream>

// 基类 鞋子
class Shoes
{
public:
    Shoes()
    {
        std::cout << "鞋子 制造" << std::endl;
    }

    ~Shoes()
    {
        std::cout << "鞋子 销毁" << std::endl;
    }
    virtual void Show() = 0;
   // virtual ~Shoes() = default;
};

// 耐克鞋子
class NiKeShoes : public Shoes
{
public:
    void Show()
    {
        std::cout << "我是耐克球鞋，我的广告语：Just do it" << std::endl;
    }
    NiKeShoes()
    {
        std::cout << "耐克球鞋 制造" << std::endl;
    }

    ~NiKeShoes()
    {
        std::cout << "耐克球鞋 销毁" << std::endl;
    }
};

// 基类 衣服
class Clothe
{
public:
    Clothe()
    {
        std::cout << "衣服 制造" << std::endl;
    }

    ~Clothe()
    {
        std::cout << "衣服 销毁" << std::endl;
    }
    virtual void Show() = 0;
  //  virtual ~Clothe() = default;
};

// 优衣库衣服
class UniqloClothe : public Clothe
{
public:
    void Show()
    {
        std::cout << "我是优衣库衣服，我的广告语：I am Uniqlo" << std::endl;
    }

    UniqloClothe()
    {
        std::cout << "优衣库衣服 制造" << std::endl;
    }

    ~UniqloClothe()
    {
        std::cout << "优衣库衣服 销毁" << std::endl;
    }
};


int main()
{
    {
        // ========================== 生产耐克球鞋过程 ===========================//
        thatboy::ProductRegistrar<Shoes, NiKeShoes> nikeShoes("nike");
        auto pNiKeShoes = thatboy::ProductFactory<Shoes>::Instance().GetProduct("nike");
        auto pNiKeShoes2 = thatboy::ProductFactory<Shoes>::Instance().GetProduct("nike");

        pNiKeShoes->Show();
    }
    {
        // ========================== 生产优衣库衣服过程 ===========================//
        thatboy::ProductRegistrar<Clothe, UniqloClothe> adidasShoes("uniqlo");
        auto pUniqloClothe = thatboy::ProductFactory<Clothe>::Instance().GetProduct("uniqlo");

        pUniqloClothe->Show();
    }
    return 0;
}