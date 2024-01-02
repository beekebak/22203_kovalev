#include <functional>
#include "factory.h"

#ifndef FACTORY_INITIALIZATOR_H
#define FACTORY_INITIALIZATOR_H

template <typename Product, typename ID, typename ExactCreator>
class FactoryInitializator{
  public:
    FactoryInitializator(ID id){
        Factory<Product, ID, std::function<Product*()>>::GetInstance()->
            RegisterInstance(id, CreateNewExactProduct);
    }
  private:
    static Product* CreateNewExactProduct(){
        return new ExactCreator();
    }
};

#endif
