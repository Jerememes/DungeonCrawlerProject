#pragma once
#include "Objet.h"
class ObjetDeverouillant : public Objet
{
public:
    ObjetDeverouillant() = default;
    ObjetDeverouillant(const std::string& nom,
                       const std::string& description,
                       const std::string& utilisation,
                       const std::string& message,
                       const bool& estCache = false);
    void virtual use(std::ostream& os) override;

private:
    std::string message_;
};

