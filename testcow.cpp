#include "testcow.h"
struct TestCowStringPrivate
{
    std::string str;
};

TestCowString::TestCowString()
    : d(std::make_shared<TestCowStringPrivate>())
{}

TestCowString::~TestCowString()
{}

void TestCowString::setValue(const std::string &val)
{
    d->str = val;
}

const std::string &TestCowString::value() const
{
    return d->str;
}

int TestCowString::useCount() const
{
    return d.useCount();
}


struct TestCowPrivate
{
    int value = 0;
    TestCowString cowString;
};

TestCow::TestCow()
    : d(std::make_shared<TestCowPrivate>())
{}

TestCow::~TestCow()
{}

void TestCow::setValue(int val)
{
    d->value = val;
}

int TestCow::value() const
{
    return d->value;
}

void TestCow::setCowString(const TestCowString &test)
{
    d->cowString = test;
}

const TestCowString &TestCow::cowString() const
{
    return d->cowString;
}

int TestCow::useCount() const
{
    return d.useCount();
}
