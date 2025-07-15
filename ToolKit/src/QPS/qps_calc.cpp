#include "qps_calc.h"


#include <ctime>

// #include "global_objects.h"

namespace tool::qps
{

QpsCalc::QpsCalc(const std::string& identifier, uint32_t print_interval, uint32_t stat_period)
    : m_identifier(identifier)
    , m_print_interval(print_interval)
    , m_stat_period(stat_period)
{
    m_last_print_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
}

void QpsCalc::Tick(uint64_t cost_time, bool success)
{
    auto cur_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();

    std::lock_guard<std::mutex> lock_guard(m_tick_lock);
    m_ticks.emplace(cost_time, cur_time, success);
    m_tick_order.emplace(cost_time, cur_time);
    m_sum_cost_time += cost_time;
    m_sum_success_count += success;

    auto outdate_time = cur_time - (uint64_t)m_stat_period;
    while (!m_ticks.empty())
    {
        auto tick_time = std::get<1>(m_ticks.front());
        if (tick_time < outdate_time)
        {
            auto cost_time = std::get<0>(m_ticks.front());
            m_sum_cost_time -= cost_time;
            m_sum_success_count -= std::get<2>(m_ticks.front());
            m_tick_order.erase(std::make_pair(cost_time, tick_time));
            m_ticks.pop();
        }
        else
        {
            break;
        }
    }

    auto real_print_interval = cur_time - m_last_print_time;
    if (real_print_interval >= m_print_interval)
    {
        auto qps = m_ticks.size() * 1000.0 / m_stat_period;
        auto avg_time = m_sum_cost_time * 1.0 / m_ticks.size();
        auto peak_time = m_tick_order.rbegin()->first;
        auto valley_time = m_tick_order.begin()->first;
        auto success_rate = m_sum_success_count * 100.0 / m_ticks.size();
        printf("%s, qps = %.2lf/s, avg_time = %.2lf ms, peak_time = %lu ms, valley_time = %lu ms, "
             "success_rate = %.2lf%%, count = %d. \n",
             m_identifier.data(), qps, avg_time, peak_time, valley_time, success_rate, m_ticks.size());
        m_last_print_time = cur_time;
        m_qps.store(qps, std::memory_order_relaxed);
        m_avg_time.store(avg_time, std::memory_order_relaxed);
        m_peak_time.store(peak_time, std::memory_order_relaxed);
        m_valley_time.store(valley_time, std::memory_order_relaxed);
        m_success_rate.store(success_rate, std::memory_order_relaxed);
        m_count.store(m_ticks.size(), std::memory_order_relaxed);
    }
}

QpsTick::QpsTick(QpsCalc* calc)
    : m_calc(calc)
{
    m_begin_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
}

QpsTick::~QpsTick()
{
    auto cur_time =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();
    m_calc->Tick(cur_time - m_begin_time, m_success);
}

void QpsTick::Tick(bool success)
{
    m_success = success;
}

}  // namespace fsp::sss::rule
