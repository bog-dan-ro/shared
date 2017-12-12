#pragma once
#include <shared>
#include <string>

class TestCowString
{
public:
    TestCowString();
    virtual ~TestCowString();
    void setValue(const std::string &val);
    const std::string &value() const;
    int useCount() const;
private:
    shared<struct TestCowStringPrivate> d;
};


class TestCow
{
public:
    TestCow();
    virtual ~TestCow();
    void setValue(int val);
    int value() const;
    void setCowString(const TestCowString &test);
    const TestCowString &cowString() const;
    int useCount() const;
private:
    shared<struct TestCowPrivate> d;
};
