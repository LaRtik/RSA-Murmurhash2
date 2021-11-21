#pragma once

#include "utils.h"

#include <exception>
#include <string>
#include <vector>

struct Keys
{
    std::pair<bigint, bigint> _public;
    std::pair<bigint, bigint> _private;
};

Keys calculateRSAKeys();

bigint cryptData(bigint data, std::pair<bigint, bigint> _publicKey);

bigint encryptData(bigint data, std::pair<bigint, bigint> _privateKey);

std::vector<bigint> cryptMessage(std::string data, std::pair<bigint, bigint> _publicKey);

std::string encryptMessage(std::vector<bigint> data, std::pair<bigint, bigint> _privateKey);
