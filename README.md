![Blockchain Diagram](https://img.money.com/2022/06/What-Is-Blockchain-Infographic.jpg?quality=60)

# Blockchain Implementation in C++ with OpenSSL

This project demonstrates a simple implementation of a blockchain using C++ and OpenSSL's EVP (Envelope) API for cryptographic hashing. The blockchain is based on the concept of blocks that contain data, a timestamp, a hash, and a reference to the previous block's hash. This chain of blocks ensures the integrity and immutability of the data stored in it.

## Features

- **Block Structure**: Each block contains:
  - `index`: The position of the block in the blockchain.
  - `timestamp`: The time when the block was created.
  - `data`: The transaction data stored in the block.
  - `previousHash`: The hash of the previous block to ensure the chain's integrity.
  - `hash`: The hash of the current block.
  - `nonce`: A value used in the proof-of-work mining process.

- **Proof of Work (PoW)**: Each block is mined by performing a computationally expensive process to find a hash that meets the required difficulty (i.e., a hash with a certain number of leading zeros).

- **Blockchain Integrity**: The blockchain ensures that each block's hash is correctly computed and that each block's previous hash matches the previous block's hash. The integrity of the entire blockchain is verified by the `isChainValid()` method.

## Requirements

- **C++ Compiler**: A C++11 compatible compiler (e.g., GCC, Clang, or MSVC).
- **OpenSSL**: OpenSSL libraries for cryptographic functions (for SHA-256 hashing).
  
  Ensure OpenSSL is installed on your system. For installation instructions, visit [OpenSSL's official website](https://www.openssl.org/).

## Compilation

To compile the code, use the following command:

```bash
g++ BlockChain.cpp -o BlockChain -lssl -lcrypto
```
This command links the OpenSSL SSL and Crypto libraries to the program.

Running the Program
After successful compilation, run the program with:
```bash
./BlockChain
```
Expected Output:
```bash
PS G:\BlockChain_Implementation> cd "g:\BlockChain_Implementation\" ; if ($?) { g++ BlockChain.cpp -o Bl
ockChain } ; if ($?) { .\BlockChain }                                                                   Block mined! Hash: 0000de2a032cef45
Mining block 1...
Block mined! Hash: 00005fe77bac9671

Mining block 2...
Block mined! Hash: 000062c080dd1f6d

Blockchain validity: VALID

Blockchain:

Block #0
Data: Genesis Block
Hash: 0000de2a032cef45
Previous Hash: 0
-----------------

Block #1
Data: Transaction: Alice -> Bob: 50 coins
Hash: 00005fe77bac9671
Previous Hash: 0000de2a032cef45
-----------------

Previous Hash: 0
-----------------

Block #1
Data: Transaction: Alice -> Bob: 50 coins
```
