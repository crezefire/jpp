#include "gtest/gtest.h"
#include "jpp/Jpp.h"

using namespace jpp::literals;

//****************************
// Tests for Creating Objects
//****************************

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

TEST(CreateJppObject, Arbitrary) {

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
        "null0"_f = nullptr,
        "null1"_f = nullptr
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

//*****************************
// Tests for Accessing Objects
//*****************************


TEST(AccessJppObject, String) {
   jpp::obj temp{
       "string0"_f = "stringy0",
       "string1"_f = "stringy1",
       "string2"_f = "stringy2"
   };

   auto a0 = jpp::Get<jpp::str>(temp["string0"]);
   auto a1 = jpp::Get<jpp::str>(temp["string1"]);
   auto a2 = jpp::Get<jpp::str>(temp["string2"]);

   EXPECT_STREQ(a0, "stringy0");
   EXPECT_STREQ(a1, "stringy1");
   EXPECT_STREQ(a2, "stringy2");
}


TEST(AccessJppObject, Number) {

   jpp::obj temp{
       "double0"_f = 3.1415926500,
       "double1"_f = 3.1415926501,
       "double2"_f = 3.1415926502
   };

   auto a0 = jpp::Get<double>(temp["double0"]);
   auto a1 = jpp::Get<double>(temp["double1"]);
   auto a2 = jpp::Get<double>(temp["double2"]);

   EXPECT_EQ(a0, 3.1415926500);
   EXPECT_EQ(a1, 3.1415926501);
   EXPECT_EQ(a2, 3.1415926502);
}

TEST(AccessJppObject, Integer) {

   jpp::obj temp{
        "integer0"_f = 1234500,
        "integer1"_f = 1234501,
        "integer2"_f = 1234502
    };

   auto a0 = jpp::Get<int>(temp["integer0"]);
   auto a1 = jpp::Get<int>(temp["integer1"]);
   auto a2 = jpp::Get<int>(temp["integer2"]);

   EXPECT_EQ(a0, 1234500);
   EXPECT_EQ(a1, 1234501);
   EXPECT_EQ(a2, 1234502);
}

TEST(AccessJppObject, Boolean) {

   jpp::obj temp{
        "boolean0"_f = false,
        "boolean1"_f = true
    };

   auto a0 = jpp::Get<bool>(temp["boolean0"]);
   auto a1 = jpp::Get<bool>(temp["boolean1"]);

   EXPECT_EQ(a0, false);
   EXPECT_EQ(a1, true);
}

TEST(AccessJppObject, Arbitrary) {

    struct dummy { int x; };

   jpp::obj temp{
        "struct0"_f = dummy{ 1 },
        "struct1"_f = dummy{ 2 },
        "struct2"_f = dummy{ 3 }
    };

   auto a0 = jpp::Get<dummy>(temp["struct0"]);
   auto a1 = jpp::Get<dummy>(temp["struct1"]);
   auto a2 = jpp::Get<dummy>(temp["struct2"]);

   EXPECT_EQ(a0->x, 1);
   EXPECT_EQ(a1->x, 2);
   EXPECT_EQ(a2->x, 3);
}

TEST(AccessJppObject, Null) {

   jpp::obj temp{
        "null0"_f = nullptr,
        "null1"_f = nullptr
    };

   auto a0 = jpp::Get<jpp::null>(temp["null0"]);
   auto a1 = jpp::Get<jpp::null>(temp["null1"]);

   EXPECT_EQ(a0, nullptr);
   EXPECT_EQ(a1, nullptr);
}

TEST(AccessJppObject, All) {
   struct dummy { int x; };

    jpp::obj temp {
        "string"_f = "stringy",
        "double"_f = 3.1415,
        "integer"_f = 13245,
        "boolean"_f = false,
        "fuckall"_f = dummy{6666},
        "nothing"_f = nullptr
      };

   auto a0 = jpp::Get<jpp::str>(temp["string"]);
   auto a1 = jpp::Get<double>(temp["double"]);
   auto a2 = jpp::Get<int>(temp["integer"]);
   auto a3 = jpp::Get<bool>(temp["boolean"]);
   auto a4 = jpp::Get<dummy>(temp["fuckall"]);
   auto a5 = jpp::Get<jpp::null>(temp["nothing"]);

   EXPECT_STREQ(a0, "stringy");
   EXPECT_EQ(a1, 3.1415);
   EXPECT_EQ(a2, 13245);
   EXPECT_EQ(a3, false);
   EXPECT_EQ(a4->x, 6666);
   EXPECT_EQ(a5, nullptr);
}

TEST(WrongTypeAccessJppObject, String) {
    
    struct dummy {};
    
    jpp::obj temp{
        "string0"_f = "stringy0"
    };

    EXPECT_DEATH(jpp::Get<int>(temp["string0"]), "integral");
    EXPECT_DEATH(jpp::Get<bool>(temp["string0"]), "boolean");
    EXPECT_DEATH(jpp::Get<float>(temp["string0"]), "floating");
    EXPECT_DEATH(jpp::Get<jpp::null>(temp["string0"]), "null");
    EXPECT_DEATH(jpp::Get<dummy>(temp["string0"]), "non-fundamental");
}

TEST(WrongTypeAccessJppObject, Number) {

    struct dummy {};

    jpp::obj temp{
        "double0"_f = 3.1415926500
    };

    EXPECT_DEATH(jpp::Get<int>(temp["double0"]), "integral");
    EXPECT_DEATH(jpp::Get<bool>(temp["double0"]), "boolean");
    EXPECT_DEATH(jpp::Get<jpp::str>(temp["double0"]), "string");
    EXPECT_DEATH(jpp::Get<jpp::null>(temp["double0"]), "null");
    EXPECT_DEATH(jpp::Get<dummy>(temp["double0"]), "non-fundamental");
}

TEST(WrongTypeAccessJppObject, Integer) {

    struct dummy {};

    jpp::obj temp{
        "integer0"_f = 123456
    };

    EXPECT_DEATH(jpp::Get<float>(temp["integer0"]), "floating");
    EXPECT_DEATH(jpp::Get<bool>(temp["integer0"]), "boolean");
    EXPECT_DEATH(jpp::Get<jpp::str>(temp["integer0"]), "string");
    EXPECT_DEATH(jpp::Get<jpp::null>(temp["integer0"]), "null");
    EXPECT_DEATH(jpp::Get<dummy>(temp["integer0"]), "non-fundamental");
}

TEST(WrongTypeAccessJppObject, Boolean) {

    struct dummy {};

    jpp::obj temp{
        "boolean0"_f = true
    };

    EXPECT_DEATH(jpp::Get<float>(temp["boolean0"]), "floating");
    EXPECT_DEATH(jpp::Get<int>(temp["boolean0"]), "integral");
    EXPECT_DEATH(jpp::Get<jpp::str>(temp["boolean0"]), "string");
    EXPECT_DEATH(jpp::Get<jpp::null>(temp["boolean0"]), "null");
    EXPECT_DEATH(jpp::Get<dummy>(temp["boolean0"]), "non-fundamental");
}

TEST(WrongTypeAccessJppObject, Arbitrary) {

    struct dummy {};

    jpp::obj temp{
        "struct0"_f = dummy{}
    };

    EXPECT_DEATH(jpp::Get<float>(temp["struct0"]), "floating");
    EXPECT_DEATH(jpp::Get<int>(temp["struct0"]), "integral");
    EXPECT_DEATH(jpp::Get<jpp::str>(temp["struct0"]), "string");
    EXPECT_DEATH(jpp::Get<jpp::null>(temp["struct0"]), "null");
    EXPECT_DEATH(jpp::Get<bool>(temp["struct0"]), "boolean");
}

TEST(WrongTypeAccessJppObject, Null) {

    struct dummy {};

    jpp::obj temp{
        "null0"_f = nullptr
    };

    EXPECT_DEATH(jpp::Get<float>(temp["null0"]), "floating");
    EXPECT_DEATH(jpp::Get<int>(temp["null0"]), "integral");
    EXPECT_DEATH(jpp::Get<jpp::str>(temp["null0"]), "string");
    EXPECT_DEATH(jpp::Get<dummy>(temp["null0"]), "non-fundamental");
    EXPECT_DEATH(jpp::Get<bool>(temp["null0"]), "boolean");
}


TEST(NullAccessJppObject, All) {

    struct dummy {};

    jpp::obj temp{
    };

    EXPECT_DEATH(jpp::Get<int>(temp["string0"]), "not.*found.*empty");
    EXPECT_DEATH(jpp::Get<bool>(temp["string0"]), "not.*found.*empty");
    EXPECT_DEATH(jpp::Get<float>(temp["string0"]), "not.*found.*empty");
    EXPECT_DEATH(jpp::Get<jpp::str>(temp["string0"]), "not.*found.*empty");
    EXPECT_DEATH(jpp::Get<jpp::null>(temp["string0"]), "not.*found.*empty");
    EXPECT_DEATH(jpp::Get<dummy>(temp["string0"]), "not.*found.*empty");
}


TEST(ExampleTest, TestJSON) {

    jpp::obj temp {
        "string"_f = "this is a string",
        "double"_f = 3.14159265,
        "integer"_f  = 12345,
        "boolean"_f = true,
        "null"_f = nullptr
    };
}
