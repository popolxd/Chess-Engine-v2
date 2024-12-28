#include "core.h"
#include "main.h"

#include <stdio.h>

uint64_t knightMoves[64] = {
132096ULL, 329728ULL, 659712ULL, 1319424ULL, 2638848ULL, 5277696ULL, 10489856ULL, 4202496ULL, 
33816580ULL, 84410376ULL, 168886289ULL, 337772578ULL, 675545156ULL, 1351090312ULL, 2685403152ULL, 1075839008ULL, 
8657044482ULL, 21609056261ULL, 43234889994ULL, 86469779988ULL, 172939559976ULL, 345879119952ULL, 687463207072ULL, 275414786112ULL, 
2216203387392ULL, 5531918402816ULL, 11068131838464ULL, 22136263676928ULL, 44272527353856ULL, 88545054707712ULL, 175990581010432ULL, 70506185244672ULL, 
567348067172352ULL, 1416171111120896ULL, 2833441750646784ULL, 5666883501293568ULL, 11333767002587136ULL, 22667534005174272ULL, 45053588738670592ULL, 18049583422636032ULL, 
145241105196122112ULL, 362539804446949376ULL, 725361088165576704ULL, 1450722176331153408ULL, 2901444352662306816ULL, 5802888705324613632ULL, 11533718717099671552ULL, 4620693356194824192ULL, 
288234782788157440ULL, 576469569871282176ULL, 1224997833292120064ULL, 2449995666584240128ULL, 4899991333168480256ULL, 9799982666336960512ULL, 1152939783987658752ULL, 2305878468463689728ULL, 
1128098930098176ULL, 2257297371824128ULL, 4796069720358912ULL, 9592139440717824ULL, 19184278881435648ULL, 38368557762871296ULL, 4679521487814656ULL, 9077567998918656ULL,
};

uint64_t kingMoves[64] = {
770ULL, 1797ULL, 3594ULL, 7188ULL, 14376ULL, 28752ULL, 57504ULL, 49216ULL, 
197123ULL, 460039ULL, 920078ULL, 1840156ULL, 3680312ULL, 7360624ULL, 14721248ULL, 12599488ULL, 
50463488ULL, 117769984ULL, 235539968ULL, 471079936ULL, 942159872ULL, 1884319744ULL, 3768639488ULL, 3225468928ULL, 
12918652928ULL, 30149115904ULL, 60298231808ULL, 120596463616ULL, 241192927232ULL, 482385854464ULL, 964771708928ULL, 825720045568ULL, 
3307175149568ULL, 7718173671424ULL, 15436347342848ULL, 30872694685696ULL, 61745389371392ULL, 123490778742784ULL, 246981557485568ULL, 211384331665408ULL, 
846636838289408ULL, 1975852459884544ULL, 3951704919769088ULL, 7903409839538176ULL, 15806819679076352ULL, 31613639358152704ULL, 63227278716305408ULL, 54114388906344448ULL, 
216739030602088448ULL, 505818229730443264ULL, 1011636459460886528ULL, 2023272918921773056ULL, 4046545837843546112ULL, 8093091675687092224ULL, 16186183351374184448ULL, 13853283560024178688ULL, 
144959613005987840ULL, 362258295026614272ULL, 724516590053228544ULL, 1449033180106457088ULL, 2898066360212914176ULL, 5796132720425828352ULL, 11592265440851656704ULL, 4665729213955833856ULL,
};

uint64_t bishopPosBlockers[64] = {
18049651735527936ULL, 70506452091904ULL, 275415828992ULL, 1075975168ULL, 38021120ULL, 8657588224ULL, 2216338399232ULL, 567382630219776ULL, 
9024825867763712ULL, 18049651735527424ULL, 70506452221952ULL, 275449643008ULL, 9733406720ULL, 2216342585344ULL, 567382630203392ULL, 1134765260406784ULL, 
4512412933816832ULL, 9024825867633664ULL, 18049651768822272ULL, 70515108615168ULL, 2491752130560ULL, 567383701868544ULL, 1134765256220672ULL, 2269530512441344ULL, 
2256206450263040ULL, 4512412900526080ULL, 9024834391117824ULL, 18051867805491712ULL, 637888545440768ULL, 1135039602493440ULL, 2269529440784384ULL, 4539058881568768ULL, 
1128098963916800ULL, 2256197927833600ULL, 4514594912477184ULL, 9592139778506752ULL, 19184279556981248ULL, 2339762086609920ULL, 4538784537380864ULL, 9077569074761728ULL, 
562958610993152ULL, 1125917221986304ULL, 2814792987328512ULL, 5629586008178688ULL, 11259172008099840ULL, 22518341868716544ULL, 9007336962655232ULL, 18014673925310464ULL, 
2216338399232ULL, 4432676798464ULL, 11064376819712ULL, 22137335185408ULL, 44272556441600ULL, 87995357200384ULL, 35253226045952ULL, 70506452091904ULL, 
567382630219776ULL, 1134765260406784ULL, 2832480465846272ULL, 5667157807464448ULL, 11333774449049600ULL, 22526811443298304ULL, 9024825867763712ULL, 18049651735527936ULL,
};

