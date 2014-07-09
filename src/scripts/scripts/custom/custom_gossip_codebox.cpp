/*
########################################################
# This file will be used for Custom TBN NPC. It will   #
# welcome new players and give some explinations about #
# the realm. If the char is on an account without any  #
# existing char on lvl 70 the player will be able to   #
# level up and grand some things.                      #
#######################################################################################
#                                                                                     #
# Batch into Char DB:                                                                 #
#                                                                                     #
# DROP TABLE IF EXISTS `character_push`;                                              #
# CREATE TABLE `character_push` (                                                     #
# `account` int(11) NOT NULL,                                                         #
# `ip` varchar(30) CHARACTER SET utf8 NOT NULL                                        #
# ) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='character_push';   #
#                                                                                     #
# Batch into World DB:                                                                #
#                                                                                     #
# INSERT INTO npc_texts bla . . .                                                     #
#######################################################################################
*/

#include "precompiled.h"
#include <cstring>

bool GossipHello_custom_gossip_codebox(Player *Player, Creature *Creature) {
    Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    Player->ADD_GOSSIP_ITEM(0, "Einleitung ueberspringen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    Player->PlayerTalkClass->SendGossipMenu(30000, Creature->GetGUID());
    return true;
}

bool GossipSelect_custom_gossip_codebox(Player* Player, Creature* Creature, uint32 /*sender*/, uint32 action)
{
    uint32 professions = 0;
    switch (action) {
        case GOSSIP_ACTION_INFO_DEF + 2:
            Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            Player->PlayerTalkClass->SendGossipMenu(30001, Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            Player->PlayerTalkClass->SendGossipMenu(30002, Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:
            Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            Player->PlayerTalkClass->SendGossipMenu(30003, Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:
            Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            Player->PlayerTalkClass->SendGossipMenu(30004, Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:
            Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            Player->PlayerTalkClass->SendGossipMenu(30005, Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:
            Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            Player->PlayerTalkClass->SendGossipMenu(30006, Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:
            Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            Player->PlayerTalkClass->SendGossipMenu(30007, Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:
            Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            Player->PlayerTalkClass->SendGossipMenu(30008, Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:
        {
            switch(Player->GetValidForPush())
            {
                case 0: // zu hohes level aber noch einen char frei fuer push
                {
                    Player->ADD_GOSSIP_ITEM(0, "Schliessen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 111);
                    Player->PlayerTalkClass->SendGossipMenu(30014, Creature->GetGUID());
                    return true;
                }
                case 1: // zu hohes level und sowieso bereits 2 ueber 60
                {
                    Player->ADD_GOSSIP_ITEM(0, "Schliessen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 111);
                    Player->PlayerTalkClass->SendGossipMenu(30015, Creature->GetGUID());
                    return true;
                }
                case 2: // bereits zu viele auf zu hohem level
                {
                    Player->ADD_GOSSIP_ITEM(0, "Schliessen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 111);
                    Player->PlayerTalkClass->SendGossipMenu(30010, Creature->GetGUID());
                    return true;
                }
                case 3: // alles okay, gib feuer
                {
                    Player->ADD_GOSSIP_ITEM(0, "Setz mich auf Level 60", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
                    Player->PlayerTalkClass->SendGossipMenu(30009, Creature->GetGUID());
                    return true;
                }
                case 4: // Second Account
                {
                    Player->ADD_GOSSIP_ITEM(0, "Schliessen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 111);
                    Player->PlayerTalkClass->SendGossipMenu(30020, Creature->GetGUID());
                    return true;
                }
                default:
                    return false;
            }
        }
        case GOSSIP_ACTION_INFO_DEF + 11:
            Player->Push();
            Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
            Player->PlayerTalkClass->SendGossipMenu(30011, Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 111:
            Player->PlayerTalkClass->CloseGossip();
            return false;
        case GOSSIP_ACTION_INFO_DEF + 12:
            switch (Player->getClass()) {
                case CLASS_WARRIOR:
                    Player->ADD_GOSSIP_ITEM(0, "Schadenverursacher", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
                    Player->ADD_GOSSIP_ITEM(0, "Tank", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
                    break;
                case CLASS_PALADIN:
                    Player->ADD_GOSSIP_ITEM(0, "Schadenverursacher", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
                    // do we realy need a shokadin?
                    // Player->ADD_GOSSIP_ITEM(0, "DD - Shocka", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+151);
                    Player->ADD_GOSSIP_ITEM(0, "Tank", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 16);
                    Player->ADD_GOSSIP_ITEM(0, "Heiler", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 17);
                    break;
                case CLASS_HUNTER:
                    Player->ADD_GOSSIP_ITEM(0, "Schadenverursacher", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 18);
                    break;
                case CLASS_ROGUE:
                    Player->ADD_GOSSIP_ITEM(0, "Schadenverursacher", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 19);
                    break;
                case CLASS_PRIEST:
                    Player->ADD_GOSSIP_ITEM(0, "Schadenverursacher", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
                    Player->ADD_GOSSIP_ITEM(0, "Heiler", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
                    break;
                case CLASS_SHAMAN:
                    Player->ADD_GOSSIP_ITEM(0, "Schadenverursacher - Verstaerker", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
                    Player->ADD_GOSSIP_ITEM(0, "Schadenverursacher - Elementar", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
                    Player->ADD_GOSSIP_ITEM(0, "Heiler", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);
                    break;
                case CLASS_MAGE:

                    Player->ADD_GOSSIP_ITEM(0, "Schadenverursacher", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25);
                    break;
                case CLASS_WARLOCK:
                    Player->ADD_GOSSIP_ITEM(0, "Schadenverursacher", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 26);
                    break;
                case CLASS_DRUID:
                    Player->ADD_GOSSIP_ITEM(0, "Schadenverursacher - Katze", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 27);
                    Player->ADD_GOSSIP_ITEM(0, "Schadenverursacher - Eule", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 28);
                    Player->ADD_GOSSIP_ITEM(0, "Heiler", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 29);
                    Player->ADD_GOSSIP_ITEM(0, "Tank", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
                    break;
            }
            Player->PlayerTalkClass->SendGossipMenu(30012, Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 13:
        {
            // WARRIOR - DD -fertig
            //               Helm,   Kette, Schulter, 0, Brust, Gurt,  Beine, Füße,  Arme,  Hände, Ring,  Ring2, Schmuck, Schmuck, Umhang, Waffe, 2HWaffe, Fernk
            uint16 items[] = {16731, 22340, 16733,    0, 16730, 16736, 16732, 16734, 16735, 16737, 18701, 13098, 7734,    22321,   13397,  22404, 14487,   18680};
            Player->EquipForPush(items);
            if (!Player->HasItemCount(28053, 200, true))
                Player->AddItem(28053, 200);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 14:
        {
            // WARRIOR - TANK -ü
            uint16 items[] = {12620,13177,22001,0,18503,21503,22000,20710,21996,14525,22680, 19912,21784,21567,19888,19968,12602,19993};
            Player->EquipForPush(items);
            if (!Player->HasItemCount(28053, 200, true))
                Player->AddItem(28053, 200);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 15:
        {
            // PALADIN - DD - fertig
            uint16 items[] = {16727, 22340, 16729, 0, 16726, 16723, 16728, 16725, 16722, 16724, 18701, 13098, 7734, 22321, 13397, 12583, 0, 22401};
            Player->EquipForPush(items);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 151:
        {
            // PALADIN - DD - Shockadin
            uint16 items[] = {29969, 25784, 30005, 0, 29789, 29807, 29980, 29786, 30402, 29812, 30339, 25926, 29776, 31617, 25780, 30394, 0, 30227};
            Player->EquipForPush(items);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 16:
        {
            // PALADIN - TANK -ü
            uint16 items[] = {23276,21792,18384,0,15413,14620,14623,14621,21996, 23274,22680, 11669,12930,13515,19888,18396,22336,22401};
            Player->EquipForPush(items);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 17:
        {
            // PALADIN - HEILER -ü
            uint16 items[] = {12633,18723,14548,0,15047,18702,20266,20711,13969,18527,13178, 16058,18472,12930,18389,22380,22336,23201};
            Player->EquipForPush(items);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 18:
        {
            // HUNTER - fertig
            uint16 items[] = {16677, 22340, 16679, 0, 16674, 16680, 16678, 16675, 16681, 16676, 18701, 13098, 7734, 18537, 13397, 13368, 13368, 18680};
            Player->EquipForPush(items);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 19:
        {
            // ROGUE - fertig
            uint16 items[] = {16707, 22340, 16708, 0, 16721, 16713, 16709, 16711, 16710, 16712, 18701, 13098, 7734, 22321, 13397, 22404, 13368, 28972};
            Player->EquipForPush(items);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 20:
        {
            // PRIEST - DD - fertig
            uint16 items[] = {16693, 22403, 16695, 0, 16690, 16696, 16694, 16691, 16697, 16692, 22433, 13345, 7734, 12930, 12968, 22335, 0, 13938};
            Player->EquipForPush(items);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 21:
        {
            // PRIEST - HEILER -ü
            uint16 items[] = {13102,18723,22405,0,13346,18327,18386,12556,18497,12554,22334, 18395,18469,12930,18389,22380,18523,21801};
            Player->EquipForPush(items);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 22:
        {
            // SHAMANE - VERSTÄRKER - fertig
            uint16 items[] = {16667, 22340, 16669, 0, 16666, 16673, 16668, 16670, 16671, 16672, 18701, 13098, 7734, 22321, 13397, 22404, 0, 22395};
            Player->EquipForPush(items);
            Player->AddItem(14487, 1);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 23:
        {
            // SHAMANE - ELEMENTAR -fertig
            uint16 items[] = {16667, 22403, 16669, 0, 16666, 16673, 16668, 16670, 16671, 16672, 22433, 13345, 7734, 12930, 12968, 22335, 0, 22395};
            Player->EquipForPush(items);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 24:
        {
            // SHAMANE - HEILER -ü
            uint16 items[] = {18807,18723,14548,0,15047,18721,14522,18318,13969, 18527,13178, 22334,12930,18471,18389,22380,22336,23200};
            Player->EquipForPush(items);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 25:
        {
            // MAGE -fertig
            uint16 items[] = {16686, 22403, 16689, 0, 16688, 16685, 16687, 16682, 16683, 16684, 22433, 13345, 7734, 12930, 12968, 22335, 0, 13938};
            Player->EquipForPush(items);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 26:
        {
            // WARLOCK -fertig
            uint16 items[] = {16698, 22403, 16701, 0, 16700, 16702, 16699, 16704, 16703, 16705, 22433, 13345, 7734, 12930, 12968, 22335, 0, 13938};
            Player->EquipForPush(items);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 27:
        {
            // DRUID - KATZE -fertig
            uint16 items[] = {16720, 22340, 16718, 0, 16706, 16716, 16719, 16715, 16714, 16717, 18701, 13098, 7734, 22321, 13397, 13372, 0, 22397};
            Player->EquipForPush(items);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 28:
        {
            // DRUID - EULE -ü
            uint16 items[] = {16720, 22403, 16718, 0, 16706, 16716, 16719, 16715, 16714, 16717, 22433, 13345, 7734, 12930, 12968, 22335, 0, 22398};
            Player->EquipForPush(items);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 29:
        {
            // DRUID - BAUM -ü
            uint16 items[] = {17740,18723,15061,0,22272,18391,18682,22275,13208,12547,22334, 18395,18470,12930,18389,22380,18523,22398};
            Player->EquipForPush(items);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 30:
        {
            // DRUID - BÄR -ü
            uint16 items[] = {14539,13091,15058,0,15056,20261,15057,19052,18700,18377,22680, 11669,21784,11810,19888,20556,0,23198};
            Player->EquipForPush(items);
            Player->ADD_GOSSIP_ITEM(0, "Weiter zu den Berufen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
            Player->PlayerTalkClass->SendGossipMenu(30013, Creature->GetGUID());
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 31:
        {
            professions = 0;
            QueryResultAutoPtr result = RealmDataDatabase.PQuery("SELECT guid FROM characters WHERE account in (SELECT account FROM characters WHERE guid = '%u')", GUID_LOPART(Player->GetGUID()));
            Field *fields = NULL;
            uint32 maxchars = 0;

            do
            {
                fields = result->Fetch();
                QueryResultAutoPtr level = RealmDataDatabase.PQuery("SELECT level FROM characters WHERE guid = %u", fields->GetUInt32());
                if (level->Fetch()->GetUInt32() >= 60)
                    maxchars++;
            } while (result->NextRow());
            if (maxchars >= 2)
            {
                Player->ADD_GOSSIP_ITEM(0, "Weiter zum ausbilden :)", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
                Player->PlayerTalkClass->SendGossipMenu(30017, Creature->GetGUID());
                break;
            }
                
            if (Player->HasSkill(SKILL_ALCHEMY))
                professions++;
            if (Player->HasSkill(SKILL_BLACKSMITHING))
                professions++;
            if (Player->HasSkill(SKILL_ENCHANTING))
                professions++;
            if (Player->HasSkill(SKILL_ENGINERING))
                professions++;
            if (Player->HasSkill(SKILL_HERBALISM))
                professions++;
            if (Player->HasSkill(SKILL_JEWELCRAFTING))
                professions++;
            if (Player->HasSkill(SKILL_LEATHERWORKING))
                professions++;
            if (Player->HasSkill(SKILL_MINING))
                professions++;
            if (Player->HasSkill(SKILL_SKINNING))
                professions++;
            if (Player->HasSkill(SKILL_TAILORING))
                professions++;
            if (professions >= 2)
            {
                Player->ADD_GOSSIP_ITEM(0, "Weiter zum ausbilden!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
                Player->PlayerTalkClass->SendGossipMenu(30017, Creature->GetGUID());
            }
            else
            {
                Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Alchemie", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 401);
                Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Bergbauer", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 402);
                Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Ingenieurskunst", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 403);
                Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Juwelenschleifen", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 404);
                Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Kraeutersuche", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 405);
                Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Kuerschnerei", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 406);
                Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Lederverarbeitung", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 407);
                Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Schmiedekunst", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 408);
                Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Schneiderei", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 409);
                Player->ADD_GOSSIP_ITEM(GOSSIP_ICON_TRAINER, "Verzauberungskunst", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 410);
                Player->ADD_GOSSIP_ITEM(0, "Ich will keinen Beruf", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
                Player->PlayerTalkClass->SendGossipMenu(30016, Creature->GetGUID());
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 401: //Alchi
        {
            professions = 0;
            if (Player->HasSkill(SKILL_ALCHEMY))
                professions++;
            if (Player->HasSkill(SKILL_BLACKSMITHING))
                professions++;
            if (Player->HasSkill(SKILL_ENCHANTING))
                professions++;
            if (Player->HasSkill(SKILL_ENGINERING))
                professions++;
            if (Player->HasSkill(SKILL_HERBALISM))
                professions++;
            if (Player->HasSkill(SKILL_JEWELCRAFTING))
                professions++;
            if (Player->HasSkill(SKILL_LEATHERWORKING))
                professions++;
            if (Player->HasSkill(SKILL_MINING))
                professions++;
            if (Player->HasSkill(SKILL_SKINNING))
                professions++;
            if (Player->HasSkill(SKILL_TAILORING))
                professions++;
            if (professions >= 2)
            {
                Player->ADD_GOSSIP_ITEM(0, "Weiter zum ausbilden!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
                Player->PlayerTalkClass->SendGossipMenu(30017, Creature->GetGUID());
            }
            else
            {
                Player->learnSpell(11611);
                Player->SetSkill(171,300,300);
                Player->AddItem(9149, 1);
                Player->AddItem(8925, 20);
                Player->AddItem(18256, 20);
                Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
                Player->PlayerTalkClass->SendGossipMenu(30019, Creature->GetGUID());
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 402: //Bergbau
        {
            professions = 0;
            if (Player->HasSkill(SKILL_ALCHEMY))
                professions++;
            if (Player->HasSkill(SKILL_BLACKSMITHING))
                professions++;
            if (Player->HasSkill(SKILL_ENCHANTING))
                professions++;
            if (Player->HasSkill(SKILL_ENGINERING))
                professions++;
            if (Player->HasSkill(SKILL_HERBALISM))
                professions++;
            if (Player->HasSkill(SKILL_JEWELCRAFTING))
                professions++;
            if (Player->HasSkill(SKILL_LEATHERWORKING))
                professions++;
            if (Player->HasSkill(SKILL_MINING))
                professions++;
            if (Player->HasSkill(SKILL_SKINNING))
                professions++;
            if (Player->HasSkill(SKILL_TAILORING))
                professions++;
            if (professions >= 2)
            {
                Player->ADD_GOSSIP_ITEM(0, "Weiter zum ausbilden!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
                Player->PlayerTalkClass->SendGossipMenu(30017, Creature->GetGUID());
            }
            else
            {
                Player->learnSpell(10248);
                Player->SetSkill(186,300,300);
                Player->AddItem(2901, 1);
                Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
                Player->PlayerTalkClass->SendGossipMenu(30019, Creature->GetGUID());
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 403: //Ingi
        {
            professions = 0;
            if (Player->HasSkill(SKILL_ALCHEMY))
                professions++;
            if (Player->HasSkill(SKILL_BLACKSMITHING))
                professions++;
            if (Player->HasSkill(SKILL_ENCHANTING))
                professions++;
            if (Player->HasSkill(SKILL_ENGINERING))
                professions++;
            if (Player->HasSkill(SKILL_HERBALISM))
                professions++;
            if (Player->HasSkill(SKILL_JEWELCRAFTING))
                professions++;
            if (Player->HasSkill(SKILL_LEATHERWORKING))
                professions++;
            if (Player->HasSkill(SKILL_MINING))
                professions++;
            if (Player->HasSkill(SKILL_SKINNING))
                professions++;
            if (Player->HasSkill(SKILL_TAILORING))
                professions++;
            if (professions >= 2)
            {
                Player->ADD_GOSSIP_ITEM(0, "Weiter zum ausbilden!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
                Player->PlayerTalkClass->SendGossipMenu(30017, Creature->GetGUID());
            }
            else
            {
                Player->learnSpell(12656);
                Player->SetSkill(202,300,300);
                Player->AddItem(6219, 1);
                Player->AddItem(10498, 1);
                professions++;
                Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
                Player->PlayerTalkClass->SendGossipMenu(30019, Creature->GetGUID());
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 404: //Juwe
        {
            professions = 0;
            if (Player->HasSkill(SKILL_ALCHEMY))
                professions++;
            if (Player->HasSkill(SKILL_BLACKSMITHING))
                professions++;
            if (Player->HasSkill(SKILL_ENCHANTING))
                professions++;
            if (Player->HasSkill(SKILL_ENGINERING))
                professions++;
            if (Player->HasSkill(SKILL_HERBALISM))
                professions++;
            if (Player->HasSkill(SKILL_JEWELCRAFTING))
                professions++;
            if (Player->HasSkill(SKILL_LEATHERWORKING))
                professions++;
            if (Player->HasSkill(SKILL_MINING))
                professions++;
            if (Player->HasSkill(SKILL_SKINNING))
                professions++;
            if (Player->HasSkill(SKILL_TAILORING))
                professions++;
            if (professions >= 2)
            {
                Player->ADD_GOSSIP_ITEM(0, "Weiter zum ausbilden!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
                Player->PlayerTalkClass->SendGossipMenu(30017, Creature->GetGUID());
            }
            else
            {
                Player->learnSpell(28895);
                Player->SetSkill(755,300,300);
                Player->AddItem(20815, 1);
                Player->AddItem(20824, 1);
                Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
                Player->PlayerTalkClass->SendGossipMenu(30019, Creature->GetGUID());
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 405: //Kräuter
        {
            professions = 0;
            if (Player->HasSkill(SKILL_ALCHEMY))
                professions++;
            if (Player->HasSkill(SKILL_BLACKSMITHING))
                professions++;
            if (Player->HasSkill(SKILL_ENCHANTING))
                professions++;
            if (Player->HasSkill(SKILL_ENGINERING))
                professions++;
            if (Player->HasSkill(SKILL_HERBALISM))
                professions++;
            if (Player->HasSkill(SKILL_JEWELCRAFTING))
                professions++;
            if (Player->HasSkill(SKILL_LEATHERWORKING))
                professions++;
            if (Player->HasSkill(SKILL_MINING))
                professions++;
            if (Player->HasSkill(SKILL_SKINNING))
                professions++;
            if (Player->HasSkill(SKILL_TAILORING))
                professions++;
            if (professions >= 2)
            {
                Player->ADD_GOSSIP_ITEM(0, "Weiter zum ausbilden!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
                Player->PlayerTalkClass->SendGossipMenu(30017, Creature->GetGUID());
            }
            else
            {
                Player->learnSpell(11993);
                Player->SetSkill(182,300,300);
                Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
                Player->PlayerTalkClass->SendGossipMenu(30019, Creature->GetGUID());
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 406: //Kürschner
        {
            professions = 0;
            if (Player->HasSkill(SKILL_ALCHEMY))
                professions++;
            if (Player->HasSkill(SKILL_BLACKSMITHING))
                professions++;
            if (Player->HasSkill(SKILL_ENCHANTING))
                professions++;
            if (Player->HasSkill(SKILL_ENGINERING))
                professions++;
            if (Player->HasSkill(SKILL_HERBALISM))
                professions++;
            if (Player->HasSkill(SKILL_JEWELCRAFTING))
                professions++;
            if (Player->HasSkill(SKILL_LEATHERWORKING))
                professions++;
            if (Player->HasSkill(SKILL_MINING))
                professions++;
            if (Player->HasSkill(SKILL_SKINNING))
                professions++;
            if (Player->HasSkill(SKILL_TAILORING))
                professions++;
            if (professions >= 2)
            {
                Player->ADD_GOSSIP_ITEM(0, "Weiter zum ausbilden!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
                Player->PlayerTalkClass->SendGossipMenu(30017, Creature->GetGUID());
            }
            else
            {
                Player->learnSpell(10768);
                Player->SetSkill(393,300,300);
                Player->AddItem(7005, 1);
                Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
                Player->PlayerTalkClass->SendGossipMenu(30019, Creature->GetGUID());
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 407: //Leder
        {
            professions = 0;
            if (Player->HasSkill(SKILL_ALCHEMY))
                professions++;
            if (Player->HasSkill(SKILL_BLACKSMITHING))
                professions++;
            if (Player->HasSkill(SKILL_ENCHANTING))
                professions++;
            if (Player->HasSkill(SKILL_ENGINERING))
                professions++;
            if (Player->HasSkill(SKILL_HERBALISM))
                professions++;
            if (Player->HasSkill(SKILL_JEWELCRAFTING))
                professions++;
            if (Player->HasSkill(SKILL_LEATHERWORKING))
                professions++;
            if (Player->HasSkill(SKILL_MINING))
                professions++;
            if (Player->HasSkill(SKILL_SKINNING))
                professions++;
            if (Player->HasSkill(SKILL_TAILORING))
                professions++;
            if (professions >= 2)
            {
                Player->ADD_GOSSIP_ITEM(0, "Weiter zum ausbilden!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
                Player->PlayerTalkClass->SendGossipMenu(30017, Creature->GetGUID());
            }
            else
            {
                Player->learnSpell(10662);
                Player->SetSkill(165,300,300);
                Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
                Player->PlayerTalkClass->SendGossipMenu(30019, Creature->GetGUID());
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 408: //Schmied
        {
            professions = 0;
            if (Player->HasSkill(SKILL_ALCHEMY))
                professions++;
            if (Player->HasSkill(SKILL_BLACKSMITHING))
                professions++;
            if (Player->HasSkill(SKILL_ENCHANTING))
                professions++;
            if (Player->HasSkill(SKILL_ENGINERING))
                professions++;
            if (Player->HasSkill(SKILL_HERBALISM))
                professions++;
            if (Player->HasSkill(SKILL_JEWELCRAFTING))
                professions++;
            if (Player->HasSkill(SKILL_LEATHERWORKING))
                professions++;
            if (Player->HasSkill(SKILL_MINING))
                professions++;
            if (Player->HasSkill(SKILL_SKINNING))
                professions++;
            if (Player->HasSkill(SKILL_TAILORING))
                professions++;
            if (professions >= 2)
            {
                Player->ADD_GOSSIP_ITEM(0, "Weiter zum ausbilden!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
                Player->PlayerTalkClass->SendGossipMenu(30017, Creature->GetGUID());
            }
            else
            {
                Player->learnSpell(9785);
                Player->SetSkill(164,300,300);
                Player->AddItem(5956, 1);
                Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
                Player->PlayerTalkClass->SendGossipMenu(30019, Creature->GetGUID());
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 409: //Schneider
        {
            professions = 0;
            if (Player->HasSkill(SKILL_ALCHEMY))
                professions++;
            if (Player->HasSkill(SKILL_BLACKSMITHING))
                professions++;
            if (Player->HasSkill(SKILL_ENCHANTING))
                professions++;
            if (Player->HasSkill(SKILL_ENGINERING))
                professions++;
            if (Player->HasSkill(SKILL_HERBALISM))
                professions++;
            if (Player->HasSkill(SKILL_JEWELCRAFTING))
                professions++;
            if (Player->HasSkill(SKILL_LEATHERWORKING))
                professions++;
            if (Player->HasSkill(SKILL_MINING))
                professions++;
            if (Player->HasSkill(SKILL_SKINNING))
                professions++;
            if (Player->HasSkill(SKILL_TAILORING))
                professions++;
            if (professions >= 2)
            {
                Player->ADD_GOSSIP_ITEM(0, "Weiter zum ausbilden!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
                Player->PlayerTalkClass->SendGossipMenu(30017, Creature->GetGUID());
            }
            else
            {
                Player->learnSpell(12180);
                Player->SetSkill(197,300,300);
                Player->AddItem(14341, 20);
                Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
                Player->PlayerTalkClass->SendGossipMenu(30019, Creature->GetGUID());
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 410: //VZ
        {
            professions = 0;
            if (Player->HasSkill(SKILL_ALCHEMY))
                professions++;
            if (Player->HasSkill(SKILL_BLACKSMITHING))
                professions++;
            if (Player->HasSkill(SKILL_ENCHANTING))
                professions++;
            if (Player->HasSkill(SKILL_ENGINERING))
                professions++;
            if (Player->HasSkill(SKILL_HERBALISM))
                professions++;
            if (Player->HasSkill(SKILL_JEWELCRAFTING))
                professions++;
            if (Player->HasSkill(SKILL_LEATHERWORKING))
                professions++;
            if (Player->HasSkill(SKILL_MINING))
                professions++;
            if (Player->HasSkill(SKILL_SKINNING))
                professions++;
            if (Player->HasSkill(SKILL_TAILORING))
                professions++;
            if (professions >= 2)
            {
                Player->ADD_GOSSIP_ITEM(0, "Weiter zum ausbilden!", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 40);
                Player->PlayerTalkClass->SendGossipMenu(30017, Creature->GetGUID());
            }
            else
            {
                Player->learnSpell(13920);
                Player->SetSkill(333,300,300);
                Player->AddItem(22461, 1);
                Player->ADD_GOSSIP_ITEM(0, "Weiter", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
                Player->PlayerTalkClass->SendGossipMenu(30019, Creature->GetGUID());
            }
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 40:
        {
            Player->FinishPush();
            return true;
        }
        default:
            return false;
    }
    return true;
}

void AddSC_custom_gossip_codebox() {

    Script *newscript;
    newscript = new Script;
    newscript->Name = "custom_gossip_codebox";
    newscript->pGossipHello = &GossipHello_custom_gossip_codebox;
    newscript->pGossipSelect = &GossipSelect_custom_gossip_codebox;
    newscript->RegisterSelf();
}
