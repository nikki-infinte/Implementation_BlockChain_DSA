#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <functional>

class Block {
private:
    int index;
    std::string timestamp;
    std::string data;
    std::string previousHash;
    std::string hash;
    int nonce;

    // Simple hash function using std::hash
    std::string calculateHash() const {
        std::stringstream ss;
        ss << index << timestamp << data << previousHash << nonce;
        
        std::hash<std::string> hasher;
        size_t hashValue = hasher(ss.str());
        
        std::stringstream hashStream;
        hashStream << std::hex << std::setw(16) << std::setfill('0') << hashValue;
        return hashStream.str();
    }

public:
    Block(int idx, const std::string& data, const std::string& prevHash) 
        : index(idx), data(data), previousHash(prevHash), nonce(0) {
        time_t now = time(0);
        timestamp = std::ctime(&now);
        hash = mineBlock(4);
    }

    // Proof of Work implementation
    std::string mineBlock(int difficulty) {
        std::string target(difficulty, '0');
        
        do {
            nonce++;
            hash = calculateHash();
        } while (hash.substr(0, difficulty) != target);
        
        std::cout << "Block mined! Hash: " << hash << std::endl;
        return hash;
    }

    // Getters
    std::string getHash() const { return hash; }
    std::string getPreviousHash() const { return previousHash; }
    std::string getData() const { return data; }
    int getIndex() const { return index; }

    friend class Blockchain;
};

class Blockchain {
private:
    std::vector<Block> chain;
    
    Block getLastBlock() const {
        return chain.back();
    }

public:
    Blockchain() {
        chain.emplace_back(Block(0, "Genesis Block", "0"));
    }

    void addBlock(const std::string& data) {
        int index = chain.size();
        std::string previousHash = getLastBlock().getHash();
        chain.emplace_back(Block(index, data, previousHash));
    }

    bool isChainValid() const {
        for(size_t i = 1; i < chain.size(); i++) {
            const Block& currentBlock = chain[i];
            const Block& previousBlock = chain[i-1];

            // Verify hash
            if(currentBlock.getHash() != currentBlock.calculateHash()) {
                return false;
            }

            // Verify chain linkage
            if(currentBlock.getPreviousHash() != previousBlock.getHash()) {
                return false;
            }
        }
        return true;
    }

    void printChain() const {
        for(const Block& block : chain) {
            std::cout << "\nBlock #" << block.getIndex()
                      << "\nData: " << block.getData()
                      << "\nHash: " << block.getHash()
                      << "\nPrevious Hash: " << block.getPreviousHash()
                      << "\n-----------------" << std::endl;
        }
    }
};

int main() {
    Blockchain coin;
    
    std::cout << "Mining block 1..." << std::endl;
    coin.addBlock("Transaction: Alice -> Bob: 50 coins");
    
    std::cout << "\nMining block 2..." << std::endl;
    coin.addBlock("Transaction: Bob -> Charlie: 30 coins");
    
    std::cout << "\nBlockchain validity: " 
              << (coin.isChainValid() ? "VALID" : "INVALID") << std::endl;
    
    std::cout << "\nBlockchain:" << std::endl;
    coin.printChain();
    
    return 0;
}