uint64_t rookPosBlockers[64] = {
282578800148862ULL, 565157600297596ULL, 1130315200595066ULL, 2260630401190006ULL, 4521260802379886ULL, 9042521604759646ULL, 18085043209519166ULL, 36170086419038334ULL, 
282578800180736ULL, 565157600328704ULL, 1130315200625152ULL, 2260630401218048ULL, 4521260802403840ULL, 9042521604775424ULL, 18085043209518592ULL, 36170086419037696ULL, 
282578808340736ULL, 565157608292864ULL, 1130315208328192ULL, 2260630408398848ULL, 4521260808540160ULL, 9042521608822784ULL, 18085043209388032ULL, 36170086418907136ULL, 
282580897300736ULL, 565159647117824ULL, 1130317180306432ULL, 2260632246683648ULL, 4521262379438080ULL, 9042522644946944ULL, 18085043175964672ULL, 36170086385483776ULL, 
283115671060736ULL, 565681586307584ULL, 1130822006735872ULL, 2261102847592448ULL, 4521664529305600ULL, 9042787892731904ULL, 18085034619584512ULL, 36170077829103616ULL, 
420017753620736ULL, 699298018886144ULL, 1260057572672512ULL, 2381576680245248ULL, 4624614895390720ULL, 9110691325681664ULL, 18082844186263552ULL, 36167887395782656ULL, 
35466950888980736ULL, 34905104758997504ULL, 34344362452452352ULL, 33222877839362048ULL, 30979908613181440ULL, 26493970160820224ULL, 17522093256097792ULL, 35607136465616896ULL, 
9079539427579068672ULL, 8935706818303361536ULL, 8792156787827803136ULL, 8505056726876686336ULL, 7930856604974452736ULL, 6782456361169985536ULL, 4485655873561051136ULL, 9115426935197958144ULL,
};

uint64_t bishopMagic[64] = { // 54
6168167234131206204ULL, 7327291298944347841ULL, 8004787300534292723ULL, 5647390685204270576ULL, 6677881260462294624ULL, 5910893672145665930ULL, 5654940481759122337ULL, 6646974917595440657ULL, 
2318713159155537611ULL, 4173197788230023150ULL, 6462034303257396629ULL, 4153447557800612183ULL, 4627136004962414480ULL, 8746423299086327192ULL, 4945247442685660478ULL, 6771407467386543169ULL, 
8934640702152951050ULL, 5937333422484423897ULL, 5169532001511594265ULL, 6715094128728618493ULL, 865329246285694398ULL, 841623027846457856ULL, 421354052268764988ULL, 4056375662277922588ULL, 
5310715495498626928ULL, 7326609928259273457ULL, 985703580202112547ULL, 3017068704790671584ULL, 1635962901375467816ULL, 199685674623147084ULL, 38802535718001945ULL, 3397782167695232309ULL, 
2405099923639596152ULL, 7770202899615320918ULL, 848509624925488124ULL, 2214572849807943637ULL, 5677491498946510918ULL, 788513339738062954ULL, 1600729497949096086ULL, 5780113545324838612ULL, 
5969139742244484986ULL, 733555697470355578ULL, 7547280983616426258ULL, 5640835123068034109ULL, 8321417091354459421ULL, 4162153635854347490ULL, 4274833533523558674ULL, 6194133428429738811ULL, 
2785126777422565274ULL, 5004031682218057695ULL, 8519442823047034277ULL, 6938788554819747620ULL, 6131587851916397846ULL, 3913884731626563968ULL, 7477690942398170670ULL, 4501671759515531276ULL, 
7890088381655802511ULL, 9059550046061077620ULL, 1280354379971328503ULL, 2469287887850941492ULL, 7674528323780210355ULL, 7719501016042267234ULL, 7099152882670759762ULL, 9163332092694046268ULL,
};
uint64_t lookupBishop[64][1024];

