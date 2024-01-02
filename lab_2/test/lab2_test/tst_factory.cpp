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
    std::string id = "mock";
    bool registration_success = Factory<MockProduct, std::string,
    std::function<MockProduct*()>>::GetInstance()->RegisterInstance(id, []() { return new MockProduct(); });
    bool is_registred = Factory<MockProduct, std::string,
                                std::function<MockProduct*()>>::GetInstance()->IsRegistred("mock");

    ASSERT_TRUE(registration_success);
    ASSERT_TRUE(is_registred);
}

TEST(FactoryTest, RegisterInstanceOverwritePrevention) {
    using factory = Factory<MockProduct, std::string, std::function<MockProduct*()>>;

    std::string id = "mock1";
    factory::GetInstance()->RegisterInstance(id, []() -> MockProduct* { return new MockProduct(); });
    bool registration_success = factory::GetInstance()->RegisterInstance(id, []() -> MockProduct* { return new MockProduct(); });

    ASSERT_FALSE(registration_success);
}

TEST(FactoryTest, IsRegistered) {
    using factory = Factory<MockProduct, std::string, std::function<MockProduct*()>>;
    std::string id = "mock2";

    bool pre_registration = factory::GetInstance()->IsRegistred(id);
    factory::GetInstance()->RegisterInstance(id, []() { return new MockProduct(); });
    bool post_registration = factory::GetInstance()->IsRegistred(id);

    ASSERT_FALSE(pre_registration);
    ASSERT_TRUE(post_registration);
}

TEST(FactoryTest, CreateObjectSuccess) {
    using factory = Factory<MockProduct, std::string, std::function<MockProduct*()>>;
    std::string id = "mock3";

    factory::GetInstance()->RegisterInstance(id, []() { return new MockProduct(); });
    std::unique_ptr<MockProduct> product = std::unique_ptr<MockProduct>(factory::GetInstance()->CreateObject(id));

    ASSERT_NE(product, nullptr);
    EXPECT_EQ(product->Foo(), "FOOO");
}

TEST(FactoryTest, CreateObjectUnregisteredID) {
    using factory = Factory<MockProduct, std::string, std::function<MockProduct*()>>;
    std::string id = "mock4";

    EXPECT_THROW({std::unique_ptr<MockProduct> product = std::unique_ptr<MockProduct>(factory::GetInstance()->
                CreateObject(id));}, std::out_of_range);
}

