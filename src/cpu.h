#ifndef __CPU_H
#define __CPU_H

#include <fstream>
#include <vector>
#include "controller.h"
#include "common.h"
#include "config.h"


class Access {
    public:
        uint64_t hex_addr_;
        std::string access_type_;
        long time_;
        friend std::istream& operator>>(std::istream& is, Access& access);
        friend std::ostream& operator<<(std::ostream& os, const Access& access);
};


int LogBase2(int power_of_two);
Address AddressMapping(uint64_t hex_addr, const Config& config);


class RandomCPU {
    RandomCPU();
};

class TraceBasedCPU {
    public:
        TraceBasedCPU(std::vector<Controller*>& ctrls, const Config& config);
        void ClockTick();
    private:
        std::vector<Controller*>& ctrls_;
        const Config& config_;
        long clk;
        std::ifstream trace_file_;
        Request* req_;
        bool get_next_ = true;
        int req_id_ = 0;

        int channel_width_, rank_width_, bankgroup_width_, bank_width_, row_width_, column_width_;

        Request* FormRequest(const Access& access);
};

#endif