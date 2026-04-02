//
// Created by paultal on 02.04.2026.
//

#ifndef LAB07_REPOSITORYEXCEPTION_H
#define LAB07_REPOSITORYEXCEPTION_H

#include <string>

class RepositoryException
{
public:
    std::string message;
    explicit RepositoryException(std::string msg) : message(std::move(msg)) {}
};

#endif //LAB07_REPOSITORYEXCEPTION_H
