#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct ImageNode {
    std::string nom;
    bool selected;
};

void printList(const std::vector<std::string>& list) {
    if (list.empty()) {
        std::cout << "AUCUN\n";
    } else {
        for (size_t i = 0; i < list.size(); ++i) {
            std::cout << (i == 0 ? "" : " ") << list[i];
        }
        std::cout << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<ImageNode> items;
    std::vector<std::string> boardIndex;
    std::vector<int> selectedIndices;
    std::vector<std::string> boardId;
    std::vector<std::string> selectedIds;

    std::string op;
    while (std::cin >> op) {
        if (op == "AJOUTE") {
            std::string nom;
            std::cin >> nom;
            items.push_back({nom, false});
            boardIndex.push_back(nom);
            boardId.push_back(nom);
        }
        else if (op == "CLIC") {
            int i;
            std::cin >> i;
            for (auto& node : items) node.selected = false;
            if (i >= 0 && i < (int)items.size()) {
                items[i].selected = true;
            }
            selectedIndices.clear();
            if (i >= 0 && i < (int)boardIndex.size()) {
                selectedIndices.push_back(i);
            }
            selectedIds.clear();
            if (i >= 0 && i < (int)boardId.size()) {
                selectedIds.push_back(boardId[i]);
            }
        }
        else if (op == "AJOUTE_SEL") {
            int i;
            std::cin >> i;
            if (i >= 0 && i < (int)items.size()) {
                items[i].selected = true;
            }
            if (i >= 0 && i < (int)boardIndex.size()) {
                if (std::find(selectedIndices.begin(), selectedIndices.end(), i) == selectedIndices.end()) {
                    selectedIndices.push_back(i);
                }
            }
            if (i >= 0 && i < (int)boardId.size()) {
                const std::string& name = boardId[i];
                if (std::find(selectedIds.begin(), selectedIds.end(), name) == selectedIds.end()) {
                    selectedIds.push_back(name);
                }
            }
        }
        else if (op == "ECHANGE") {
            int i, j;
            std::cin >> i >> j;
            if (i >= 0 && i < (int)items.size() && j >= 0 && j < (int)items.size()) {
                std::swap(items[i], items[j]);
            }
            if (i >= 0 && i < (int)boardIndex.size() && j >= 0 && j < (int)boardIndex.size()) {
                std::swap(boardIndex[i], boardIndex[j]);
            }
            if (i >= 0 && i < (int)boardId.size() && j >= 0 && j < (int)boardId.size()) {
                std::swap(boardId[i], boardId[j]);
            }
        }
        else if (op == "RETIRE") {
            int i;
            std::cin >> i;
            if (i >= 0 && i < (int)items.size()) {
                items.erase(items.begin() + i);
            }
            if (i >= 0 && i < (int)boardIndex.size()) {
                boardIndex.erase(boardIndex.begin() + i);
            }
            if (i >= 0 && i < (int)boardId.size()) {
                boardId.erase(boardId.begin() + i);
            }
        }
        else if (op == "SUPPRIME") {
            std::vector<ImageNode> nextItems;
            for (const auto& node : items) {
                if (!node.selected) nextItems.push_back(node);
            }
            items = nextItems;

            std::vector<std::string> nextBoardIndex;
            for (size_t idx = 0; idx < boardIndex.size(); ++idx) {
                bool isSel = std::find(selectedIndices.begin(), selectedIndices.end(), (int)idx) != selectedIndices.end();
                if (!isSel) {
                    nextBoardIndex.push_back(boardIndex[idx]);
                }
            }
            boardIndex = nextBoardIndex;
            selectedIndices.clear();

            std::vector<std::string> nextBoardId;
            for (const auto& name : boardId) {
                bool isSel = std::find(selectedIds.begin(), selectedIds.end(), name) != selectedIds.end();
                if (!isSel) {
                    nextBoardId.push_back(name);
                }
            }
            boardId = nextBoardId;
            selectedIds.clear();
        }
    }

    std::vector<std::string> pItem, sItem;
    for (const auto& node : items) {
        pItem.push_back(node.nom);
        if (node.selected) sItem.push_back(node.nom);
    }

    std::vector<std::string> pIndex = boardIndex;
    std::vector<std::string> sIndex;
    for (int idx : selectedIndices) {
        if (idx >= 0 && idx < (int)boardIndex.size()) {
            sIndex.push_back(boardIndex[idx]);
        }
    }

    std::vector<std::string> pId = boardId;
    std::vector<std::string> sId;
    for (const auto& name : selectedIds) {
        if (std::find(boardId.begin(), boardId.end(), name) != boardId.end()) {
            sId.push_back(name);
        }
    }

    std::cout << "DANS_ITEM PLANCHE "; printList(pItem);
    std::cout << "DANS_ITEM SELECTION "; printList(sItem);

    std::cout << "PAR_INDEX PLANCHE "; printList(pIndex);
    std::cout << "PAR_INDEX SELECTION "; printList(sIndex);

    std::cout << "PAR_ID PLANCHE "; printList(pId);
    std::cout << "PAR_ID SELECTION "; printList(sId);

    std::vector<std::string> fauxList;
    if (pIndex != pItem || sIndex != sItem) fauxList.push_back("PAR_INDEX");
    if (pId != pItem || sId != sItem) fauxList.push_back("PAR_ID");

    std::cout << "FAUX ";
    printList(fauxList);

    return 0;
}