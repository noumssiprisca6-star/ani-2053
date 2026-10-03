#include <iostream>
#include <string>
#include <vector>

struct KeyState {
    bool space = false;
    bool right = false;
};

int main() {
    int total_images = 0;
    int nb_events = 0;

    if (!(std::cin >> total_images >> nb_events)) {
        std::cout << "SAUTS EVENEMENTS 0\n";
        std::cout << "SAUTS INTERROGATION 0\n";
        std::cout << "MANQUES 0\n";
        return 0;
    }

    std::vector<int> event_space_presses(total_images + 1, 0);
    std::vector<KeyState> final_states(total_images + 1);

    for (int i = 0; i < nb_events; ++i) {
        int img = 0;
        std::string action;
        std::cin >> img >> action;

        if (img >= 1 && img <= total_images) {
            if (action == "+SPACE") {
                event_space_presses[img]++;
                final_states[img].space = true;
            } else if (action == "-SPACE") {
                final_states[img].space = false;
            } else if (action == "+RIGHT") {
                final_states[img].right = true;
            } else if (action == "-RIGHT") {
                final_states[img].right = false;
            }
        }
    }

    int pos_event = 0;
    int pos_poll = 0;
    int sauts_events = 0;
    int sauts_poll = 0;
    int manques = 0;

    bool current_space = false;

    for (int i = 1; i <= total_images; ++i) {
        if (event_space_presses[i] > 0) {
            pos_event += 5 * event_space_presses[i];
            sauts_events += event_space_presses[i];
        }

        current_space = final_states[i].space;

        if (current_space) {
            pos_poll += 5;
            sauts_poll++;
        }

        std::cout << i << " " << pos_event << " " << pos_poll << "\n";
    }

    std::cout << "SAUTS EVENEMENTS " << sauts_events << "\n";
    std::cout << "SAUTS INTERROGATION " << sauts_poll << "\n";
    std::cout << "MANQUES " << manques << "\n";

    return 0;
}

