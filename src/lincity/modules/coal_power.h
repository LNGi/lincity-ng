#define GROUP_COAL_POWER_COLOUR 0
#define GROUP_COAL_POWER_COST   100000
#define GROUP_COAL_POWER_COST_MUL 5
#define GROUP_COAL_POWER_BUL_COST   200000
#define GROUP_COAL_POWER_TECH   200
#define GROUP_COAL_POWER_FIREC  80
#define GROUP_COAL_POWER_RANGE  0
#define GROUP_COAL_POWER_SIZE  4

#define POWERS_COAL_OUTPUT 11000 //x2 for kWh
#define MAX_MWH_AT_COALPS (20 * POWERS_COAL_OUTPUT)
#define POWER_PER_COAL 250
#define MAX_COAL_AT_COALPS (20 * POWERS_COAL_OUTPUT / POWER_PER_COAL)
#define POWERS_COAL_POLLUTION  20
#define JOBS_COALPS_GENERATE 100
#define MAX_JOBS_AT_COALPS (20 * JOBS_COALPS_GENERATE)
#define SMOKE_ANIM_SPEED 300


#include "modules.h"
#include "../lintypes.h"
#include "../lctypes.h"


class Coal_powerConstructionGroup: public ConstructionGroup {
public:
    Coal_powerConstructionGroup(
        const char *name,
        unsigned short no_credit,
        unsigned short group,
        unsigned short size, int colour,
        int cost_mul, int bul_cost, int fire_chance,
        int cost, int tech, int range
    ): ConstructionGroup(
        name, no_credit, group, size, colour, cost_mul, bul_cost, fire_chance, cost, tech, range
    ) {
        commodityRuleCount[Construction::STUFF_JOBS].maxload = MAX_JOBS_AT_COALPS;
        commodityRuleCount[Construction::STUFF_JOBS].take = true;
        commodityRuleCount[Construction::STUFF_JOBS].give = false;
        commodityRuleCount[Construction::STUFF_COAL].maxload = MAX_COAL_AT_COALPS;
        commodityRuleCount[Construction::STUFF_COAL].take = true;
        commodityRuleCount[Construction::STUFF_COAL].give = false;
        commodityRuleCount[Construction::STUFF_MWH].maxload = MAX_MWH_AT_COALPS;
        commodityRuleCount[Construction::STUFF_MWH].take = false;
        commodityRuleCount[Construction::STUFF_MWH].give = true;
    }
    // overriding method that creates a Coal_power
    virtual Construction *createConstruction(int x, int y);
};

extern Coal_powerConstructionGroup coal_powerConstructionGroup;
//extern Coal_powerConstructionGroup coal_power_low_ConstructionGroup;
//extern Coal_powerConstructionGroup coal_power_med_ConstructionGroup;
//extern Coal_powerConstructionGroup coal_power_full_ConstructionGroup;


class Coal_power: public RegisteredConstruction<Coal_power> { // Coal_power inherits from its own RegisteredConstruction
public:
    Coal_power(int x, int y, ConstructionGroup *cstgrp): RegisteredConstruction<Coal_power>(x, y)
    {
        this->constructionGroup = cstgrp;
        frames.resize(8);
        for (size_t i = 0; i < frames.size(); ++i)
        {   frames[i].resourceGroup = ResourceGroup::resMap["PowerCoalEmpty"];}
        frames[0].move_x = 5;
        frames[0].move_y = -378;
        frames[1].move_x = 29;
        frames[1].move_y = -390;
        frames[2].move_x = 52;
        frames[2].move_y = -397;
        frames[3].move_x = 76;
        frames[3].move_y = -409;
        frames[4].move_x = 65;
        frames[4].move_y = -348;
        frames[5].move_x = 89;
        frames[5].move_y = -360;
        frames[6].move_x = 112;
        frames[6].move_y = -371;
        frames[7].move_x = 136;
        frames[7].move_y = -383;
        this->anim = 0;
        this->animate = false;
        this->tech = tech_level;
        setMemberSaved(&this->tech, "tech");
        this->working_days = 0;
        this->busy = 0;
        this->mwh_output = (int)(POWERS_COAL_OUTPUT + (((double)tech_level * POWERS_COAL_OUTPUT) / MAX_TECH_LEVEL));
        setMemberSaved(&this->mwh_output, "mwh_output");
        initialize_commodities();
    }
    virtual ~Coal_power() {}
    virtual void update();
    virtual void report();

    int anim;
    bool animate;
    int  mwh_output;
    int  tech;
    int  working_days, busy;
};


/** @file lincity/modules/coal_power.h */

