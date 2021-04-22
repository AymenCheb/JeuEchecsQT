#pragma once
using namespace std;
#include <exception>
#include <stdexcept>
class ErreurSurplusRoi : public std::runtime_error {
public:
    using runtime_error::runtime_error;
    ErreurSurplusRoi();
};