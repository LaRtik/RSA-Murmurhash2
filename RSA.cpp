#include "RSA.h"


Keys calculateRSAKeys()
{
  //  bigint p("14474011154664524427946373126085988481573677491474835889066354349131199152128"), q("13164036458569648337239753460458722910223472318386943117783728128");
    bigint p("17"), q("19");
    /*int len = rand() % 34 + 1;
    string p_str, q_str;
    for (int i = 0; i < len; i++)
    {
        p_str += rand() % 10;
        q_str += rand() % 10;
    }
    p = bigint(p_str);
    q = bigint(q_str);
    while (!utils::prime(p)) { p = p + 1; }
    while (!utils::prime(q)) { q = q + 1; }*/

    bigint n = p * q;

    bigint functionE = (p - 1) * (q - 1);

    bigint e = 2;
    for (bigint i = bigint(2); i < functionE; i = i + 1)
    {
        cout << i << endl;
        if (i == 43) cout << "WOW" << endl;
        cout << utils::gcd(i, functionE) << endl;
        if (utils::gcd(i, functionE) == 1)
        {
            e = i;
            break;
        }
    }
    
    bigint d = 0;
    for (bigint i = 0;; i = i + 1)
    {
      //  cout << i << " " << (i * e) % functionE << endl;
        if ((i * e) % functionE == 1)
        {
            
            d = i;
            break;
        }
    }
    cout << n << " " << functionE << " " << e  << " " << d <<  endl;

    Keys keys{ std::pair<bigint, bigint> {e, n}, std::pair<bigint, bigint> {d, n} };
    return keys;
}

bigint cryptData(bigint data, std::pair<bigint, bigint> _publicKey)
{
    if (data > _publicKey.second)
    {
        throw std::exception("Invalid data");
    }

    bigint cryptedData = bigint(1);
    for (bigint i = 0; i < _publicKey.first; i = i + 1)
    {
        cryptedData *= data;
        cryptedData = cryptedData % _publicKey.second;
    }

    return cryptedData;
}

bigint encryptData(bigint data, std::pair<bigint, bigint> _privateKey)
{
    bigint encryptedData = 1;
    for (bigint i = 0; i < _privateKey.first; i = i + 1)
    {
        encryptedData *= data;
        encryptedData = encryptedData % _privateKey.second;
    }

    return encryptedData;
}

std::vector<bigint> cryptMessage(std::string data, std::pair<bigint, bigint> _publicKey)
{
    std::vector<bigint> cryptedMessage;
    cryptedMessage.reserve(data.size());

    for (char element : data)
    {
        cryptedMessage.push_back(cryptData(element, _publicKey));
    }

    return cryptedMessage;
}

std::string encryptMessage(std::vector<bigint> data, std::pair<bigint, bigint> _privateKey)
{
    std::string encryptedMessage;

    for (bigint element : data)
    {
        encryptedMessage.push_back(((encryptData(element, _privateKey)).to_string())[0]);
    }

    return encryptedMessage;
}



