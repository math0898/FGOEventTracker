#include "mission.hpp"
#include <string>

/**
 * @brief Construct a new Mission object with the given parameter values.
 *
 * @param apCost         The cost to run this mission.
 * @param eventItemRates A short matrix of drop rates using the declared
 * ordering.
 * @param displayname    The string to display to users when talking about this
 * mission.
 */
fgoet::Mission::Mission(int apCost, double *eventItemRates,
                        std::string displayname) {
  this->apCost = apCost;
  this->eventItemRates = new double[4]{-1}; // TODO: Validate format and assign.
  this->displayname = displayname;
}

/**
 * @brief Destroys this mission object.
 */
fgoet::Mission::~Mission() {
    delete(eventItemRates);
}
