#ifndef TEST_REGION_H
#define TEST_REGION_H

#include "world/region.h"

class TestRegion : public Region{
    public:
        TestRegion();
        void load() override;
        void unload() override;
        Scene* getScene(std::string name) override;
};
#endif