uint64_t rookMagic[64] = { // 51
4179351428085311809ULL, 2670917614531371131ULL, 8962154815099399453ULL, 4490594595795605182ULL, 8773777271809579034ULL, 575953870293013590ULL, 3673899336689754735ULL, 900143056474460063ULL, 
2557712696041868101ULL, 1792307249173100386ULL, 5612190770005007616ULL, 4896625712622713750ULL, 970612518740607900ULL, 9075613682530885158ULL, 4527331432505394979ULL, 3108460277551869263ULL, 
290068033762430999ULL, 6908622800879440779ULL, 7836398614559327452ULL, 8071770764156452690ULL, 3052552676091194275ULL, 9039223364529710065ULL, 3369357525526057917ULL, 7145302061872748919ULL, 
1780462201430643680ULL, 1464011196211030680ULL, 2219657242309415190ULL, 4239396218921225198ULL, 1674324143720594244ULL, 1118421120525427052ULL, 1268802966309863195ULL, 1897665661886030403ULL, 
726233724072914337ULL, 5171128844619579983ULL, 7492367503153367312ULL, 2380051046900436296ULL, 4767588629122259914ULL, 8389432463933145085ULL, 4721141388251282971ULL, 2429328186043615488ULL, 
7862808436477148543ULL, 3103211664664198803ULL, 8159640270982922078ULL, 1656133519409551047ULL, 3379285973981725573ULL, 8477965337305840777ULL, 1097331035441870463ULL, 8454881051123998609ULL, 
5978284652052709339ULL, 3389298646738946698ULL, 3390876049814143177ULL, 3255722722548729054ULL, 5376938575763753472ULL, 7330433049669996078ULL, 5899517996883109178ULL, 3185757926040499502ULL, 
2383397582373111258ULL, 8139310957975080506ULL, 8203231994999114210ULL, 4571967999530326614ULL, 8408872936138131918ULL, 4474388650675897054ULL, 7510836237099296988ULL, 5822600864610338258ULL,
};
uint64_t lookupRook[64][8192];

void InitDefaultGameState(GameState* gs)
{
    gs->bbs[wp] = 0x000000000000FF00ULL;
    gs->bbs[wn] = 0x0000000000000042ULL;
    gs->bbs[wb] = 0x0000000000000024ULL;
    gs->bbs[wr] = 0x0000000000000081ULL;
    gs->bbs[wq] = 0x0000000000000010ULL;
    gs->bbs[wk] = 0x0000000000000008ULL;

    gs->bbs[bp] = 0x00FF000000000000ULL;
    gs->bbs[bn] = 0x4200000000000000ULL;
    gs->bbs[bb] = 0x2400000000000000ULL;
    gs->bbs[br] = 0x8100000000000000ULL;
    gs->bbs[bq] = 0x1000000000000000ULL;
    gs->bbs[bk] = 0x0800000000000000ULL;

    gs->bbs[whiteP] = gs->bbs[wp] | gs->bbs[wn] | gs->bbs[wb] | gs->bbs[wr] | gs->bbs[wq] | gs->bbs[wk];
    gs->bbs[blackP] = gs->bbs[bp] | gs->bbs[bn] | gs->bbs[bb] | gs->bbs[br] | gs->bbs[bq] | gs->bbs[bk];
    gs->bbs[allP] = gs->bbs[whiteP] | gs->bbs[blackP];

    gs->enPassantSq = -1;
    gs->castle[0] = 1; gs->castle[1] = 1; gs->castle[2] = 1; gs->castle[3] = 1;
    gs->wtm= 1;
}

