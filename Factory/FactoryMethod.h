#pragma once

#ifndef _FACTORYMETHOD_H_
#define _FACTORYMETHOD_H_

#include <map>
#include <memory>
#include <string>

namespace thatboy
{
    // ���࣬��Ʒע��ģ��ӿ���
    template <class ProductType_t>
    class IProductRegistrar
    {
    public:
        virtual std::shared_ptr<ProductType_t> CreateProduct() = 0;
    protected:
        IProductRegistrar() = default;
        virtual ~IProductRegistrar() = default;
        IProductRegistrar(const IProductRegistrar&) = delete;
        IProductRegistrar& operator=(const IProductRegistrar&) = delete;
    };

    // ����ģ���࣬���ڻ�ȡ��ע���Ʒ����
    template <class ProductType_t>
    class ProductFactory
    {
    public:
        static ProductFactory<ProductType_t>& Instance()
        {
            static ProductFactory<ProductType_t> instance;
            return instance;
        }

        // ��Ʒע��
        void RegisterProduct(IProductRegistrar<ProductType_t>* registrar, std::string name)
        {
            m_ProductRegistry[name] = registrar;
        }

        // �������֣���ȡ��Ӧ����Ĳ�Ʒ����
        std::shared_ptr<ProductType_t> GetProduct(std::string name)
        {
            if (m_ProductRegistry.find(name) != m_ProductRegistry.end())
                return m_ProductRegistry[name]->CreateProduct();
            else
                return nullptr;
        }

    protected:
        ProductFactory() = default;
        ~ProductFactory() = default;
        ProductFactory(const ProductFactory&) = delete;
        ProductFactory& operator=(const ProductFactory&) = delete;

        // ����ע����Ĳ�Ʒ��key:��Ʒ���� , value:��Ʒ����
        std::map<std::string, IProductRegistrar<ProductType_t>*> m_ProductRegistry;
    };

    // ��Ʒע��ģ���࣬���ڴ��������Ʒ�ʹӹ�����ע���Ʒ
    template <class ProductType_t, class ProductImpl_t>
    class ProductRegistrar : public IProductRegistrar<ProductType_t>
    {
    public:
        // ���캯��������ע���Ʒ��������ֻ����ʾ����
        explicit ProductRegistrar(std::string name)
        {
            // ͨ�����������Ѳ�Ʒע�ᵽ����
            ProductFactory<ProductType_t>::Instance().RegisterProduct(this, name);
        }
        // ���������Ʒ����ָ��
        std::shared_ptr<ProductType_t> CreateProduct()
        {
            return std::make_shared<ProductImpl_t>();
        }
    };
}

#endif