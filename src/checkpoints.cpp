// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2013 StableCoin Developers

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

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (          0, uint256("0x0a59605118489aa9cde58e64210d3d56e246758fbabcd1482e54bf4032545221"))
            (       1000, uint256("0xebce88a0891a2b4cd24c9e1baace8381bb38963a603d5ac4ec67f85b2bbb3838"))
	    (       5000, uint256("0xdb8b18987a8af6fb5e7df2cedf2ba8eaa8c26990b93b82fe05cd1cd2656211a2"))
	    (       8000, uint256("0xc6e73ae9841cc79cdd825d5b5faadf3be6c4312b2ddb19f29ab8133d4b3cd679"))
	    (      20000, uint256("0x872b7e09b100567376643bf80dc1be2c495120635ea4163b4400561b64909f2d"))
            (      35120, uint256("0xccb94eddd81fb5dcbedd6b503f0ed2291c494c72a844447d8edd94ea8f7bff28"))
	    (      50000, uint256("0x619604d44987a9effb42d570d3185257bb235d68c076e86ec06fbe3acd3dc46a"))
	    (     100000, uint256("0x73bc352c4cbc62e958b2a8a70f731aa2b01397671e825bf449fdf2ac1420de84"))
	    (     150000, uint256("0x81be22a865629ca117661d10de2852e4cf600029328bc3d022a9e56567a63750"))
	    (     200000, uint256("0xe6a7af111a33a6e8d57a0045d6d059fddee6f50bfa001911d0e499aa8acda181"))
	    (     276000, uint256("0xd187fa6c813cafd086c3e653f29acdd7eee87e053d8c3724a6e35950a8339734"))
	    (     312200, uint256("0x3f86beee80b99d469857b7d411469efe5b3c418287ba993df6eb235a95db92c7"))
	    (     400000, uint256("0xd774a3662106be6459830f7bf2abd022a00758b874ddb899a0de6a4ef0e82d25"))
	    (     600000, uint256("0x70fa9138f6ba0b43d73174eb5f070790ff5a0ae145fa122dad7a330d21625237"))
	    (     800000, uint256("0xaef2d9bb0f740acba91ea10579fab96d6d32636a9b1042a8e2e773fd8705b08e"))
	    (    1000000, uint256("0xf0878ee26d3b00a06eb49819920f791b5333c0e109c1b7f637a052f4bfe1c76b"))
	    (    1200000, uint256("0x2353a9ecb03ef0e59587fb07519bf3a536d3ec2237a6fdcdfa006ea81990379d"))
	    (    1400000, uint256("0xe44daf295ed6ac561d08fe5dbd2e1b2500f31a350f1974d7b706725fb9d15072"))
	    (    1600000, uint256("0xb91fbfacba52435e8a6a8b343cc055d9210c53e9173403e9a4269f76349c739c"))
	    (    1800000, uint256("0x512ae55b5f753f84d73622e35fd0b7d17b820b304a5af360f692ddaf3b677685"))
	    (    2000000, uint256("0xe49e378c3c387e2cd7812285dd6a2cf5957f5745940e41f50111f1220e49280e"))
	    (    2100000, uint256("0x963834250029eb23420eefee372f61732ecaf3443c1b516fc46ad4782f09308a"))
	    (    2244312, uint256("0x51e549cdcfe952f2ec1572c4b965d03302e4e3eebb95036c25a8be82198259bf"))
            ;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
