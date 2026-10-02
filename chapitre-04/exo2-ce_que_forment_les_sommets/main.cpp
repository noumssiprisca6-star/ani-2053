#include<string>
#include<vector>
#include <iostream>

struct PrimitiveQuery {
    std::string type;
    long long sommets = 0;
};

struct PrimitiveResult {
    std::string type;
    long long sommets = 0;
    long long formes = 0;
    std::string unite;
    long long restant = 0;
    bool estValide = false;
};

PrimitiveResult traiterPrimitive(const PrimitiveQuery& query) {
    PrimitiveResult res;
    res.type = query.type;
    res.sommets = query.sommets;

    long long s = query.sommets;

    if (query.type == "POINTS") {
        res.formes = s;
        res.unite = "POINTS";
        res.restant = 0;
        res.estValide = true;
    } 
    else if (query.type == "LINES") {
        res.formes = s / 2;
        res.unite = "SEGMENTS";
        res.restant = s % 2;
        res.estValide = true;
    } 
    else if (query.type == "LINE_STRIP") { 
        res.formes = (s >= 2) ? (s - 1) : 0;
        res.unite = "SEGMENTS";
        res.restant = (s >= 2) ? 0 : s;
        res.estValide = true;
    } 
    else if (query.type == "TRIANGLES") {
        res.formes = s / 3;
        res.unite = "TRIANGLES";
        res.restant = s % 3;
        res.estValide = true;
    } 
    else if (query.type == "TRIANGLE_STRIP" || query.type == "TRIANGLE_FAN") {
        res.formes = (s >= 3) ? (s - 2) : 0;
        res.unite = "TRIANGLES";
        res.restant = (s >= 3) ? 0 : s;
        res.estValide = true;
    } 
    else {
        
        res.estValide = false;
    }

    return res;
}
int main() {

std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n = 0;
    if (!(std::cin >> n) || n <= 0) {
        std::cout << "POINTS 0\n";
        std::cout << "SEGMENTS 0\n";
        std::cout << "TRIANGLES 0\n";
        std::cout << "REFUSES 0\n";
        return 0;
    }

    
    std::vector<PrimitiveQuery> requetes(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> requetes[i].type >> requetes[i].sommets;
    }

    long long total_points = 0;
    long long total_segments = 0;
    long long total_triangles = 0;
    long long total_refuses = 0;

    // 2. Traitement et affichage ligne par ligne
    for (const auto& req : requetes) {
        PrimitiveResult res = traiterPrimitive(req);

        if (res.estValide) {
            std::cout << res.type << " " 
                      << res.sommets << " " 
                      << res.formes << " " 
                      << res.unite << " " 
                      << res.restant << "\n";

            if (res.unite == "POINTS") {
                total_points += res.formes;
            } else if (res.unite == "SEGMENTS") {
                total_segments += res.formes;
            } else if (res.unite == "TRIANGLES") {
                total_triangles += res.formes;
            }
        } else {
            std::cout << res.type << " " << res.sommets << " REFUSE\n";
            total_refuses++;
        }
    }

    std::cout << "POINTS " << total_points << "\n";
    std::cout << "SEGMENTS " << total_segments << "\n";
    std::cout << "TRIANGLES " << total_triangles << "\n";
    std::cout << "REFUSES " << total_refuses << "\n";
    return 0;
}
