// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    bool fEnabled = true;

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        ( 0,     uint256("0x00000ae665347e2abddbc4b2e5dd2547e72b512240c8215e31a04e7f15d15762"))
	( 10000,     uint256("0x0000000000049a4cad4daf08841ab8c75afc4b5e2068bacfd85c200b20f4a1e8"))
	( 15000,     uint256("0x00000000000036a9443704d13ed4b7736c49aedd5e667ab3ae7096b22887ea19"))
	( 20000,     uint256("0x0000000000001057872bc376590ed77fa3b56b574a577abab461a8f3d7ca2a0f"))
	( 25004,     uint256("0x0000000000008face9f5f048fb6be7884a89359497e922ca5cc6a5494a7ac3c0"))
	( 30000,     uint256("0x0000000000014537dca7b9333de329439081d8d66984c150bf322a2237118751"))
	( 35006,     uint256("0x00000000000146876c429b1df1ccfa6d7ffc5e21fa6efc0ec898bcb4255ca3a9"))
	( 40000,     uint256("0x000000000003e5b395991339e4adfcaa3b240481d222a05d851d957b201d121d"))
	( 45000,     uint256("0x0000000000010ce0aaa73f01ae87e1efb63c656490ee7cd90dd261457734c44b"))
	( 49203,     uint256("0x0000000000005a0c8708398f7f5d7881257be39acd1a7819b464281b1251edfc"))
	( 250000,     uint256("0x00000000000779168b6ab8fa353a793338f272de473c51b31f1562cca6de3ec3"))
	( 400000,     uint256("0x0000000000073b769b38a2a33eaeb46b83efd77c294fd7e49f5b9e362bd6dbb3"))
	( 435000,     uint256("0x000000000017e3e330be688ab32e3e01ef884d72e5251c2bd116d36547c3a4a2"))
        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1403277769, // * UNIX timestamp of last checkpoint block
        576770,     // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        2880        // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256("0x"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1374901773,
        0,
        2880
    };

    const CCheckpointData &Checkpoints() {
        if (TestNet())
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!fEnabled)
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        
        //fake123
        return hash == i->second;
        //return true;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (!fEnabled)
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;
		//fake123
        return checkpoints.rbegin()->first;
        //return 0;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!fEnabled)
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                //fake123
                return t->second;
                //return NULL;
        }
        return NULL;
    }
}
