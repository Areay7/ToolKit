#pragma once

#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>
#include <queue>
#include <set>
#include <string>

#include <stdio.h>
#include <iostream>

namespace tool::qps
{

class QpsCalc
{
public:
    QpsCalc(const std::string& identifier, uint32_t print_interval, uint32_t stat_period);
    ~QpsCalc() = default;

    void Tick(uint64_t cost_time, bool success);
    double Qps() { return m_qps.load(std::memory_order_relaxed); }
    double AvgTime() { return m_avg_time.load(std::memory_order_relaxed); }
    uint64_t PeakTime() { return m_peak_time.load(std::memory_order_relaxed); }
    uint64_t ValleyTime() { return m_valley_time.load(std::memory_order_relaxed); }
    double SuccessRate() { return m_success_rate.load(std::memory_order_relaxed); }
    int32_t Count() { return m_count.load(std::memory_order_relaxed); }

private:
    std::string m_identifier;
    uint32_t m_print_interval = 60000;
    uint32_t m_stat_period = 60000;
    uint64_t m_last_print_time = 0;
    std::mutex m_tick_lock;
    std::queue<std::tuple<uint64_t, uint64_t, bool>> m_ticks;
    std::set<std::pair<uint64_t, uint64_t>> m_tick_order;
    uint64_t m_sum_cost_time = 0;
    uint64_t m_sum_success_count = 0;
    std::atomic<double> m_qps{0};
    std::atomic<double> m_avg_time{0};
    std::atomic<uint64_t> m_peak_time{0};
    std::atomic<uint64_t> m_valley_time{0};
    std::atomic<double> m_success_rate{0};
    std::atomic<int32_t> m_count{0};
};

using QpsCalcPtr = std::shared_ptr<QpsCalc>;

class QpsTick
{
public:
    QpsTick(QpsCalc* calc);
    void Tick(bool success);
    ~QpsTick();

private:
    bool m_success = true;
    uint64_t m_begin_time;
    QpsCalc* m_calc = nullptr;
};

}  // namespace fsp::sss::rule