void InitGameStateFromFEN(GameState* gs, char* fen)
{
    for (uint8_t i = 0; i < 12; i++) {
        gs->bbs[i] = 0ULL;
    }

    uint16_t i = 0;

    uint8_t xPos = 7;
    uint8_t yPos = 7;

    // board
    while (fen[i] != ' ') {

        if (fen[i] > 47 && fen[i] < 58) { // cislo
            xPos -= fen[i] - 47;

        } else if (fen[i] == '/') {
            yPos--;
            xPos = 7;
        
        } else {
            switch (fen[i]) {
                case 'P':
                    gs->bbs[wp] += 1ULL << (yPos*8 + xPos); break;
                case 'N':
                    gs->bbs[wn] += 1ULL << (yPos*8 + xPos); break;
                case 'B':
                    gs->bbs[wb] += 1ULL << (yPos*8 + xPos); break;
                case 'R':
                    gs->bbs[wr] += 1ULL << (yPos*8 + xPos); break;
                case 'Q':
                    gs->bbs[wq] += 1ULL << (yPos*8 + xPos); break;
                case 'K':
                    gs->bbs[wk] += 1ULL << (yPos*8 + xPos); break;
                case 'p':
                    gs->bbs[bp] += 1ULL << (yPos*8 + xPos); break;
                case 'n':
                    gs->bbs[bn] += 1ULL << (yPos*8 + xPos); break;
                case 'b':
                    gs->bbs[bb] += 1ULL << (yPos*8 + xPos); break;
                case 'r':
                    gs->bbs[br] += 1ULL << (yPos*8 + xPos); break;
                case 'q':
                    gs->bbs[bq] += 1ULL << (yPos*8 + xPos); break;
                case 'k':
                    gs->bbs[bk] += 1ULL << (yPos*8 + xPos); break;
                default:
                    break;
            }
            xPos--;
        }
        i++;
    }
    i++;

    gs->bbs[whiteP] = gs->bbs[wp] | gs->bbs[wn] | gs->bbs[wb] | gs->bbs[wr] | gs->bbs[wq] | gs->bbs[wk];
    gs->bbs[blackP] = gs->bbs[bp] | gs->bbs[bn] | gs->bbs[bb] | gs->bbs[br] | gs->bbs[bq] | gs->bbs[bk];
    gs->bbs[allP] = gs->bbs[whiteP] | gs->bbs[blackP];

    // wtm
    if (fen[i] == 'w') gs->wtm = 1;
    else gs->wtm = 0;
    i += 2;

    // castling rights
    for (uint8_t j = 0; j < 4; j++) {
        gs->castle[j] = 0;
    }

    while (fen[i] != ' ') {
        switch (fen[i]) {
            case 'K':
                gs->castle[0] = 1; break;
            case 'Q':
                gs->castle[1] = 1; break;
            case 'k':
                gs->castle[2] = 1; break;
            case 'q':
                gs->castle[3] = 1; break;
            default:
                break;
        }
        i++;
    }
    i++;

    // en passant
    if (fen[i] == '-') gs->enPassantSq = -1;
    else {
        uint8_t col = 104 - fen[i];
        i++;
        uint8_t row = fen[i] - 1;

        gs->enPassantSq = row*8 + col;
    }
}

uint8_t GenPLPawnMoves(GameState* gs, uint8_t pos, uint8_t* PLMoves, uint8_t onlyCaptures)
{
    uint8_t movesLen = 0;

    if (!onlyCaptures && !(gs->bbs[allP] & (1ULL << (pos + gs->wtm*16 - 8)))) {
        PLMoves[movesLen] = pos + gs->wtm*16 - 8; movesLen++;

        if (pos / 8 == 6 - gs->wtm*5 && !(gs->bbs[allP] & (1ULL << (pos + gs->wtm*32 - 16)))) {
            PLMoves[movesLen] = pos + gs->wtm*32 - 16; movesLen++;
        }
    }

    if ((pos % 8 > 0 && gs->bbs[whiteP + gs->wtm] & (1ULL << (pos + gs->wtm*16 - 9)))
    || (gs->enPassantSq == pos + gs->wtm*16 - 9)) {
        PLMoves[movesLen] = pos + gs->wtm*16 - 9; movesLen++;
    }

    if ((pos % 8 < 7 && gs->bbs[whiteP + gs->wtm] & (1ULL << (pos + gs->wtm*16 - 7)))
    || (gs->enPassantSq == pos + gs->wtm*16 - 7)) {
        PLMoves[movesLen] = pos + gs->wtm*16 - 7; movesLen++;
    }

    return movesLen;
}

uint8_t GenPLKnightMoves(GameState* gs, uint8_t pos, uint8_t* PLMoves, uint8_t onlyCaptures)
{
    uint64_t filter = (onlyCaptures) ? gs->bbs[whiteP + gs->wtm] : (~gs->bbs[blackP - gs->wtm]);
    uint64_t movesBB = knightMoves[pos] & filter;
    return OnesFromBBToArr(movesBB, PLMoves);
}

