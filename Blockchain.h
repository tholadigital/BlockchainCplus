/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Blockchain.h
 * Author: gift
 *
 * Created on 26 August 2019, 3:29 PM
 */

#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

//Blockchain class is where we store Blocks generated by Block class

class Blockchain {
public:
    const string coinName = "Afrika"; 
    Blockchain();
    void AddBlock(Block bNew);
    int ChainSize() const;
    Block _GetBlockIndex(uint32_t index) const{
        return _vChain[index];
    }
    bool _ValidateChain() const{
        for(int i = 0; i < ChainSize(); ++i){
            if(_vChain[i]._GetPrivateData()[1] !== _vChain[i]._CalculateHash() ) {
	                return false;
	    }
        }
    }
private:
    const unsigned int coinSupply = 7000;
    unsigned int _inCirculation; 
    uint32_t _nDifficulty;
    vector<Block> _vChain;
 
    Block _GetLastBlock() const;
   
    
};


#endif /* BLOCKCHAIN_H */

