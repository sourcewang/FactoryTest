#include "FactoryMethod.h"
#include <iostream>

// ���� Ь��
class Shoes
{
public:
    Shoes()
    {
        std::cout << "Ь�� ����" << std::endl;
    }

    ~Shoes()
    {
        std::cout << "Ь�� ����" << std::endl;
    }
    virtual void Show() = 0;
   // virtual ~Shoes() = default;
};

// �Ϳ�Ь��
class NiKeShoes : public Shoes
{
public:
    void Show()
    {
        std::cout << "�����Ϳ���Ь���ҵĹ���Just do it" << std::endl;
    }
    NiKeShoes()
    {
        std::cout << "�Ϳ���Ь ����" << std::endl;
    }

    ~NiKeShoes()
    {
        std::cout << "�Ϳ���Ь ����" << std::endl;
    }
};

// ���� �·�
class Clothe
{
public:
    Clothe()
    {
        std::cout << "�·� ����" << std::endl;
    }

    ~Clothe()
    {
        std::cout << "�·� ����" << std::endl;
    }
    virtual void Show() = 0;
  //  virtual ~Clothe() = default;
};

// ���¿��·�
class UniqloClothe : public Clothe
{
public:
    void Show()
    {
        std::cout << "�������¿��·����ҵĹ���I am Uniqlo" << std::endl;
    }

    UniqloClothe()
    {
        std::cout << "���¿��·� ����" << std::endl;
    }

    ~UniqloClothe()
    {
        std::cout << "���¿��·� ����" << std::endl;
    }
};


int main()
{
    {
        // ========================== �����Ϳ���Ь���� ===========================//
        thatboy::ProductRegistrar<Shoes, NiKeShoes> nikeShoes("nike");
        auto pNiKeShoes = thatboy::ProductFactory<Shoes>::Instance().GetProduct("nike");
        auto pNiKeShoes2 = thatboy::ProductFactory<Shoes>::Instance().GetProduct("nike");

        pNiKeShoes->Show();
    }
    {
        // ========================== �������¿��·����� ===========================//
        thatboy::ProductRegistrar<Clothe, UniqloClothe> adidasShoes("uniqlo");
        auto pUniqloClothe = thatboy::ProductFactory<Clothe>::Instance().GetProduct("uniqlo");

        pUniqloClothe->Show();
    }
    return 0;
}