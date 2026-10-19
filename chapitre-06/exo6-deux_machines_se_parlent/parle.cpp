#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "NKNetwork/NKNetwork.h"

using namespace nkentseu;

int main(int argc, char* argv[]) {
    NkSocket::PlatformInit();

    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " [serveur|client] [ip]" << std::endl;
        return 1;
    }

    std::string role = argv[1];
    NkConnectionManager connectionManager;

    NkPeerId connectedPeer;
    bool hasPeer = false;

    connectionManager.onPeerConnected = [&](const NkPeerId& peerId) {
        connectedPeer = peerId;
        hasPeer = true;
        std::cout << "[Connexion] Pair connecte - ID value: " << peerId.value << std::endl;
    };

    if (role == "serveur") {
        connectionManager.StartServer(7777, 8);
        std::cout << "Serveur demarre sur le port 7777..." << std::endl;

        while (true) {
            NkVector<NkReceiveMsg> messages;
            connectionManager.DrainAll(messages);
            for (const auto& msg : messages) {
                std::string message(reinterpret_cast<const char*>(msg.data), msg.size);
                std::cout << "[Message recu] De l'expediteur ID value: " << msg.from.value 
                          << " -> Contenu: \"" << message << "\"" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

    } else if (role == "client") {
        std::string ip = (argc >= 3) ? argv[2] : "192.168.71.244";
        std::cout << "Tentative de connexion au serveur a l'adresse " << ip << ":7777..." << std::endl;

        connectionManager.Connect(net::NkAddress(ip.c_str(), 7777));

        while (!hasPeer) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        std::string texte = "Bonjour depuis le client NKNetwork !";
        connectionManager.SendTo(connectedPeer, reinterpret_cast<const uint8*>(texte.c_str()), texte.size() + 1);
        std::cout << "Message envoye au serveur : \"" << texte << "\"" << std::endl;

        while (true) {
            NkVector<NkReceiveMsg> messages;
            connectionManager.DrainAll(messages);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    } else {
        std::cerr << "Role inconnu. Utilisez 'serveur' ou 'client'." << std::endl;
        return 1;
    }

    return 0;
}