#include <map>
#include <algorithm>

#ifndef FACTORY_H
#define FACTORY_H

template <typename Product, typename ID, typename Creator>
class Factory{
  public:
    static Factory* GetInstance(){
        static Factory f;
        return &f;
    }

    Product* CreateObject(ID id){
        auto creator = RegistredCreatorMap_.at(id);
        return creator();
    }

    bool IsRegistred(ID id){
        return RegistredCreatorMap_.find(id) != RegistredCreatorMap_.end();
    }

    bool RegisterInstance(ID id, Creator creator){
        if(IsRegistred(id)){
            return false;
        }
        RegistredCreatorMap_[id] = creator;
        return true;
    }
  private:
    Factory() = default;
    Factory(Factory&) = delete;
    Factory(Factory&&) = delete;
    Factory& operator=(Factory&) = delete;
    Factory& operator=(Factory&&) = delete;
    std::map<ID, Creator> RegistredCreatorMap_;
};

#endif // FACTORY_H
