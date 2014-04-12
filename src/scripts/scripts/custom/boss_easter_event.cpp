/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* ScriptData
SDName: boss_easter_event
SD%Complete: 0%
SDComment: Basic structure with example
SDCategory: custom
EndScriptData */

#include "precompiled.h"

#define SAY_AGGRO                   -1000387

#define SPELL_EARTHQUAKE            32686

struct boss_easter_eventAI : public ScriptedAI
{
    boss_easter_eventAI(Creature *c) : ScriptedAI(c)
    {        
    }

    uint32 Chain_Timer;

    void Reset()
    {
        Chain_Timer     = 10000 + rand()%20000;
    }

    void KilledUnit(Unit* victim)
    {
        DoScriptText(RAND(SAY_AGGRO, SAY_AGGRO, SAY_AGGRO), m_creature);
    }

    void JustDied(Unit* Killer)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void EnterCombat(Unit *who)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void MoveInLineOfSight(Unit* who)
    {
        
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;


        //Spell Chain Lightning
        if (Chain_Timer < diff)
        {
            Unit* target = NULL;
            target = SelectUnit(SELECT_TARGET_RANDOM,1, GetSpellMaxRange(SPELL_EARTHQUAKE), true, m_creature->getVictimGUID());

            if (!target)
                target = m_creature->getVictim();

            if (target)
                DoCast(target,SPELL_EARTHQUAKE);

            Chain_Timer = 10000 + rand()%25000;
        }else Chain_Timer -= diff;


        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_easter_event(Creature *_Creature)
{
    return new boss_easter_eventAI (_Creature);
}

void AddSC_boss_doomwalker()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_easter_event";
    newscript->GetAI = &GetAI_boss_easter_event;
    newscript->RegisterSelf();
}
