#ifndef SUGAKU_MISSION
#define SUGAKU_MISSION

#include <string>

/**
 * @brief The namespace for classes and functions defined for the Fate/Grander Order Event Tracker program.
 */
namespace fgoet {

    /**
     * @brief A runable mission that is part of an event.
     */
    class Mission {
        private:

            /**
             * @brief The action point cost to run this mission.
             */
            int apCost;

            /**
             * @brief A short matrix of drop rates. Formatted as the expected number of each event item per run.
             * 0 - Bronze
             * 1 - Silver
             * 2 - Gold
             * 3 - Points
             */
            double* eventItemRates;

            /**
             * @brief The name to display to the user when talking about this mission.
             */
            std::string displayname;

        public:

            /**
             * @brief Construct a new Mission object with the given parameter values.
             * 
             * @param apCost         The cost to run this mission.
             * @param eventItemRates A short matrix of drop rates using the declared ordering.
             * @param displayname    The string to display to users when talking about this mission.
             */
            Mission(int apCost, double* eventItemRates, std::string displayname);

            /**
             * @brief Destroys this mission object.
             */
            ~Mission();

            /**
             * @brief Accessor method for the mission's ap cost.
             * 
             * @return The ap cost of this mission.
             */
            int inline getApCost () {
                return apCost;
            }

            /**
             * @brief Accessor method for the drop rate of items in this mission.
             * 
             * @return An array of drop rates.
             */
            double inline* getEventItemRates () {
                return eventItemRates;
            }

            /**
             * @brief Accessor method for the display string of this mission.
             * 
             * @return The display string for this mission.
             */
            std::string inline getDisplayname () {
                return displayname;
            }
    };
};

#endif