uint8_t GenPLKingMoves(GameState* gs, uint8_t pos, uint8_t* PLMoves, uint8_t onlyCaptures)
{
    uint64_t filter = (onlyCaptures) ? gs->bbs[whiteP + gs->wtm] : (~gs->bbs[blackP - gs->wtm]);
    uint64_t movesBB = kingMoves[pos] & filter;
    uint8_t movesLen = OnesFromBBToArr(movesBB, PLMoves);

    if (!onlyCaptures && pos == 59 - gs->wtm*56 && !IsCheck(gs)) { // TODO: castle check checking
        if (gs->castle[2 - gs->wtm*2] && !(gs->bbs[allP] & (1ULL << (58 - gs->wtm*56)) || gs->bbs[allP] & (1ULL << (57 - gs->wtm*56)))) {
            
            // soft move
            gs->bbs[bk - gs->wtm*6] += (1ULL << (57 - gs->wtm*56)) - (1ULL << pos);
            gs->bbs[blackP - gs->wtm] += (1ULL << (57 - gs->wtm*56)) - (1ULL << pos);
            gs->bbs[allP] += (1ULL << (57 - gs->wtm*56)) - (1ULL << pos);

            if (!IsCheck(gs)) { 
                PLMoves[movesLen] = 57 - gs->wtm*56; movesLen++; 
            }

            // undo
            gs->bbs[bk - gs->wtm*6] -= (1ULL << (57 - gs->wtm*56)) - (1ULL << pos);
            gs->bbs[blackP - gs->wtm] -= (1ULL << (57 - gs->wtm*56)) - (1ULL << pos);
            gs->bbs[allP] -= (1ULL << (57 - gs->wtm*56)) - (1ULL << pos);
        }
        if (gs->castle[3 - gs->wtm*2] && !(gs->bbs[allP] & (1ULL << (60 - gs->wtm*56)) || gs->bbs[allP] & (1ULL << (61 - gs->wtm*56)))) {

            // soft move
            gs->bbs[bk - gs->wtm*6] += (1ULL << (60 - gs->wtm*56)) - (1ULL << pos);
            gs->bbs[blackP - gs->wtm] += (1ULL << (60 - gs->wtm*56)) - (1ULL << pos);
            gs->bbs[allP] += (1ULL << (60 - gs->wtm*56)) - (1ULL << pos);

            if (!IsCheck(gs)) { 
                PLMoves[movesLen] = 61 - gs->wtm*56; movesLen++; 
            }

            // undo
            gs->bbs[bk - gs->wtm*6] -= (1ULL << (60 - gs->wtm*56)) - (1ULL << pos);
            gs->bbs[blackP - gs->wtm] -= (1ULL << (60 - gs->wtm*56)) - (1ULL << pos);
            gs->bbs[allP] -= (1ULL << (60 - gs->wtm*56)) - (1ULL << pos);
        }
    }

    return movesLen;
}

uint8_t GenPLBishopMoves(GameState* gs, uint8_t pos, uint8_t* PLMoves, uint8_t onlyCaptures)
{
    uint64_t blockers = bishopPosBlockers[pos] & gs->bbs[allP];
    uint16_t index = (blockers * bishopMagic[pos]) >> 54;

    uint64_t filter = (onlyCaptures) ? gs->bbs[whiteP + gs->wtm] : (~gs->bbs[blackP - gs->wtm]);
    uint64_t movesBB = lookupBishop[pos][index] & filter;
    return OnesFromBBToArr(movesBB, PLMoves);
}

uint8_t GenPLRookMoves(GameState* gs, uint8_t pos, uint8_t* PLMoves, uint8_t onlyCaptures)
{
    uint64_t blockers = rookPosBlockers[pos] & gs->bbs[allP];
    uint16_t index = (blockers * rookMagic[pos]) >> 51;

    uint64_t filter = (onlyCaptures) ? gs->bbs[whiteP + gs->wtm] : (~gs->bbs[blackP - gs->wtm]);
    uint64_t movesBB = lookupRook[pos][index] & filter;
    return OnesFromBBToArr(movesBB, PLMoves);
}

uint8_t GenPLQueenMoves(GameState* gs, uint8_t pos, uint8_t* PLMoves, uint8_t onlyCaptures)
{
    uint8_t movesLen = GenPLBishopMoves(gs, pos, PLMoves, onlyCaptures);
    movesLen += GenPLRookMoves(gs, pos, &PLMoves[movesLen], onlyCaptures);
    return movesLen;
}

