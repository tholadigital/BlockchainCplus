/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Block.h
 * Author: gift
 *
 * Created on 23 August 2019, 12:35 PM
 */

#ifndef BLOCK_H
#define BLOCK_H

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif


using namespace std;

class Block {
public:
    string sPrevHash;
 
    Block(uint32_t nIndexIn, const string &sDataIn);
 
    string GetHash();
    
    string _CalculateHash() const;
    void MineBlock(uint32_t nDifficulty);
    vector<string> getPrivateData() const;
private:
    uint32_t _nIndex;
    int64_t _nNonce;
    string _sData;
    string _sHash;
    time_t _tTime;
 
};

#endif /* BLOCK_H */