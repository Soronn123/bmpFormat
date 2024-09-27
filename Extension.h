#pragma once

#include <stdexcept>


class Error : public std::runtime_error
{
public:
    Error(const char* message) : std::runtime_error(message)
    {  }
};