uint8_t GenAllPosMoves(GameState* gs, Move* moves, uint8_t onlyCaptures)
{
    uint8_t movesLen = 0; 
    
    uint8_t PLMoves[27];
    uint8_t PLMovesLen = 0;

    uint8_t locs[10];
    uint8_t locsLen;

    for (int8_t i = 6 - gs->wtm*6; i < 12 - gs->wtm*6; i++) {
        locsLen = OnesFromBBToArr(gs->bbs[i], locs);

        switch (i) {
            case wp:
            case bp:
                for (uint8_t j = 0; j < locsLen; j++) {
                    PLMovesLen = GenPLPawnMoves(gs, locs[j], PLMoves, onlyCaptures);
                    movesLen += GetLMovesFromPLMoves(gs, locs[j], bp - gs->wtm*6, PLMoves, PLMovesLen, &moves[movesLen]);
                }
                break;
            case wn:
            case bn:
                for (uint8_t j = 0; j < locsLen; j++) {
                    PLMovesLen = GenPLKnightMoves(gs, locs[j], PLMoves, onlyCaptures);
                    movesLen += GetLMovesFromPLMoves(gs, locs[j], bn - gs->wtm*6, PLMoves, PLMovesLen, &moves[movesLen]);
                }
                break;
            case wb:
            case bb:
                for (uint8_t j = 0; j < locsLen; j++) {
                    PLMovesLen = GenPLBishopMoves(gs, locs[j], PLMoves, onlyCaptures);
                    movesLen += GetLMovesFromPLMoves(gs, locs[j], bb - gs->wtm*6, PLMoves, PLMovesLen, &moves[movesLen]);
                }
                break;
            case wr:
            case br:
                for (uint8_t j = 0; j < locsLen; j++) {
                    PLMovesLen = GenPLRookMoves(gs, locs[j], PLMoves, onlyCaptures);
                    movesLen += GetLMovesFromPLMoves(gs, locs[j], br - gs->wtm*6, PLMoves, PLMovesLen, &moves[movesLen]);
                }
                break;
            case wq:
            case bq:
                for (uint8_t j = 0; j < locsLen; j++) {
                    PLMovesLen = GenPLQueenMoves(gs, locs[j], PLMoves, onlyCaptures);
                    movesLen += GetLMovesFromPLMoves(gs, locs[j], bq - gs->wtm*6, PLMoves, PLMovesLen, &moves[movesLen]);
                }
                break;
            case wk:
            case bk:
                for (uint8_t j = 0; j < locsLen; j++) {
                    PLMovesLen = GenPLKingMoves(gs, locs[j], PLMoves, onlyCaptures);
                    movesLen += GetLMovesFromPLMoves(gs, locs[j], bk - gs->wtm*6, PLMoves, PLMovesLen, &moves[movesLen]);
                }
                break;
        }
    }

    return movesLen;
}

uint8_t GetLMovesFromPLMoves(GameState* gs, uint8_t pos, uint8_t pieceType, uint8_t* PLMoves, uint8_t PLMovesLen, Move* LMoves)
{
    if (PLMovesLen == 0) return 0; // lot of times there are no legal moves

    // if i delete piece and there is no check, then there never will be a check
    if (pieceType != bk - gs->wtm*6) {
        gs->bbs[pieceType] -= 1UL << pos;
        gs->bbs[blackP - gs->wtm] -= 1UL << pos;
        gs->bbs[allP] -= 1UL << pos;

        uint8_t isCheck = IsCheck(gs);

        gs->bbs[pieceType] += 1UL << pos;
        gs->bbs[blackP - gs->wtm] += 1UL << pos;
        gs->bbs[allP] += 1UL << pos;

        if (!isCheck) { // all PL moves are L moves
            for (uint8_t i = 0; i < PLMovesLen; i++) {
                LMoves[i] = (Move){.startSq = pos, .endSq = PLMoves[i]};
            }
            return PLMovesLen;
        }
    }

    uint8_t LMovesLen = 0;

    uint64_t saveBitboards[15]; // TODO: it is little inefficient
    for (uint8_t i = 0; i < 15; i++) saveBitboards[i] = gs->bbs[i];

    for (uint8_t i = 0; i < PLMovesLen; i++) {

        // make soft move
        uint8_t posToDelete;
        if (pieceType == bp - gs->wtm*6 && PLMoves[i] == gs->enPassantSq) posToDelete = PLMoves[i] - gs->wtm*16 + 8;
        else posToDelete = PLMoves[i];

        // delete from start
        gs->bbs[pieceType] -= 1UL << pos;
        gs->bbs[blackP - gs->wtm] -= 1UL << pos;
        gs->bbs[allP] -= 1UL << pos;

        // delete from end
        for (uint8_t j = gs->wtm*6; j < 6 + gs->wtm*6; j++) {
            gs->bbs[j] &= ~(1UL << posToDelete);
        }
        gs->bbs[whiteP + gs->wtm] &= ~(1UL << posToDelete);
        gs->bbs[allP] &= ~(1ULL << posToDelete);

        // add to end
        gs->bbs[pieceType] += 1UL << PLMoves[i];
        gs->bbs[blackP - gs->wtm] += 1UL << PLMoves[i];
        gs->bbs[allP] += 1UL << PLMoves[i];

        // check if not check
        if (!IsCheck(gs)) {
            LMoves[LMovesLen] = (Move){.startSq = pos, .endSq = PLMoves[i]}; LMovesLen++;
        }

        // undo
        for (uint8_t j = 0; j < 15; j++) {
            gs->bbs[j] = saveBitboards[j];
        }
    }

    return LMovesLen;
}

