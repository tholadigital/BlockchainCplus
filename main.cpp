/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: gift
 *
 * Created on 23 August 2019, 12:11 PM
 */

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include "Block.h"
#include "Blockchain.h"


using namespace std;
#include <openssl/sha.h>
string sha256(const string str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}


/*
 * 
 */

//implement block constructor
Block::Block(uint32_t nIndexIn, const string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn) {
    _nNonce = -1;
    _tTime = time(nullptr);
}
//implement Block class gethash method
string Block::GetHash() {
    return _sHash;
}

//implement Block class mineblock function
void Block::MineBlock(uint32_t nDifficulty) {
    char cstr[nDifficulty + 1];
    for (uint32_t i = 0; i < nDifficulty; ++i) {
        cstr[i] = '0';
    }
    cstr[nDifficulty] = '\0';
 
    string str(cstr);
    cout << "difficulty" << cstr << endl;
 
    do {
        _nNonce++;
        _sHash = _CalculateHash();
    } while (_sHash.substr(0, nDifficulty) != str);
 
    
    cout << "Block mined: " << _sHash << endl;
}

//implement block class funtion to calculate hash using sha256

inline string Block::_CalculateHash() const {
    stringstream ss;
    ss << _nIndex << _tTime << _sData << _nNonce << sPrevHash;
    string hashedData = sha256(ss.str());
    
    return hashedData;
}


//implement the blockchain construtor

Blockchain::Blockchain() {
    _vChain.emplace_back(Block(0, "Genesis Block"));
    _nDifficulty = 6;
}

// implement the blockchain add block function

void Blockchain::AddBlock(Block bNew) {
    bNew.sPrevHash = _GetLastBlock().GetHash();
    bNew.MineBlock(_nDifficulty);
    _vChain.push_back(bNew);
}

//implement Blockchain last function for getting the last added block
	
Block Blockchain::_GetLastBlock() const {
    return _vChain.back();
}

//implement Blockchain class function for getting the number of blocks

int Blockchain::ChainSize() const {
    return _vChain.size();
}

vector<string> Block::getPrivateData() const{
    vector<string> toReturn = {_sData, _sHash};
    return toReturn;
}

int main(int argc, char** argv) {
    Blockchain myChain = Blockchain();
    myChain.AddBlock(Block(myChain.ChainSize(), "second block"));
    
    
    cout << "block 1 " << myChain._GetBlockIndex(0).getPrivateData()[0] << endl;
    cout << "block 2 " << myChain._GetBlockIndex(1).getPrivateData()[0] << endl;
    return 0;
}

