/* Copyright (C) 2010-2013 OpenEmulator <http://www.openemulator.com/>
*
* This file is free software; as a special exception the author gives
* unlimited permission to copy and/or distribute it, with or without
* modifications, as long as this notice is preserved.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum MonkSpells
{
    SPELL_MONK_LEGACY_OF_THE_EMPEROR            = 117667,
    SPELL_MONK_FORTIFYING_BREW                  = 120954,
    SPELL_MONK_PROVOKE                          = 118635,
    SPELL_MONK_BLACKOUT_KICK_DOT                = 128531,
    SPELL_MONK_BLACKOUT_KICK_HEAL               = 128591,
    SPELL_MONK_SHUFFLE                          = 115307,
    SPELL_MONK_ZEN_PILGRIMAGE                   = 126892,
    SPELL_MONK_ZEN_PILGRIMAGE_RETURN            = 126895,
    SPELL_MONK_DISABLE_ROOT                     = 116706,
    SPELL_MONK_DISABLE                          = 116095,
    SPELL_MONK_SOOTHING_MIST_VISUAL             = 125955,
    SPELL_MONK_SOOTHING_MIST_ENERGIZE           = 116335,
    SPELL_MONK_BREATH_OF_FIRE_DOT               = 123725,
    SPELL_MONK_BREATH_OF_FIRE_CONFUSED          = 123393,
    SPELL_MONK_ELUSIVE_BREW_STACKS              = 128939,
    SPELL_MONK_ELUSIVE_BREW                     = 115308,
    SPELL_MONK_KEG_SMASH_VISUAL                 = 123662,
    SPELL_MONK_KEG_SMASH_ENERGIZE               = 127796,
    SPELL_MONK_WEAKENED_BLOWS                   = 115798,
    SPELL_MONK_DIZZYING_HAZE                    = 116330,
    SPELL_MONK_CLASH_CHARGE                     = 126452,
    SPELL_MONK_LIGHT_STAGGER                    = 124275,
    SPELL_MONK_MODERATE_STAGGER                 = 124274,
    SPELL_MONK_HEAVY_STAGGER                    = 124273,
    SPELL_MONK_ROLL                             = 109132,
    SPELL_MONK_ROLL_TRIGGER                     = 107427,
    SPELL_MONK_CHI_TORPEDO_HEAL                 = 124040,
    SPELL_MONK_CHI_TORPEDO_DAMAGE               = 117993,
    SPELL_MONK_FLYING_SERPENT_KICK              = 101545,
    SPELL_MONK_FLYING_SERPENT_KICK_NEW          = 115057,
    SPELL_MONK_FLYING_SERPENT_KICK_AOE          = 123586,
    SPELL_MONK_TIGEREYE_BREW                    = 116740,
    SPELL_MONK_TIGEREYE_BREW_STACKS             = 125195,
    SPELL_MONK_SPEAR_HAND_STRIKE_SILENCE        = 116709,
    SPELL_MONK_CHI_BURST_DAMAGE                 = 130651,
    SPELL_MONK_CHI_BURST_HEAL                   = 130654,
    SPELL_MONK_ZEN_SPHERE_DAMAGE                = 124098,
    SPELL_MONK_ZEN_SPHERE_HEAL                  = 124081,
    SPELL_MONK_ZEN_SPHERE_DETONATE_HEAL         = 124101,
    SPELL_MONK_ZEN_SPHERE_DETONATE_DAMAGE       = 125033,
    SPELL_MONK_HEALING_ELIXIRS_AURA             = 122280,
    SPELL_MONK_HEALING_ELIXIRS_RESTORE_HEALTH   = 122281,
    SPELL_MONK_RENEWING_MIST_HOT                = 119611,
    SPELL_MONK_RENEWING_MIST_JUMP_AURA          = 119607,
    SPELL_MONK_GLYPH_OF_RENEWING_MIST           = 123334,
    SPELL_MONK_SURGING_MIST_HEAL                = 116995,
    SPELL_MONK_ENVELOPING_MIST_HEAL             = 132120,
    SPELL_MONK_PLUS_ONE_MANA_TEA                = 123760,
    SPELL_MONK_MANA_TEA_STACKS                  = 115867,
    SPELL_MONK_MANA_TEA_REGEN                   = 115294,
    SPELL_MONK_SPINNING_CRANE_KICK_HEAL         = 117640,
    MONK_NPC_JADE_SERPENT_STATUE                = 60849,
    SPELL_MONK_UPLIFT_ALLOWING_CAST             = 123757,
    SPELL_MONK_THUNDER_FOCUS_TEA                = 116680,
    SPELL_MONK_PATH_OF_BLOSSOM_AREATRIGGER      = 122035,
    SPELL_MONK_SPINNING_FIRE_BLOSSOM_DAMAGE     = 123408,
    SPELL_MONK_SPINNING_FIRE_BLOSSOM_MISSILE    = 118852,
    SPELL_MONK_SPINNING_FIRE_BLOSSOM_ROOT       = 123407,
    SPELL_MONK_TOUCH_OF_KARMA_REDIRECT_DAMAGE   = 124280,
    SPELL_MONK_JADE_LIGHTNING_ENERGIZE          = 123333,
    SPELL_MONK_CRACKLING_JADE_SHOCK_BUMP        = 117962,
    SPELL_MONK_POWER_STRIKES_TALENT             = 121817,
    SPELL_MONK_CREATE_CHI_SPHERE                = 121286,
    SPELL_MONK_GLYPH_OF_ZEN_FLIGHT              = 125893,
    SPELL_MONK_ZEN_FLIGHT                       = 125883,
    SPELL_MONK_BEAR_HUG                         = 127361,
    ITEM_MONK_T14_TANK_4P                       = 123159,
    MONK_NPC_BLACK_OX_STATUE                    = 61146,
    SPELL_MONK_GUARD                            = 115295,
    SPELL_MONK_ITEM_2_S12_MISTWEAVER            = 131561,
    SPELL_MONK_ITEM_4_S12_MISTWEAVER            = 124487,
    SPELL_MONK_ZEN_FOCUS                        = 124488,
    SPELL_MONK_EMINENCE_HEAL                    = 126890,
    SPELL_MONK_GRAPPLE_WEAPON_DPS_UPGRADE       = 123231,
    SPELL_MONK_GRAPPLE_WEAPON_TANK_UPGRADE      = 123232,
    SPELL_MONK_GRAPPLE_WEAPON_HEAL_UPGRADE      = 123234,
    SPELL_MONK_GLYPH_OF_BLACKOUT_KICK           = 132005,
    SPELL_MONK_CHI_WAVE_HEAL                    = 132463,
    SPELL_MONK_CHI_WAVE_DAMAGE                  = 132467,
    SPELL_MONK_CHI_WAVE_HEALING_BOLT            = 132464,
    SPELL_MONK_CHI_WAVE_TALENT_AURA             = 115098,
    SPELL_MONK_ITEM_PVP_GLOVES_BONUS            = 124489,
};


