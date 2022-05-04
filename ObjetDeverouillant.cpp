#include "ObjetDeverouillant.h"

ObjetDeverouillant::ObjetDeverouillant(const std::string& nom,
                                       const std::string& description,
                                       const std::string& utilisation,
                                       const std::string& message,
                                       const bool& estCache) :
                                       Objet(nom, description, utilisation, estCache)
{
    message_ = message;
}

void ObjetDeverouillant::use(std::ostream& os)
{
    os << message_ << std::endl;
    message_ = description_;
}
