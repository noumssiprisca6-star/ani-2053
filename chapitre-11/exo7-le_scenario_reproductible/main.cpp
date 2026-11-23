#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

struct Action {
    int type;
    long long n;
    std::string a;
    std::string b;
    std::string c;
    bool done = false;
};

struct Capture {
    long long n;
    bool done = false;
};

static bool parse_ll(const std::string& s, long long& out) {
    if (s.empty()) {
        return false;
    }
    size_t idx = 0;
    if (s[0] == '-' || s[0] == '+') {
        if (s.size() == 1) {
            return false;
        }
        idx = 1;
    }
    for (size_t i = idx; i < s.size(); ++i) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }
    try {
        out = std::stoll(s);
    } catch (...) {
        return false;
    }
    return true;
}

static std::vector<std::string> split_char(const std::string& s, char sep) {
    std::vector<std::string> parts;
    size_t start = 0;
    while (true) {
        size_t pos = s.find(sep, start);
        if (pos == std::string::npos) {
            parts.push_back(s.substr(start));
            break;
        }
        parts.push_back(s.substr(start, pos - start));
        start = pos + 1;
    }
    return parts;
}

int main() {
    std::vector<Action> actions;
    std::vector<Capture> captures;
    bool has_exit = false;
    long long exit_frame = 0;
    long long ignores = 0;

    std::string line;
    while (std::getline(std::cin, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            continue;
        }
        size_t eq = line.find('=');
        if (eq == std::string::npos) {
            ++ignores;
            continue;
        }
        std::string name = line.substr(0, eq);
        std::string val = line.substr(eq + 1);

        if (name == "NK_AGENT_SHOT") {
            if (val.empty()) {
                continue;
            }
            std::vector<std::string> items = split_char(val, ',');
            int kept = 0;
            for (const std::string& item : items) {
                long long n = 0;
                if (!parse_ll(item, n)) {
                    ++ignores;
                    continue;
                }
                if (kept >= 8) {
                    ++ignores;
                    continue;
                }
                ++kept;
                captures.push_back(Capture{n, false});
            }
        } else if (name == "NK_AGENT_EXIT") {
            long long n = 0;
            if (!parse_ll(val, n)) {
                ++ignores;
                continue;
            }
            has_exit = true;
            exit_frame = n;
        } else if (name == "NK_AGENT_PAN") {
            std::vector<std::string> f = split_char(val, ':');
            long long n = 0;
            if (f.size() < 3 || !parse_ll(f[0], n)) {
                ++ignores;
                continue;
            }
            actions.push_back(Action{0, n, f[1], f[2], "", false});
        } else if (name == "NK_AGENT_ZOOM") {
            std::vector<std::string> f = split_char(val, ':');
            long long n = 0;
            if (f.size() < 4 || !parse_ll(f[0], n)) {
                ++ignores;
                continue;
            }
            actions.push_back(Action{1, n, f[1], f[2], f[3], false});
        } else if (name == "NK_AGENT_DROP") {
            if (val.empty()) {
                continue;
            }
            std::vector<std::string> items = split_char(val, ';');
            int kept = 0;
            for (const std::string& item : items) {
                size_t c1 = item.find(':');
                size_t c2 = (c1 == std::string::npos) ? std::string::npos : item.find(':', c1 + 1);
                size_t c3 = (c2 == std::string::npos) ? std::string::npos : item.find(':', c2 + 1);
                if (c3 == std::string::npos) {
                    ++ignores;
                    continue;
                }
                std::string s_n = item.substr(0, c1);
                std::string px = item.substr(c1 + 1, c2 - (c1 + 1));
                std::string py = item.substr(c2 + 1, c3 - (c2 + 1));
                std::string path = item.substr(c3 + 1);
                long long n = 0;
                if (!parse_ll(s_n, n)) {
                    ++ignores;
                    continue;
                }
                if (kept >= 8) {
                    ++ignores;
                    continue;
                }
                ++kept;
                actions.push_back(Action{2, n, path, px, py, false});
            }
        } else if (name == "NK_AGENT_CLICK") {
            if (val.empty()) {
                continue;
            }
            std::vector<std::string> items = split_char(val, ';');
            int kept = 0;
            for (const std::string& item : items) {
                std::vector<std::string> f = split_char(item, ':');
                long long n = 0;
                if (f.size() < 3 || !parse_ll(f[0], n)) {
                    ++ignores;
                    continue;
                }
                if (kept >= 8) {
                    ++ignores;
                    continue;
                }
                ++kept;
                actions.push_back(Action{3, n, f[1], f[2], "", false});
            }
        } else if (name == "NK_AGENT_MOVE") {
            std::vector<std::string> f = split_char(val, ':');
            long long n = 0;
            if (f.size() < 3 || !parse_ll(f[0], n)) {
                ++ignores;
                continue;
            }
            actions.push_back(Action{4, n, f[1], f[2], "", false});
        } else if (name == "NK_AGENT_PACK") {
            long long n = 0;
            if (!parse_ll(val, n)) {
                ++ignores;
                continue;
            }
            actions.push_back(Action{5, n, "", "", "", false});
        } else if (name == "NK_AGENT_GRID") {
            std::vector<std::string> f = split_char(val, ':');
            long long n = 0;
            if (f.size() < 2 || !parse_ll(f[0], n)) {
                ++ignores;
                continue;
            }
            actions.push_back(Action{6, n, f[1], "", "", false});
        }
    }

    long long max_pos = 0;
    for (const Action& act : actions) {
        if (act.n > max_pos) {
            max_pos = act.n;
        }
    }
    for (const Capture& cap : captures) {
        if (cap.n > max_pos) {
            max_pos = cap.n;
        }
    }

    bool stopped_by_exit = false;
    long long last_tour = 0;
    long long counter = 0;

    long long t = 0;
    while (true) {
        if (has_exit && exit_frame > 0 && counter >= exit_frame) {
            stopped_by_exit = true;
            break;
        }
        if (!(has_exit && exit_frame > 0) && t > max_pos && counter > max_pos) {
            break;
        }

        last_tour = t;

        for (int typ = 0; typ <= 6; ++typ) {
            for (Action& act : actions) {
                if (!act.done && act.n == t && act.n > 0 && act.type == typ) {
                    act.done = true;
                    if (typ == 0) {
                        std::cout << "TOUR " << t << " PAN " << act.a << ' ' << act.b << '\n';
                    } else if (typ == 1) {
                        std::cout << "TOUR " << t << " ZOOM " << act.a << ' ' << act.b << ' ' << act.c << '\n';
                    } else if (typ == 2) {
                        std::cout << "TOUR " << t << " DEPOT " << act.a << ' ' << act.b << ' ' << act.c << '\n';
                    } else if (typ == 3) {
                        std::cout << "TOUR " << t << " CLIC " << act.a << ' ' << act.b << '\n';
                    } else if (typ == 4) {
                        std::cout << "TOUR " << t << " MOVE " << act.a << ' ' << act.b << '\n';
                    } else if (typ == 5) {
                        std::cout << "TOUR " << t << " RANGE\n";
                    } else if (typ == 6) {
                        std::cout << "TOUR " << t << " GRILLE " << act.a << '\n';
                    }
                }
            }
        }

        counter = t + 1;
        for (Capture& cap : captures) {
            if (!cap.done && cap.n == counter) {
                cap.done = true;
                std::cout << "TOUR " << t << " CAPTURE\n";
            }
        }

        if (has_exit && exit_frame > 0 && counter >= exit_frame) {
            stopped_by_exit = true;
            break;
        }

        ++t;
    }

    if (stopped_by_exit) {
        std::cout << "ARRET " << last_tour << '\n';
    } else {
        std::cout << "SANS_ARRET\n";
    }

    long long jamais = 0;
    for (const Action& act : actions) {
        if (!act.done) {
            ++jamais;
        }
    }
    for (const Capture& cap : captures) {
        if (!cap.done) {
            ++jamais;
        }
    }

    std::cout << "JAMAIS " << jamais << '\n';
    std::cout << "IGNORES " << ignores << '\n';

    return 0;
}