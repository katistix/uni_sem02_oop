//
// Created by paultal on 02.04.2026.
//

#ifndef LAB07_PRODUSVALIDATOR_H
#define LAB07_PRODUSVALIDATOR_H
#include <string>
#include <vector>
#include "../domain/Produs.h"

using namespace std;

class ValidationException
{
private:
    std::string errorMessage;
public:
    ValidationException(string errorMsg):errorMessage(errorMsg){};
    ValidationException(vector<string> errorMsgs);
    const string& getMessage() const;
};

class ProdusValidator
{
public:
    void validate(const Produs &p);
};


#endif //LAB07_PRODUSVALIDATOR_H