uint8_t IsCheck(GameState* gs)
{
    uint8_t kingPos = __builtin_ctzll(gs->bbs[bk - gs->wtm*6]);

    // pawn
    if (kingPos % 8 > 0 && gs->bbs[wp + gs->wtm*6] & (1ULL << (kingPos + gs->wtm*16 - 9))) return 1;
    if (kingPos % 8 < 7 && gs->bbs[wp + gs->wtm*6] & (1ULL << (kingPos + gs->wtm*16 - 7))) return 1;

    // knight
    if (gs->bbs[wn + gs->wtm*6] & knightMoves[kingPos]) return 1;

    // king
    if (gs->bbs[wk + gs->wtm*6] & kingMoves[kingPos]) return 1;

    // bishop and queen
    uint64_t blockers = bishopPosBlockers[kingPos] & gs->bbs[allP];
    uint16_t index = (blockers * bishopMagic[kingPos]) >> 54;
    if (gs->bbs[wb + gs->wtm*6] & lookupBishop[kingPos][index] || gs->bbs[wq + gs->wtm*6] & lookupBishop[kingPos][index]) return 1;

    // rook and queen
    blockers = rookPosBlockers[kingPos] & gs->bbs[allP];
    index = (blockers * rookMagic[kingPos]) >> 51;
    if (gs->bbs[wr + gs->wtm*6] & lookupRook[kingPos][index] || gs->bbs[wq + gs->wtm*6] & lookupRook[kingPos][index]) return 1;

    return 0;
}

uint8_t OnesFromBBToArr(uint64_t bitb, uint8_t* arr)
{
    uint8_t len = __builtin_popcountll(bitb);

    for (uint8_t i = 0; i < len; i++) {
        int index = __builtin_ctzll(bitb);
        bitb &= (bitb - 1);

        arr[i] = index;
    }

    return len;
}

uint16_t GenAllPosBlockersComb(uint64_t posBlockersBB, uint64_t* allComb)
{
    uint8_t spots[12];
    uint8_t spotsLen = OnesFromBBToArr(posBlockersBB, spots);

    uint16_t allCombLen = 1 << spotsLen;

    for (uint16_t i = 0; i < allCombLen; i++) {

        uint64_t curBlockers = 0ULL;
        for (uint8_t j = 0; j < spotsLen; j++) {
            if (i & (1ULL << j)) curBlockers += 1ULL << spots[j];
        }

        allComb[i] = curBlockers;
    }

    return allCombLen;
}

void FillLookups()
{
    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 8; j++) {

            uint64_t allPosBlockersComb[4096];
            uint16_t len = GenAllPosBlockersComb(bishopPosBlockers[i*8 + j], allPosBlockersComb);

            for (uint16_t k = 0; k < len; k++) {
                // classic way of figuring out possible moves
                uint64_t curPosMoves = 0ULL;

                for (uint8_t l = 1; l <= min(j, i); l++) {
                    curPosMoves += 1ULL << ((i-l)*8 + j-l);
                    if (allPosBlockersComb[k] & (1ULL << ((i-l)*8 + j-l))) break;
                }
                for (uint8_t l = 1; l <= min(7-j, i); l++) {
                    curPosMoves += 1ULL << ((i-l)*8 + j+l);
                    if (allPosBlockersComb[k] & (1ULL << ((i-l)*8 + j+l))) break;
                }
                for (uint8_t l = 1; l <= min(j, 7-i); l++) {
                    curPosMoves += 1ULL << ((i+l)*8 + j-l);
                    if (allPosBlockersComb[k] & (1ULL << ((i+l)*8 + j-l))) break;
                }
                for (uint8_t l = 1; l <= min(7-j, 7-i); l++) {
                    curPosMoves += 1ULL << ((i+l)*8 + j+l);
                    if (allPosBlockersComb[k] & (1ULL << ((i+l)*8 + j+l))) break;
                }

                uint16_t index = (allPosBlockersComb[k] * bishopMagic[i*8 + j]) >> 54;
                lookupBishop[i*8 + j][index] = curPosMoves;
            }

            len = GenAllPosBlockersComb(rookPosBlockers[i*8 + j], allPosBlockersComb);
            for (uint16_t k = 0; k < len; k++) {
                // classic way of figuring out possible moves
                uint64_t curPosMoves = 0ULL;

                for (uint8_t l = 1; l <= j; l++) {
                    curPosMoves += 1ULL << (i*8 + j-l);
                    if (allPosBlockersComb[k] & (1ULL << (i*8 + j-l))) break;
                }
                for (uint8_t l = 1; l <= 7-j; l++) {
                    curPosMoves += 1ULL << (i*8 + j+l);
                    if (allPosBlockersComb[k] & (1ULL << (i*8 + j+l))) break;
                }
                for (uint8_t l = 1; l <= i; l++) {
                    curPosMoves += 1ULL << ((i-l)*8 + j);
                    if (allPosBlockersComb[k] & (1ULL << ((i-l)*8 + j))) break;
                }
                for (uint8_t l = 1; l <= 7-i; l++) {
                    curPosMoves += 1ULL << ((i+l)*8 + j);
                    if (allPosBlockersComb[k] & (1ULL << ((i+l)*8 + j))) break;
                }

                uint16_t index = (allPosBlockersComb[k] * rookMagic[i*8 + j]) >> 51;
                lookupRook[i*8 + j][index] = curPosMoves;
            }
        }
    }
}

