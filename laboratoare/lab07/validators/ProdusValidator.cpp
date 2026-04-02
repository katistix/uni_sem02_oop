//
// Created by paultal on 02.04.2026.
//

#include "ProdusValidator.h"
#include <string>

ValidationException::ValidationException(vector<string> errorMsgs)
{
    errorMessage = "";
    for (string &error: errorMsgs)
        errorMessage += error + "\n";
}

const string& ValidationException::getMessage() const
{
    return errorMessage;
}

void ProdusValidator::validate(const Produs &p)
{
    std::vector<string> errorMessages;
    if (p.getId() <= 0)
        errorMessages.push_back("ID-ul trebuie sa fie un numar pozitiv.");
    if (strlen(p.getNume()) == 0)
        errorMessages.push_back("Numele trebuie sa contina cel putin un caracter.");
    if (strlen(p.getTip())==0)
        errorMessages.push_back("Tipul trebuie sa contina cel putin un caracter.");
    if (p.getPret() < 0)
        errorMessages.push_back("Pretul trebuie sa fie pozitiv.");
    if (strlen(p.getProducator()) == 0)
        errorMessages.push_back("Denumirea producatorului trebuie sa contina cel putin un caracter.");

    if (!errorMessages.empty())
        throw ValidationException(errorMessages);
}
