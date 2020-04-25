#pragma once

#ifndef _FACTORYMETHOD_H_
#define _FACTORYMETHOD_H_

#include <map>
#include <memory>
#include <string>

namespace thatboy
{
    // 基类，产品注册模板接口类
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

    // 工厂模板类，用于获取和注册产品对象
    template <class ProductType_t>
    class ProductFactory
    {
    public:
        static ProductFactory<ProductType_t>& Instance()
        {
            static ProductFactory<ProductType_t> instance;
            return instance;
        }

        // 产品注册
        void RegisterProduct(IProductRegistrar<ProductType_t>* registrar, std::string name)
        {
            m_ProductRegistry[name] = registrar;
        }

        // 根据名字，获取对应具体的产品对象
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

        // 保存注册过的产品，key:产品名字 , value:产品类型
        std::map<std::string, IProductRegistrar<ProductType_t>*> m_ProductRegistry;
    };

    // 产品注册模板类，用于创建具体产品和从工厂里注册产品
    template <class ProductType_t, class ProductImpl_t>
    class ProductRegistrar : public IProductRegistrar<ProductType_t>
    {
    public:
        // 构造函数，用于注册产品到工厂，只能显示调用
        explicit ProductRegistrar(std::string name)
        {
            // 通过工厂单例把产品注册到工厂
            ProductFactory<ProductType_t>::Instance().RegisterProduct(this, name);
        }
        // 创建具体产品对象指针
        std::shared_ptr<ProductType_t> CreateProduct()
        {
            return std::make_shared<ProductImpl_t>();
        }
    };
}

#endif