void MakeMove(GameState* gs, Move move)
{
    // castle
    if (gs->bbs[bk - gs->wtm*6] & (1ULL << move.startSq)) {

        if (move.startSq == 59 - gs->wtm*56) {
            if (move.endSq == 57 - gs->wtm*56) { // king castle
                gs->bbs[br - gs->wtm*6] += (1ULL << (58 - gs->wtm*56)) - (1ULL << (56 - gs->wtm*56));
                gs->bbs[blackP - gs->wtm] += (1ULL << (58 - gs->wtm*56)) - (1ULL << (56 - gs->wtm*56));
                gs->bbs[allP] += (1ULL << (58 - gs->wtm*56)) - (1ULL << (56 - gs->wtm*56));

            } else if (move.endSq == 61 - gs->wtm*56) { // queen castle
                gs->bbs[br - gs->wtm*6] += (1ULL << (60 - gs->wtm*56)) - (1ULL << (63 - gs->wtm*56));
                gs->bbs[blackP - gs->wtm] += (1ULL << (60 - gs->wtm*56)) - (1ULL << (63 - gs->wtm*56));
                gs->bbs[allP] += (1ULL << (60 - gs->wtm*56)) - (1ULL << (63 - gs->wtm*56));
            }
        }
        gs->castle[2 - gs->wtm*2] = 0; gs->castle[3 - gs->wtm*2] = 0;
    }

    if (move.startSq == 0 || move.endSq == 0) gs->castle[0] = 0;
    if (move.startSq == 7 || move.endSq == 7) gs->castle[1] = 0;
    if (move.startSq == 56 || move.endSq == 56) gs->castle[2] = 0;
    if (move.startSq == 63 || move.endSq == 63) gs->castle[3] = 0;

    // en-passant
    if (move.endSq == gs->enPassantSq && gs->bbs[bp - gs->wtm*6] & (1ULL << move.startSq)) {
        gs->bbs[wp + gs->wtm*6] -= 1ULL << (move.endSq - gs->wtm*16 + 8);
        gs->bbs[whiteP + gs->wtm] -= 1ULL << (move.endSq - gs->wtm*16 + 8);
        gs->bbs[allP] -= 1ULL << (move.endSq - gs->wtm*16 + 8);
    }
    if (gs->bbs[bp - gs->wtm*6] & (1ULL << move.startSq) && move.startSq - move.endSq == 16 - gs->wtm*32) {
        gs->enPassantSq = move.endSq - gs->wtm*16 + 8;
    } else {
        gs->enPassantSq = -1;
    }

    // standart
    uint8_t selectedPiece;
    for (uint8_t i = 6 - gs->wtm*6; i < 12 - gs->wtm*6; i++) {
        if (gs->bbs[i] & (1ULL << move.startSq)) {
            selectedPiece = i;
            break;
        }
    }

    for (uint8_t i = gs->wtm*6; i < 6 + gs->wtm*6; i++) {
        gs->bbs[i] &= ~(1ULL << move.endSq);
    }
    gs->bbs[whiteP + gs->wtm] &= ~(1ULL << move.endSq);
    gs->bbs[allP] &= ~(1ULL << move.endSq);

    gs->bbs[selectedPiece] -= 1ULL << move.startSq;
    gs->bbs[blackP - gs->wtm] -= 1ULL << move.startSq;
    gs->bbs[allP] -= 1ULL << move.startSq;

    // promotion
    if (selectedPiece == bp - gs->wtm*6 && move.endSq / 8 == gs->wtm*7) {
        gs->bbs[bq - gs->wtm*6] += 1ULL << move.endSq;
        gs->bbs[blackP - gs->wtm] += 1ULL << move.endSq;
        gs->bbs[allP] += 1ULL << move.endSq;
    } else {
        gs->bbs[selectedPiece] += 1ULL << move.endSq;
        gs->bbs[blackP - gs->wtm] += 1ULL << move.endSq;
        gs->bbs[allP] += 1ULL << move.endSq;
    }

    gs->wtm = !gs->wtm;
}

void CopyGameState(GameState* to, GameState* from)
{
    to->wtm = from->wtm;
    to->enPassantSq = from->enPassantSq;
    for (uint8_t i = 0; i < 4; i++) {
        to->castle[i] = from->castle[i];
    }
    for (uint8_t i = 0; i < 15; i++) {
        to->bbs[i] = from->bbs[i];
    }
}