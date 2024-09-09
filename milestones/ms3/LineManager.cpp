// Name: Siddhartha Thapa Chhetri
// Seneca Student ID: 147913222
// Seneca email: sthapa-chhetri2@myseneca.ca
// Date of completion: 2024/08/03
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.
#include "LineManager.h"
#include <fstream>
#include <algorithm>
#include "Utilities.h"
#include <stdexcept>

namespace seneca {

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {
        std::ifstream filename(file);
        if (!filename) {
            throw std::runtime_error("Unable to open file");
        }

        size_t next_pos = 0u;
        bool more = false;
        Utilities util; // Instance of the Utilities class
        std::string line;

        while (std::getline(filename, line)) {
            if (!line.empty()) {
                next_pos = 0;
                std::string station = util.extractToken(line, next_pos, more);
                std::string next_station = "a";
                if (more) {
                    next_station = util.extractToken(line, next_pos, more);
                }

                Workstation* ws = nullptr;
                Workstation* next_ws = nullptr;

                for (auto& s_ptr : stations) {
                    if (s_ptr->getItemName() == station) {
                        ws = s_ptr;
                    }
                    if (s_ptr->getItemName() == next_station) {
                        next_ws = s_ptr;
                    }
                }

                if (ws) {
                    if (next_ws) {
                        ws->setNextStation(next_ws);
                    }
                    m_activeLine.push_back(ws);
                }
            }
        }

        m_firstStation = nullptr;
        for (auto& s_ptr : stations) {
            bool found = false;
            for (auto& checkStation : stations) {
                if (checkStation->getNextStation() == s_ptr) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                m_firstStation = s_ptr;
                break;
            }
        }

        if (!m_firstStation) {
            throw std::runtime_error("Error: No starting station found");
        }

        m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations()
    {
        Workstation* forward_station = m_firstStation;
        std::vector<Workstation*> ws;

        while (forward_station) {
            ws.push_back(forward_station);
            forward_station = forward_station->getNextStation();
        }

        m_activeLine = std::move(ws);
    }

    bool LineManager::run(std::ostream& os)
    {
        static size_t count = 0u;
        os << "Line Manager Iteration: " << ++count << std::endl;

        if (!g_pending.empty()) {
            *m_activeLine.front() += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for (auto* workstation : m_activeLine) {
            workstation->fill(os);
        }

        for (auto* workstation : m_activeLine) {
            workstation->attemptToMoveOrder();
        }

        return m_cntCustomerOrder == g_completed.size() + g_incomplete.size();
    }

    void LineManager::display(std::ostream& os) const
    {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* src) {
            src->display(os);
            });
    }
}
