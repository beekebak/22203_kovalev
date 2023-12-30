#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "factory.h"

using namespace testing;

class MockProduct {
public:
    MockProduct() = default;
    ~MockProduct() = default;
    std::string Foo(){
        return "FOOO";
    }
};

TEST(FactoryTest, RegisterInstance) {
    Factory<MockProduct, std::string, std::function<MockProduct*()>> factory;

    std::string id = "mock";
    bool registrationSuccess = factory.RegisterInstance(id, []() { return new MockProduct(); });

    ASSERT_TRUE(registrationSuccess);
    ASSERT_TRUE(factory.IsRegistred(id));
}

TEST(FactoryTest, RegisterInstanceOverwritePrevention) {
    Factory<MockProduct, std::string, std::function<MockProduct*()>> factory;

    std::string id = "mock";
    factory.RegisterInstance(id, []() { return new MockProduct(); });
    bool registrationSuccess = factory.RegisterInstance(id, []() { return new MockProduct(); });

    ASSERT_FALSE(registrationSuccess);
}

TEST(FactoryTest, IsRegistered) {
    Factory<MockProduct, std::string, std::function<std::unique_ptr<MockProduct>()>> factory;
    std::string id = "mock";

    bool preRegistration = factory.IsRegistred(id);
    factory.RegisterInstance(id, []() { return std::unique_ptr<MockProduct>(new MockProduct()); });
    bool postRegistration = factory.IsRegistred(id);

    ASSERT_FALSE(preRegistration);
    ASSERT_TRUE(postRegistration);
}

TEST(FactoryTest, CreateObjectSuccess) {
    Factory<MockProduct, std::string, std::function<MockProduct*()>> factory;
    std::string id = "mock";

    factory.RegisterInstance(id, []() { return new MockProduct(); });
    std::unique_ptr<MockProduct> product = std::unique_ptr<MockProduct>(factory.CreateObject(id));

    ASSERT_NE(product, nullptr);
    EXPECT_EQ(product->Foo(), "FOOO");
}

TEST(FactoryTest, CreateObjectUnregisteredID) {
    Factory<MockProduct, std::string, std::function<MockProduct*()>> factory;
    std::string id = "mock";

    EXPECT_THROW({std::unique_ptr<MockProduct> product = std::unique_ptr<MockProduct>(factory.CreateObject(id));},
                 std::out_of_range);
}

