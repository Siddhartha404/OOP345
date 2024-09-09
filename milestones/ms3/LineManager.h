// Name: Siddhartha Thapa Chhetri
// Seneca Student ID: 147913222
// Seneca email: sthapa-chhetri2@myseneca.ca
// Date of completion: 2024/08/03
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include <vector>
#include <string>
#include <ostream>
#include "Workstation.h"

namespace seneca {

    class LineManager {
        // The collection of workstations for the current assembly line.
        std::vector<Workstation*> m_activeLine;

        // The total number of CustomerOrder objects.
        size_t m_cntCustomerOrder{ 0u };

        // Points to the first active station on the current line.
        Workstation* m_firstStation{ nullptr };

    public:
        // Constructor to initialize the LineManager with a file and a vector of Workstation pointers.
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);

        // Function to reorder the stations.
        void reorderStations();

        // Function to run the LineManager.
        bool run(std::ostream& os);

        // Function to display the status of the LineManager.
        void display(std::ostream& os) const;
    };

} // namespace seneca

#endif // SENECA_LINEMANAGER_H
