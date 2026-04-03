//
// Created by paultal on 02.04.2026.
//

#ifndef LAB07_PRODUSVALIDATOR_H
#define LAB07_PRODUSVALIDATOR_H
#include <string>
#include <utility>
#include <vector>
#include "../domain/Produs.h"

using namespace std;

class ValidationException
{
private:
    std::string errorMessage;
public:
    ValidationException(string errorMsg):errorMessage(std::move(errorMsg)){};
    ValidationException(vector<string> errorMsgs);
    [[nodiscard]] const string& getMessage() const;
};

class ProdusValidator
{
public:
    static void validate(const Produs &p);
};


#endif //LAB07_PRODUSVALIDATOR_H