#include "gtest/gtest.h"
#include "jpp/Jpp.h"

using namespace jpp::literals;

TEST(CreateJppObject, String) {
      jpp::obj temp {
          "string0"_f = "stringy0",
          "string1"_f = "stringy1",
          "string2"_f = "stringy2"
      };

    ASSERT_EQ(0, 0);
}

TEST(CreateJppObject, Number) {
    jpp::obj temp{
        "double0"_f = 3.1415926500,
        "double1"_f = 3.1415926501,
        "double2"_f = 3.1415926502
    };

    ASSERT_EQ(0, 0);
}

TEST(CreateJppObject, Integer) {
    jpp::obj temp{
        "integer0"_f = 1234500,
        "integer1"_f = 1234501,
        "integer2"_f = 1234502
    };

    ASSERT_EQ(0, 0);
}

TEST(CreateJppObject, Boolean) {
    jpp::obj temp{
        "boolean0"_f = false,
        "boolean1"_f = true
    };

    ASSERT_EQ(0, 0);
}

TEST(CreateJppObject, Arbitary) {

    struct dummy { int x; };

    jpp::obj temp{
        "struct0"_f = dummy{ 1 },
        "struct1"_f = dummy{ 2 },
        "struct2"_f = dummy{ 3 }
    };

    ASSERT_EQ(0, 0);
}

TEST(CreateJppObject, Null) {

    jpp::obj temp{
        "null"_f = nullptr,
        "null"_f = nullptr
    };

    ASSERT_EQ(0, 0);
}

TEST(CreateJppObject, All) {

    struct dummy { int x; };

    jpp::obj temp {
        "string"_f = "stringy",
        "double"_f = 3.1415,
        "integer"_f = 13245,
        "boolean"_f = false,
        "fuckall"_f = dummy{6666},
        "nothing"_f = nullptr
      };

    ASSERT_EQ(0, 0);
}

//Will uncomment when interface is ready
//TEST(AccessJppObject, String) {
//    jpp::obj temp{
//        "string0"_f = "stringy0",
//        "string1"_f = "stringy1",
//        "string2"_f = "stringy2"
//    };
//
//    auto a0 = temp["string0"].GetValue<jpp::str>();
//    auto a1 = temp["string1"].GetValue<jpp::str>();
//    auto a2 = temp["string2"].GetValue<jpp::str>();
//
//    EXPECT_STREQ(a0, "stringy0");
//    EXPECT_STREQ(a1, "stringy1");
//    EXPECT_STREQ(a2, "stringy2");
//}
//
//TEST(AccessJppObject, Number) {
//    
//    jpp::obj temp{
//        "double0"_f = 3.1415926500,
//        "double1"_f = 3.1415926501,
//        "double2"_f = 3.1415926502
//    };
//
//    auto a0 = temp["double0"].GetValue<double>();
//    auto a1 = temp["double1"].GetValue<double>();
//    auto a2 = temp["double2"].GetValue<double>();
//
//    EXPECT_EQ(a0, 3.1415926500);
//    EXPECT_EQ(a1, 3.1415926501);
//    EXPECT_EQ(a2, 3.1415926502);
//}
