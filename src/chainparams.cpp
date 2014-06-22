// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

//
// Main network
//

static const char * pnSeed[] =
{
	"66.85.164.76",
	"184.95.40.150",
	"107.170.140.109",
	"162.243.15.107"
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0x1a;
        pchMessageStart[1] = 0x3b;
        pchMessageStart[2] = 0x3c;
        pchMessageStart[3] = 0x7e;
        vAlertPubKey = ParseHex("04f98b76210c6ab77a59927afb30bc1419e9ef94cb00d9f9a26f5a1eb2a7f0d185b4e4200d8f3c1860e2b305ce448db1f703fc6a673888ee3c0c2ce8fec74e5337");
        nDefaultPort = 8921;
        nRPCPort = 8920;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);
        nSubsidyHalvingInterval = 200000;

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
  
//00000ae665347e2abddbc4b2e5dd2547e72b512240c8215e31a04e7f15d15762
//888b2c9089c7694de6a2e562956427aa126400d4fead903c21ef3b98b3fa666a
//1e0fffff
//CBlock(hash=00000ae665347e2abddbc4b2e5dd2547e72b512240c8215e31a04e7f15d15762, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=888b2c9089c7694de6a2e562956427aa126400d4fead903c21ef3b98b3fa666a, nTime=1394128351, nBits=1e0fffff, nNonce=1713038, vtx=1)
//  CTransaction(hash=888b2c9089, ver=1, vin.size=1, vout.size=1, nLockTime=0)
//    CTxIn(COutPoint(0000000000, 4294967295), coinbase 04ffff001d010434332d362d32303134206c656168206d63677261746820676f6f646d616e20646f78656420426974636f696e20696e76656e746f72)
//    CTxOut(nValue=100000.00000000, scriptPubKey=04678afdb0fe5548271967f1a67130)
//  vMerkleTree: 888b2c9089c7694de6a2e562956427aa126400d4fead903c21ef3b98b3fa666a 
 

        const char* pszTimestamp = "3-6-2014 leah mcgrath goodman doxed Bitcoin inventor";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 100000 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1394128351;
        genesis.nBits    = 0x1e0fffff;
        genesis.nNonce   = 1713038;
        
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        //comment out
        while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
           if (++genesis.nNonce==0) break;
           hashGenesisBlock = genesis.GetHash();
        }
		//comment out

        printf("%s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        printf("%x\n", bnProofOfWorkLimit.GetCompact());
        genesis.print();
        
        
        assert(hashGenesisBlock == uint256("0x00000ae665347e2abddbc4b2e5dd2547e72b512240c8215e31a04e7f15d15762"));
        assert(genesis.hashMerkleRoot == uint256("0x888b2c9089c7694de6a2e562956427aa126400d4fead903c21ef3b98b3fa666a"));

        vSeeds.push_back(CDNSSeedData("66.85.164.76", "66.85.164.76"));


        base58Prefixes[PUBKEY_ADDRESS] = 73;
        base58Prefixes[SCRIPT_ADDRESS] = 1;
        base58Prefixes[SECRET_KEY] = 337;

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' 
            const int64 nTwoDays = 2 * 24 * 60 * 60;
            CAddress addr(CService(pnSeed[i], GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nTwoDays) - nTwoDays;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0x0a;
        pchMessageStart[1] = 0x0b;
        pchMessageStart[2] = 0x0c;
        pchMessageStart[3] = 0x0d;
        vAlertPubKey = ParseHex("04deffaef5b9552d1635013708eff25f2fac734cd6720d86fe83f9618572eb095b738efd752128b885c40ca0a37535df5a4b2b2cae5c80cea9bf315fb67ce9fcb2");
        nDefaultPort = 17921;
        nRPCPort = 17920;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1388822738;
        genesis.nNonce = 414708675;
        
        
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        //while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
        //    if (++genesis.nNonce==0) break;
        //   hashGenesisBlock = genesis.GetHash();
        //}

        printf("%s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        genesis.print();
        
        //assert(hashGenesisBlock == uint256("0x"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // vSeeds.push_back(CDNSSeedData("WeAreSatoshi.test", "test.WeAreSatoshi.org"));

        base58Prefixes[PUBKEY_ADDRESS] = 73;
        base58Prefixes[SCRIPT_ADDRESS] = 188;
        base58Prefixes[SECRET_KEY] = 239;

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0x0f;
        pchMessageStart[2] = 0xa5;
        pchMessageStart[3] = 0x5a;
        nSubsidyHalvingInterval = 150;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1296688602;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 3;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        
        //// debug print
        hashGenesisBlock = genesis.GetHash();
        //while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
        //    if (++genesis.nNonce==0) break;
        //    hashGenesisBlock = genesis.GetHash();
        //}

        printf("%s\n", hashGenesisBlock.ToString().c_str());
        printf("%s\n", genesis.hashMerkleRoot.ToString().c_str());
        genesis.print();

        // assert(hashGenesisBlock == uint256("0x13d8d31dde96874006da503dd2b63fa68c698dc823334359e417aa3a92f80433"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.

        base58Prefixes[PUBKEY_ADDRESS] = 0;
        base58Prefixes[SCRIPT_ADDRESS] = 5;
        base58Prefixes[SECRET_KEY] = 128;
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
