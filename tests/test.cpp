#include <gtest/gtest.h>
#include "../include/twelve.h"

TEST(TwelveTest, DefaultConstructor) {
    Twelve num;
}

TEST(TwelveTest, StringConstructor) {
    Twelve num("A7B");
}

TEST(TwelveTest, StringConstructorInvalid) {
    EXPECT_THROW({
        Twelve num("G12"); 
    }, std::exception);
}

TEST(TwelveTest, SizeAndCharConstructor) {
    Twelve num(3, 'A');
}

TEST(TwelveTest, InitializerListConstructor) {
    Twelve num{'1', 'A', 'B'};
}

TEST(TwelveTest, CopyConstructor) {
    Twelve original("A7B");
    Twelve copy(original);
    
    EXPECT_TRUE(original.eq(copy)); 
}

TEST(TwelveTest, MoveConstructor) {
    Twelve original("A7B");
    Twelve moved(std::move(original));
    
}


TEST(TwelveTest, Equality) {
    Twelve num1("A7B");
    Twelve num2("A7B");
    Twelve num3("123");
    
    EXPECT_TRUE(num1.eq(num2));
    EXPECT_FALSE(num1.eq(num3));
}

TEST(TwelveTest, GreaterThan) {
    Twelve num1("B00"); 
    Twelve num2("100"); 
    
    EXPECT_TRUE(num1.gt(num2));
    EXPECT_FALSE(num2.gt(num1));
}

TEST(TwelveTest, LessThan) {
    Twelve num1("100");
    Twelve num2("B00");
    
    EXPECT_TRUE(num1.lt(num2));
    EXPECT_FALSE(num2.lt(num1));
}

TEST(TwelveTest, Addition) {
    Twelve num1("123");
    Twelve num2("456");
    Twelve expected("579");
    
    Twelve result = num1.add(num2);
    EXPECT_TRUE(result.eq(expected));
}

TEST(TwelveTest, AdditionWithCarry) {
    Twelve num1("BBB"); 
    Twelve num2("1");  
    Twelve expected("1000"); 
    
    Twelve result = num1.add(num2);
    EXPECT_TRUE(result.eq(expected));
}

TEST(TwelveTest, Subtraction) {
    Twelve num1("A7B");
    Twelve num2("45A");
    Twelve expected("621");
    
    Twelve result = num1.sub(num2);
    EXPECT_TRUE(result.eq(expected));
}

TEST(TwelveTest, SubtractionInvalid) {
    Twelve num1("123");
    Twelve num2("456"); 
    
    EXPECT_THROW({
        num1.sub(num2); 
    }, std::exception);
}

TEST(TwelveTest, SubtractionZero) {
    Twelve num1("A7B");
    Twelve num2;
    
    Twelve result = num1.sub(num2);
    EXPECT_TRUE(result.eq(num1)); 
}

TEST(TwelveTest, CopyFrom) {
    Twelve source("A7B");
    Twelve target;
    
    target.copy_from(source);
    EXPECT_TRUE(source.eq(target));
    
}

TEST(TwelveTest, MoveFrom) {
    Twelve source("A7B");
    Twelve target;
    
    target.move_from(std::move(source));
    
    Twelve expected("A7B");
    EXPECT_TRUE(target.eq(expected));
}


TEST(TwelveTest, LargeNumbers) {
    Twelve num1("BA987654321");
    Twelve num2("1");
    Twelve expected("BA987654322");
    
    Twelve result = num1.add(num2);
    EXPECT_TRUE(result.eq(expected));
}

TEST(TwelveTest, CopyIdentity) {
    Twelve original("A7B");
    Twelve copy1(original); 
    Twelve copy2;
    copy2.copy_from(original); 
    
    EXPECT_TRUE(original.eq(copy1));
    EXPECT_TRUE(original.eq(copy2));
    EXPECT_TRUE(copy1.eq(copy2));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}