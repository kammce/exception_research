
    #include <array>
    #include <cstddef>
    #include <cstdint>
    #include <cstdlib>
    #include <exception>
    #include <span>
    #include <string_view>

    volatile std::int32_t side_effect = 0;
    std::uint32_t start_cycles = 0;
    std::uint32_t end_cycles = 0;

    /// Structure type to access the Data Watch point and Trace Register (DWT).
    struct dwt_register_t
    {
    /// Offset: 0x000 (R/W)  Control Register
    volatile uint32_t ctrl;
    /// Offset: 0x004 (R/W)  Cycle Count Register
    volatile uint32_t cyccnt;
    /// Offset: 0x008 (R/W)  CPI Count Register
    volatile uint32_t cpicnt;
    /// Offset: 0x00C (R/W)  Exception Overhead Count Register
    volatile uint32_t exccnt;
    /// Offset: 0x010 (R/W)  Sleep Count Register
    volatile uint32_t sleepcnt;
    /// Offset: 0x014 (R/W)  LSU Count Register
    volatile uint32_t lsucnt;
    /// Offset: 0x018 (R/W)  Folded-instruction Count Register
    volatile uint32_t foldcnt;
    /// Offset: 0x01C (R/ )  Program Counter Sample Register
    volatile const uint32_t pcsr;
    /// Offset: 0x020 (R/W)  Comparator Register 0
    volatile uint32_t comp0;
    /// Offset: 0x024 (R/W)  Mask Register 0
    volatile uint32_t mask0;
    /// Offset: 0x028 (R/W)  Function Register 0
    volatile uint32_t function0;
    /// Reserved 0
    std::array<uint32_t, 1> reserved0;
    /// Offset: 0x030 (R/W)  Comparator Register 1
    volatile uint32_t comp1;
    /// Offset: 0x034 (R/W)  Mask Register 1
    volatile uint32_t mask1;
    /// Offset: 0x038 (R/W)  Function Register 1
    volatile uint32_t function1;
    /// Reserved 1
    std::array<uint32_t, 1> reserved1;
    /// Offset: 0x040 (R/W)  Comparator Register 2
    volatile uint32_t comp2;
    /// Offset: 0x044 (R/W)  Mask Register 2
    volatile uint32_t mask2;
    /// Offset: 0x048 (R/W)  Function Register 2
    volatile uint32_t function2;
    /// Reserved 2
    std::array<uint32_t, 1> reserved2;
    /// Offset: 0x050 (R/W)  Comparator Register 3
    volatile uint32_t comp3;
    /// Offset: 0x054 (R/W)  Mask Register 3
    volatile uint32_t mask3;
    /// Offset: 0x058 (R/W)  Function Register 3
    volatile uint32_t function3;
    };

    /// Structure type to access the Core Debug Register (CoreDebug)
    struct core_debug_registers_t
    {
    /// Offset: 0x000 (R/W)  Debug Halting Control and Status Register
    volatile uint32_t dhcsr;
    /// Offset: 0x004 ( /W)  Debug Core Register Selector Register
    volatile uint32_t dcrsr;
    /// Offset: 0x008 (R/W)  Debug Core Register Data Register
    volatile uint32_t dcrdr;
    /// Offset: 0x00C (R/W)  Debug Exception and Monitor Control Register
    volatile uint32_t demcr;
    };

    /// Address of the hardware DWT registers
    constexpr intptr_t dwt_address = 0xE0001000UL;

    /// Address of the Cortex M CoreDebug module
    constexpr intptr_t core_debug_address = 0xE000EDF0UL;

    // NOLINTNEXTLINE
    auto* dwt = reinterpret_cast<dwt_register_t*>(dwt_address);

    // NOLINTNEXTLINE
    auto* core = reinterpret_cast<core_debug_registers_t*>(core_debug_address);

    void
    dwt_counter_enable()
    {
    /**
    * @brief This bit must be set to 1 to enable use of the trace and debug
    * blocks:
    *
    *   - Data Watchpoint and Trace (DWT)
    *   - Instrumentation Trace Macrocell (ITM)
    *   - Embedded Trace Macrocell (ETM)
    *   - Trace Port Interface Unit (TPIU).
    */
    constexpr unsigned core_trace_enable = 1 << 24U;

    /// Mask for turning on cycle counter.
    constexpr unsigned enable_cycle_count = 1 << 0;

    // Enable trace core
    core->demcr = (core->demcr | core_trace_enable);

    // Reset cycle count
    dwt->cyccnt = 0;

    // Start cycle count
    dwt->ctrl = (dwt->ctrl | enable_cycle_count);
    }

    std::uint32_t
    uptime()
    {
    return dwt->cyccnt;
    }
    

        #include <tl/expected.hpp>
        struct my_error_t
        {
            std::array<std::uint8_t, 4> data;
        };
        

    tl::expected<int, my_error_t> start();
    int main()
    {
        dwt_counter_enable();
        volatile int return_code = 0;
        auto result = start();
        if (!result) {
            return_code = result.error().data[0];
        } else {
            return_code = result.value();
        }
        while(true) {
            continue;
        }
        return return_code;
    }
    

        std::array<std::uint64_t, 25> cycle_map{};
        

        tl::expected<int, my_error_t> funct_group0_0();
tl::expected<int, my_error_t> funct_group1_0();
tl::expected<int, my_error_t> funct_group2_0();
tl::expected<int, my_error_t> funct_group3_0();
tl::expected<int, my_error_t> funct_group4_0();
tl::expected<int, my_error_t> funct_group5_0();
tl::expected<int, my_error_t> funct_group6_0();
tl::expected<int, my_error_t> funct_group7_0();
tl::expected<int, my_error_t> funct_group8_0();
tl::expected<int, my_error_t> funct_group9_0();
tl::expected<int, my_error_t> funct_group10_0();
tl::expected<int, my_error_t> funct_group11_0();
tl::expected<int, my_error_t> funct_group12_0();
tl::expected<int, my_error_t> funct_group13_0();
tl::expected<int, my_error_t> funct_group14_0();
tl::expected<int, my_error_t> funct_group15_0();
tl::expected<int, my_error_t> funct_group16_0();
tl::expected<int, my_error_t> funct_group17_0();
tl::expected<int, my_error_t> funct_group18_0();
tl::expected<int, my_error_t> funct_group19_0();
tl::expected<int, my_error_t> funct_group20_0();
tl::expected<int, my_error_t> funct_group21_0();
tl::expected<int, my_error_t> funct_group22_0();
tl::expected<int, my_error_t> funct_group23_0();
tl::expected<int, my_error_t> funct_group24_0();
        tl::expected<int, my_error_t> start() {
            
        start_cycles = uptime();
        if (auto result = funct_group0_0(); !result) {
            end_cycles = uptime();
            cycle_map[0] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group1_0(); !result) {
            end_cycles = uptime();
            cycle_map[1] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group2_0(); !result) {
            end_cycles = uptime();
            cycle_map[2] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group3_0(); !result) {
            end_cycles = uptime();
            cycle_map[3] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group4_0(); !result) {
            end_cycles = uptime();
            cycle_map[4] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group5_0(); !result) {
            end_cycles = uptime();
            cycle_map[5] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group6_0(); !result) {
            end_cycles = uptime();
            cycle_map[6] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group7_0(); !result) {
            end_cycles = uptime();
            cycle_map[7] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group8_0(); !result) {
            end_cycles = uptime();
            cycle_map[8] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group9_0(); !result) {
            end_cycles = uptime();
            cycle_map[9] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group10_0(); !result) {
            end_cycles = uptime();
            cycle_map[10] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group11_0(); !result) {
            end_cycles = uptime();
            cycle_map[11] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group12_0(); !result) {
            end_cycles = uptime();
            cycle_map[12] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group13_0(); !result) {
            end_cycles = uptime();
            cycle_map[13] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group14_0(); !result) {
            end_cycles = uptime();
            cycle_map[14] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group15_0(); !result) {
            end_cycles = uptime();
            cycle_map[15] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group16_0(); !result) {
            end_cycles = uptime();
            cycle_map[16] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group17_0(); !result) {
            end_cycles = uptime();
            cycle_map[17] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group18_0(); !result) {
            end_cycles = uptime();
            cycle_map[18] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group19_0(); !result) {
            end_cycles = uptime();
            cycle_map[19] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group20_0(); !result) {
            end_cycles = uptime();
            cycle_map[20] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group21_0(); !result) {
            end_cycles = uptime();
            cycle_map[21] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group22_0(); !result) {
            end_cycles = uptime();
            cycle_map[22] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group23_0(); !result) {
            end_cycles = uptime();
            cycle_map[23] = end_cycles - start_cycles;
        }
        

        start_cycles = uptime();
        if (auto result = funct_group24_0(); !result) {
            end_cycles = uptime();
            cycle_map[24] = end_cycles - start_cycles;
        }
        
            return side_effect;
        }
        
class class_0 { public:
        static tl::expected<class_0, my_error_t> make(std::int32_t p_channel)
        {
            if (p_channel >= 1'000'000'000) {
                return tl::unexpected(
                    my_error_t{ .data = { 0x55, 0xAA, 0x33, 0x44 } }
                );
            }
            side_effect = side_effect + 1;
            return class_0(p_channel);
        }
        
        class_0(class_0&) = delete;
        class_0& operator=(class_0&) = delete;
        class_0(class_0&&) noexcept = default;
        class_0& operator=(class_0&&) noexcept = default;
        ~class_0() = default;
        tl::expected<void, my_error_t> trigger()
        {
            if (m_channel >= 1'000'000'000) {
                return tl::unexpected(
                    my_error_t{ .data = { 0xAA, 0xBB, 0x33, 0x44 } }
                );
            }
            side_effect = side_effect + 1;

            return {};
        }
        
        private:
        class_0(std::int32_t p_channel)
            : m_channel(p_channel)
        {
        }
        
            std::int32_t m_channel = 0;
        };
        
class class_1 { public:
        static tl::expected<class_1, my_error_t> make(std::int32_t p_channel)
        {
            if (p_channel >= 1'000'000'000) {
                return tl::unexpected(
                    my_error_t{ .data = { 0x55, 0xAA, 0x33, 0x44 } }
                );
            }
            side_effect = side_effect + 1;
            return class_1(p_channel);
        }
        
        class_1(class_1&) = delete;
        class_1& operator=(class_1&) = delete;
        class_1(class_1&&) noexcept = default;
        class_1& operator=(class_1&&) noexcept = default;
        ~class_1()
            {
                side_effect = side_effect & ~(1 << m_channel);
            }
            
        tl::expected<void, my_error_t> trigger()
        {
            if (m_channel >= 1'000'000'000) {
                return tl::unexpected(
                    my_error_t{ .data = { 0xAA, 0xBB, 0x33, 0x44 } }
                );
            }
            side_effect = side_effect + 1;

            return {};
        }
        
        private:
        class_1(std::int32_t p_channel)
            : m_channel(p_channel)
        {
        }
        
            std::int32_t m_channel = 0;
        };
        

            tl::expected<int, my_error_t> funct_group0_1(); 

            
        tl::expected<int, my_error_t> funct_group0_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group0_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group0_2(); 

            
        tl::expected<int, my_error_t> funct_group0_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group0_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group0_3(); 

            
        tl::expected<int, my_error_t> funct_group0_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group0_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group0_4(); 

            
        tl::expected<int, my_error_t> funct_group0_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group0_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group0_5(); 

            
        tl::expected<int, my_error_t> funct_group0_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group0_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group0_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group1_1(); 

            
        tl::expected<int, my_error_t> funct_group1_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group1_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group1_2(); 

            
        tl::expected<int, my_error_t> funct_group1_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group1_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group1_3(); 

            
        tl::expected<int, my_error_t> funct_group1_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group1_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group1_4(); 

            
        tl::expected<int, my_error_t> funct_group1_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group1_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group1_5(); 

            
        tl::expected<int, my_error_t> funct_group1_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group1_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group1_6(); 

            
        tl::expected<int, my_error_t> funct_group1_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group1_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group1_7(); 

            
        tl::expected<int, my_error_t> funct_group1_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group1_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group1_8(); 

            
        tl::expected<int, my_error_t> funct_group1_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group1_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group1_9(); 

            
        tl::expected<int, my_error_t> funct_group1_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group1_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group1_10(); 

            
        tl::expected<int, my_error_t> funct_group1_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group1_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group1_11(); 

            
        tl::expected<int, my_error_t> funct_group1_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group1_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group1_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_1(); 

            
        tl::expected<int, my_error_t> funct_group2_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_2(); 

            
        tl::expected<int, my_error_t> funct_group2_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_3(); 

            
        tl::expected<int, my_error_t> funct_group2_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_4(); 

            
        tl::expected<int, my_error_t> funct_group2_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_5(); 

            
        tl::expected<int, my_error_t> funct_group2_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_6(); 

            
        tl::expected<int, my_error_t> funct_group2_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_7(); 

            
        tl::expected<int, my_error_t> funct_group2_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_8(); 

            
        tl::expected<int, my_error_t> funct_group2_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_9(); 

            
        tl::expected<int, my_error_t> funct_group2_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_10(); 

            
        tl::expected<int, my_error_t> funct_group2_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_11(); 

            
        tl::expected<int, my_error_t> funct_group2_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_12(); 

            
        tl::expected<int, my_error_t> funct_group2_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_12(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_13(); 

            
        tl::expected<int, my_error_t> funct_group2_12()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_13(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_14(); 

            
        tl::expected<int, my_error_t> funct_group2_13()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_14(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_15(); 

            
        tl::expected<int, my_error_t> funct_group2_14()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_15(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_16(); 

            
        tl::expected<int, my_error_t> funct_group2_15()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_16(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_17(); 

            
        tl::expected<int, my_error_t> funct_group2_16()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_17(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_18(); 

            
        tl::expected<int, my_error_t> funct_group2_17()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_18(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_19(); 

            
        tl::expected<int, my_error_t> funct_group2_18()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_19(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_20(); 

            
        tl::expected<int, my_error_t> funct_group2_19()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_20(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_21(); 

            
        tl::expected<int, my_error_t> funct_group2_20()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_21(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_22(); 

            
        tl::expected<int, my_error_t> funct_group2_21()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_22(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group2_23(); 

            
        tl::expected<int, my_error_t> funct_group2_22()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group2_23(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group2_23()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_1(); 

            
        tl::expected<int, my_error_t> funct_group3_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_2(); 

            
        tl::expected<int, my_error_t> funct_group3_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_3(); 

            
        tl::expected<int, my_error_t> funct_group3_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_4(); 

            
        tl::expected<int, my_error_t> funct_group3_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_5(); 

            
        tl::expected<int, my_error_t> funct_group3_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_6(); 

            
        tl::expected<int, my_error_t> funct_group3_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_7(); 

            
        tl::expected<int, my_error_t> funct_group3_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_8(); 

            
        tl::expected<int, my_error_t> funct_group3_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_9(); 

            
        tl::expected<int, my_error_t> funct_group3_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_10(); 

            
        tl::expected<int, my_error_t> funct_group3_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_11(); 

            
        tl::expected<int, my_error_t> funct_group3_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_12(); 

            
        tl::expected<int, my_error_t> funct_group3_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_12(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_13(); 

            
        tl::expected<int, my_error_t> funct_group3_12()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_13(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_14(); 

            
        tl::expected<int, my_error_t> funct_group3_13()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_14(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_15(); 

            
        tl::expected<int, my_error_t> funct_group3_14()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_15(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_16(); 

            
        tl::expected<int, my_error_t> funct_group3_15()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_16(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_17(); 

            
        tl::expected<int, my_error_t> funct_group3_16()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_17(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_18(); 

            
        tl::expected<int, my_error_t> funct_group3_17()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_18(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_19(); 

            
        tl::expected<int, my_error_t> funct_group3_18()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_19(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_20(); 

            
        tl::expected<int, my_error_t> funct_group3_19()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_20(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_21(); 

            
        tl::expected<int, my_error_t> funct_group3_20()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_21(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_22(); 

            
        tl::expected<int, my_error_t> funct_group3_21()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_22(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_23(); 

            
        tl::expected<int, my_error_t> funct_group3_22()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_23(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_24(); 

            
        tl::expected<int, my_error_t> funct_group3_23()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_24(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_25(); 

            
        tl::expected<int, my_error_t> funct_group3_24()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_25(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_26(); 

            
        tl::expected<int, my_error_t> funct_group3_25()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_26(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_27(); 

            
        tl::expected<int, my_error_t> funct_group3_26()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_27(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_28(); 

            
        tl::expected<int, my_error_t> funct_group3_27()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_28(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_29(); 

            
        tl::expected<int, my_error_t> funct_group3_28()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_29(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_30(); 

            
        tl::expected<int, my_error_t> funct_group3_29()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_30(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_31(); 

            
        tl::expected<int, my_error_t> funct_group3_30()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_31(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_32(); 

            
        tl::expected<int, my_error_t> funct_group3_31()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_32(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_33(); 

            
        tl::expected<int, my_error_t> funct_group3_32()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_33(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_34(); 

            
        tl::expected<int, my_error_t> funct_group3_33()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_34(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_35(); 

            
        tl::expected<int, my_error_t> funct_group3_34()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_35(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_36(); 

            
        tl::expected<int, my_error_t> funct_group3_35()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_36(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_37(); 

            
        tl::expected<int, my_error_t> funct_group3_36()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_37(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_38(); 

            
        tl::expected<int, my_error_t> funct_group3_37()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_38(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_39(); 

            
        tl::expected<int, my_error_t> funct_group3_38()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_39(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_40(); 

            
        tl::expected<int, my_error_t> funct_group3_39()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_40(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_41(); 

            
        tl::expected<int, my_error_t> funct_group3_40()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_41(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_42(); 

            
        tl::expected<int, my_error_t> funct_group3_41()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_42(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_43(); 

            
        tl::expected<int, my_error_t> funct_group3_42()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_43(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_44(); 

            
        tl::expected<int, my_error_t> funct_group3_43()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_44(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_45(); 

            
        tl::expected<int, my_error_t> funct_group3_44()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_45(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_46(); 

            
        tl::expected<int, my_error_t> funct_group3_45()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_46(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group3_47(); 

            
        tl::expected<int, my_error_t> funct_group3_46()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group3_47(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group3_47()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_1(); 

            
        tl::expected<int, my_error_t> funct_group4_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_2(); 

            
        tl::expected<int, my_error_t> funct_group4_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_3(); 

            
        tl::expected<int, my_error_t> funct_group4_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_4(); 

            
        tl::expected<int, my_error_t> funct_group4_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_5(); 

            
        tl::expected<int, my_error_t> funct_group4_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_6(); 

            
        tl::expected<int, my_error_t> funct_group4_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_7(); 

            
        tl::expected<int, my_error_t> funct_group4_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_8(); 

            
        tl::expected<int, my_error_t> funct_group4_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_9(); 

            
        tl::expected<int, my_error_t> funct_group4_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_10(); 

            
        tl::expected<int, my_error_t> funct_group4_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_11(); 

            
        tl::expected<int, my_error_t> funct_group4_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_12(); 

            
        tl::expected<int, my_error_t> funct_group4_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_12(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_13(); 

            
        tl::expected<int, my_error_t> funct_group4_12()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_13(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_14(); 

            
        tl::expected<int, my_error_t> funct_group4_13()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_14(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_15(); 

            
        tl::expected<int, my_error_t> funct_group4_14()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_15(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_16(); 

            
        tl::expected<int, my_error_t> funct_group4_15()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_16(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_17(); 

            
        tl::expected<int, my_error_t> funct_group4_16()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_17(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_18(); 

            
        tl::expected<int, my_error_t> funct_group4_17()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_18(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_19(); 

            
        tl::expected<int, my_error_t> funct_group4_18()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_19(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_20(); 

            
        tl::expected<int, my_error_t> funct_group4_19()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_20(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_21(); 

            
        tl::expected<int, my_error_t> funct_group4_20()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_21(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_22(); 

            
        tl::expected<int, my_error_t> funct_group4_21()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_22(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_23(); 

            
        tl::expected<int, my_error_t> funct_group4_22()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_23(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_24(); 

            
        tl::expected<int, my_error_t> funct_group4_23()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_24(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_25(); 

            
        tl::expected<int, my_error_t> funct_group4_24()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_25(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_26(); 

            
        tl::expected<int, my_error_t> funct_group4_25()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_26(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_27(); 

            
        tl::expected<int, my_error_t> funct_group4_26()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_27(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_28(); 

            
        tl::expected<int, my_error_t> funct_group4_27()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_28(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_29(); 

            
        tl::expected<int, my_error_t> funct_group4_28()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_29(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_30(); 

            
        tl::expected<int, my_error_t> funct_group4_29()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_30(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_31(); 

            
        tl::expected<int, my_error_t> funct_group4_30()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_31(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_32(); 

            
        tl::expected<int, my_error_t> funct_group4_31()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_32(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_33(); 

            
        tl::expected<int, my_error_t> funct_group4_32()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_33(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_34(); 

            
        tl::expected<int, my_error_t> funct_group4_33()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_34(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_35(); 

            
        tl::expected<int, my_error_t> funct_group4_34()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_35(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_36(); 

            
        tl::expected<int, my_error_t> funct_group4_35()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_36(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_37(); 

            
        tl::expected<int, my_error_t> funct_group4_36()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_37(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_38(); 

            
        tl::expected<int, my_error_t> funct_group4_37()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_38(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_39(); 

            
        tl::expected<int, my_error_t> funct_group4_38()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_39(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_40(); 

            
        tl::expected<int, my_error_t> funct_group4_39()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_40(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_41(); 

            
        tl::expected<int, my_error_t> funct_group4_40()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_41(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_42(); 

            
        tl::expected<int, my_error_t> funct_group4_41()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_42(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_43(); 

            
        tl::expected<int, my_error_t> funct_group4_42()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_43(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_44(); 

            
        tl::expected<int, my_error_t> funct_group4_43()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_44(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_45(); 

            
        tl::expected<int, my_error_t> funct_group4_44()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_45(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_46(); 

            
        tl::expected<int, my_error_t> funct_group4_45()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_46(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_47(); 

            
        tl::expected<int, my_error_t> funct_group4_46()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_47(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_48(); 

            
        tl::expected<int, my_error_t> funct_group4_47()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_48(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_49(); 

            
        tl::expected<int, my_error_t> funct_group4_48()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_49(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_50(); 

            
        tl::expected<int, my_error_t> funct_group4_49()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_50(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_51(); 

            
        tl::expected<int, my_error_t> funct_group4_50()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_51(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_52(); 

            
        tl::expected<int, my_error_t> funct_group4_51()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_52(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_53(); 

            
        tl::expected<int, my_error_t> funct_group4_52()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_53(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_54(); 

            
        tl::expected<int, my_error_t> funct_group4_53()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_54(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_55(); 

            
        tl::expected<int, my_error_t> funct_group4_54()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_55(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_56(); 

            
        tl::expected<int, my_error_t> funct_group4_55()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_56(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_57(); 

            
        tl::expected<int, my_error_t> funct_group4_56()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_57(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_58(); 

            
        tl::expected<int, my_error_t> funct_group4_57()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_58(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_59(); 

            
        tl::expected<int, my_error_t> funct_group4_58()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_59(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_60(); 

            
        tl::expected<int, my_error_t> funct_group4_59()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_60(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_61(); 

            
        tl::expected<int, my_error_t> funct_group4_60()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_61(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_62(); 

            
        tl::expected<int, my_error_t> funct_group4_61()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_62(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_63(); 

            
        tl::expected<int, my_error_t> funct_group4_62()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_63(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_64(); 

            
        tl::expected<int, my_error_t> funct_group4_63()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_64(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_65(); 

            
        tl::expected<int, my_error_t> funct_group4_64()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_65(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_66(); 

            
        tl::expected<int, my_error_t> funct_group4_65()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_66(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_67(); 

            
        tl::expected<int, my_error_t> funct_group4_66()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_67(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_68(); 

            
        tl::expected<int, my_error_t> funct_group4_67()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_68(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_69(); 

            
        tl::expected<int, my_error_t> funct_group4_68()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_69(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_70(); 

            
        tl::expected<int, my_error_t> funct_group4_69()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_70(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_71(); 

            
        tl::expected<int, my_error_t> funct_group4_70()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_71(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_72(); 

            
        tl::expected<int, my_error_t> funct_group4_71()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_72(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_73(); 

            
        tl::expected<int, my_error_t> funct_group4_72()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_73(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_74(); 

            
        tl::expected<int, my_error_t> funct_group4_73()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_74(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_75(); 

            
        tl::expected<int, my_error_t> funct_group4_74()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_75(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_76(); 

            
        tl::expected<int, my_error_t> funct_group4_75()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_76(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_77(); 

            
        tl::expected<int, my_error_t> funct_group4_76()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_77(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_78(); 

            
        tl::expected<int, my_error_t> funct_group4_77()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_78(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_79(); 

            
        tl::expected<int, my_error_t> funct_group4_78()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_79(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_80(); 

            
        tl::expected<int, my_error_t> funct_group4_79()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_80(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_81(); 

            
        tl::expected<int, my_error_t> funct_group4_80()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_81(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_82(); 

            
        tl::expected<int, my_error_t> funct_group4_81()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_82(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_83(); 

            
        tl::expected<int, my_error_t> funct_group4_82()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_83(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_84(); 

            
        tl::expected<int, my_error_t> funct_group4_83()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_84(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_85(); 

            
        tl::expected<int, my_error_t> funct_group4_84()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_85(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_86(); 

            
        tl::expected<int, my_error_t> funct_group4_85()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_86(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_87(); 

            
        tl::expected<int, my_error_t> funct_group4_86()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_87(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_88(); 

            
        tl::expected<int, my_error_t> funct_group4_87()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_88(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_89(); 

            
        tl::expected<int, my_error_t> funct_group4_88()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_89(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_90(); 

            
        tl::expected<int, my_error_t> funct_group4_89()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_90(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_91(); 

            
        tl::expected<int, my_error_t> funct_group4_90()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_91(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_92(); 

            
        tl::expected<int, my_error_t> funct_group4_91()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_92(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_93(); 

            
        tl::expected<int, my_error_t> funct_group4_92()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_93(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_94(); 

            
        tl::expected<int, my_error_t> funct_group4_93()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_94(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group4_95(); 

            
        tl::expected<int, my_error_t> funct_group4_94()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group4_95(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group4_95()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group5_1(); 

            
        tl::expected<int, my_error_t> funct_group5_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group5_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group5_2(); 

            
        tl::expected<int, my_error_t> funct_group5_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group5_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group5_3(); 

            
        tl::expected<int, my_error_t> funct_group5_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group5_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group5_4(); 

            
        tl::expected<int, my_error_t> funct_group5_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group5_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group5_5(); 

            
        tl::expected<int, my_error_t> funct_group5_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group5_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group5_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group6_1(); 

            
        tl::expected<int, my_error_t> funct_group6_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group6_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group6_2(); 

            
        tl::expected<int, my_error_t> funct_group6_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group6_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group6_3(); 

            
        tl::expected<int, my_error_t> funct_group6_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group6_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group6_4(); 

            
        tl::expected<int, my_error_t> funct_group6_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group6_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group6_5(); 

            
        tl::expected<int, my_error_t> funct_group6_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group6_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group6_6(); 

            
        tl::expected<int, my_error_t> funct_group6_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group6_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group6_7(); 

            
        tl::expected<int, my_error_t> funct_group6_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group6_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group6_8(); 

            
        tl::expected<int, my_error_t> funct_group6_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group6_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group6_9(); 

            
        tl::expected<int, my_error_t> funct_group6_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group6_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group6_10(); 

            
        tl::expected<int, my_error_t> funct_group6_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group6_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group6_11(); 

            
        tl::expected<int, my_error_t> funct_group6_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group6_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group6_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_1(); 

            
        tl::expected<int, my_error_t> funct_group7_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_2(); 

            
        tl::expected<int, my_error_t> funct_group7_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_3(); 

            
        tl::expected<int, my_error_t> funct_group7_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_4(); 

            
        tl::expected<int, my_error_t> funct_group7_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_5(); 

            
        tl::expected<int, my_error_t> funct_group7_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_6(); 

            
        tl::expected<int, my_error_t> funct_group7_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_7(); 

            
        tl::expected<int, my_error_t> funct_group7_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_8(); 

            
        tl::expected<int, my_error_t> funct_group7_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_9(); 

            
        tl::expected<int, my_error_t> funct_group7_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_10(); 

            
        tl::expected<int, my_error_t> funct_group7_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_11(); 

            
        tl::expected<int, my_error_t> funct_group7_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_12(); 

            
        tl::expected<int, my_error_t> funct_group7_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_12(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_13(); 

            
        tl::expected<int, my_error_t> funct_group7_12()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_13(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_14(); 

            
        tl::expected<int, my_error_t> funct_group7_13()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_14(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_15(); 

            
        tl::expected<int, my_error_t> funct_group7_14()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_15(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_16(); 

            
        tl::expected<int, my_error_t> funct_group7_15()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_16(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_17(); 

            
        tl::expected<int, my_error_t> funct_group7_16()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_17(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_18(); 

            
        tl::expected<int, my_error_t> funct_group7_17()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_18(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_19(); 

            
        tl::expected<int, my_error_t> funct_group7_18()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_19(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_20(); 

            
        tl::expected<int, my_error_t> funct_group7_19()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_20(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_21(); 

            
        tl::expected<int, my_error_t> funct_group7_20()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_21(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_22(); 

            
        tl::expected<int, my_error_t> funct_group7_21()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_22(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group7_23(); 

            
        tl::expected<int, my_error_t> funct_group7_22()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group7_23(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group7_23()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_1(); 

            
        tl::expected<int, my_error_t> funct_group8_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_2(); 

            
        tl::expected<int, my_error_t> funct_group8_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_3(); 

            
        tl::expected<int, my_error_t> funct_group8_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_4(); 

            
        tl::expected<int, my_error_t> funct_group8_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_5(); 

            
        tl::expected<int, my_error_t> funct_group8_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_6(); 

            
        tl::expected<int, my_error_t> funct_group8_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_7(); 

            
        tl::expected<int, my_error_t> funct_group8_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_8(); 

            
        tl::expected<int, my_error_t> funct_group8_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_9(); 

            
        tl::expected<int, my_error_t> funct_group8_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_10(); 

            
        tl::expected<int, my_error_t> funct_group8_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_11(); 

            
        tl::expected<int, my_error_t> funct_group8_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_12(); 

            
        tl::expected<int, my_error_t> funct_group8_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_12(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_13(); 

            
        tl::expected<int, my_error_t> funct_group8_12()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_13(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_14(); 

            
        tl::expected<int, my_error_t> funct_group8_13()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_14(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_15(); 

            
        tl::expected<int, my_error_t> funct_group8_14()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_15(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_16(); 

            
        tl::expected<int, my_error_t> funct_group8_15()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_16(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_17(); 

            
        tl::expected<int, my_error_t> funct_group8_16()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_17(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_18(); 

            
        tl::expected<int, my_error_t> funct_group8_17()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_18(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_19(); 

            
        tl::expected<int, my_error_t> funct_group8_18()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_19(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_20(); 

            
        tl::expected<int, my_error_t> funct_group8_19()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_20(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_21(); 

            
        tl::expected<int, my_error_t> funct_group8_20()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_21(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_22(); 

            
        tl::expected<int, my_error_t> funct_group8_21()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_22(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_23(); 

            
        tl::expected<int, my_error_t> funct_group8_22()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_23(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_24(); 

            
        tl::expected<int, my_error_t> funct_group8_23()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_24(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_25(); 

            
        tl::expected<int, my_error_t> funct_group8_24()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_25(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_26(); 

            
        tl::expected<int, my_error_t> funct_group8_25()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_26(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_27(); 

            
        tl::expected<int, my_error_t> funct_group8_26()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_27(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_28(); 

            
        tl::expected<int, my_error_t> funct_group8_27()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_28(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_29(); 

            
        tl::expected<int, my_error_t> funct_group8_28()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_29(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_30(); 

            
        tl::expected<int, my_error_t> funct_group8_29()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_30(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_31(); 

            
        tl::expected<int, my_error_t> funct_group8_30()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_31(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_32(); 

            
        tl::expected<int, my_error_t> funct_group8_31()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_32(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_33(); 

            
        tl::expected<int, my_error_t> funct_group8_32()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_33(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_34(); 

            
        tl::expected<int, my_error_t> funct_group8_33()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_34(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_35(); 

            
        tl::expected<int, my_error_t> funct_group8_34()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_35(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_36(); 

            
        tl::expected<int, my_error_t> funct_group8_35()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_36(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_37(); 

            
        tl::expected<int, my_error_t> funct_group8_36()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_37(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_38(); 

            
        tl::expected<int, my_error_t> funct_group8_37()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_38(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_39(); 

            
        tl::expected<int, my_error_t> funct_group8_38()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_39(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_40(); 

            
        tl::expected<int, my_error_t> funct_group8_39()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_40(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_41(); 

            
        tl::expected<int, my_error_t> funct_group8_40()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_41(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_42(); 

            
        tl::expected<int, my_error_t> funct_group8_41()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_42(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_43(); 

            
        tl::expected<int, my_error_t> funct_group8_42()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_43(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_44(); 

            
        tl::expected<int, my_error_t> funct_group8_43()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_44(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_45(); 

            
        tl::expected<int, my_error_t> funct_group8_44()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_45(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_46(); 

            
        tl::expected<int, my_error_t> funct_group8_45()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_46(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group8_47(); 

            
        tl::expected<int, my_error_t> funct_group8_46()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group8_47(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group8_47()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_1(); 

            
        tl::expected<int, my_error_t> funct_group9_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_2(); 

            
        tl::expected<int, my_error_t> funct_group9_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_3(); 

            
        tl::expected<int, my_error_t> funct_group9_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_4(); 

            
        tl::expected<int, my_error_t> funct_group9_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_5(); 

            
        tl::expected<int, my_error_t> funct_group9_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_6(); 

            
        tl::expected<int, my_error_t> funct_group9_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_7(); 

            
        tl::expected<int, my_error_t> funct_group9_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_8(); 

            
        tl::expected<int, my_error_t> funct_group9_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_9(); 

            
        tl::expected<int, my_error_t> funct_group9_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_10(); 

            
        tl::expected<int, my_error_t> funct_group9_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_11(); 

            
        tl::expected<int, my_error_t> funct_group9_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_12(); 

            
        tl::expected<int, my_error_t> funct_group9_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_12(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_13(); 

            
        tl::expected<int, my_error_t> funct_group9_12()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_13(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_14(); 

            
        tl::expected<int, my_error_t> funct_group9_13()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_14(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_15(); 

            
        tl::expected<int, my_error_t> funct_group9_14()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_15(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_16(); 

            
        tl::expected<int, my_error_t> funct_group9_15()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_16(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_17(); 

            
        tl::expected<int, my_error_t> funct_group9_16()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_17(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_18(); 

            
        tl::expected<int, my_error_t> funct_group9_17()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_18(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_19(); 

            
        tl::expected<int, my_error_t> funct_group9_18()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_19(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_20(); 

            
        tl::expected<int, my_error_t> funct_group9_19()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_20(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_21(); 

            
        tl::expected<int, my_error_t> funct_group9_20()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_21(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_22(); 

            
        tl::expected<int, my_error_t> funct_group9_21()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_22(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_23(); 

            
        tl::expected<int, my_error_t> funct_group9_22()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_23(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_24(); 

            
        tl::expected<int, my_error_t> funct_group9_23()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_24(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_25(); 

            
        tl::expected<int, my_error_t> funct_group9_24()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_25(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_26(); 

            
        tl::expected<int, my_error_t> funct_group9_25()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_26(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_27(); 

            
        tl::expected<int, my_error_t> funct_group9_26()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_27(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_28(); 

            
        tl::expected<int, my_error_t> funct_group9_27()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_28(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_29(); 

            
        tl::expected<int, my_error_t> funct_group9_28()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_29(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_30(); 

            
        tl::expected<int, my_error_t> funct_group9_29()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_30(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_31(); 

            
        tl::expected<int, my_error_t> funct_group9_30()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_31(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_32(); 

            
        tl::expected<int, my_error_t> funct_group9_31()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_32(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_33(); 

            
        tl::expected<int, my_error_t> funct_group9_32()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_33(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_34(); 

            
        tl::expected<int, my_error_t> funct_group9_33()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_34(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_35(); 

            
        tl::expected<int, my_error_t> funct_group9_34()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_35(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_36(); 

            
        tl::expected<int, my_error_t> funct_group9_35()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_36(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_37(); 

            
        tl::expected<int, my_error_t> funct_group9_36()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_37(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_38(); 

            
        tl::expected<int, my_error_t> funct_group9_37()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_38(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_39(); 

            
        tl::expected<int, my_error_t> funct_group9_38()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_39(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_40(); 

            
        tl::expected<int, my_error_t> funct_group9_39()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_40(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_41(); 

            
        tl::expected<int, my_error_t> funct_group9_40()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_41(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_42(); 

            
        tl::expected<int, my_error_t> funct_group9_41()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_42(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_43(); 

            
        tl::expected<int, my_error_t> funct_group9_42()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_43(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_44(); 

            
        tl::expected<int, my_error_t> funct_group9_43()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_44(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_45(); 

            
        tl::expected<int, my_error_t> funct_group9_44()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_45(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_46(); 

            
        tl::expected<int, my_error_t> funct_group9_45()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_46(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_47(); 

            
        tl::expected<int, my_error_t> funct_group9_46()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_47(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_48(); 

            
        tl::expected<int, my_error_t> funct_group9_47()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_48(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_49(); 

            
        tl::expected<int, my_error_t> funct_group9_48()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_49(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_50(); 

            
        tl::expected<int, my_error_t> funct_group9_49()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_50(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_51(); 

            
        tl::expected<int, my_error_t> funct_group9_50()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_51(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_52(); 

            
        tl::expected<int, my_error_t> funct_group9_51()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_52(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_53(); 

            
        tl::expected<int, my_error_t> funct_group9_52()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_53(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_54(); 

            
        tl::expected<int, my_error_t> funct_group9_53()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_54(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_55(); 

            
        tl::expected<int, my_error_t> funct_group9_54()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_55(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_56(); 

            
        tl::expected<int, my_error_t> funct_group9_55()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_56(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_57(); 

            
        tl::expected<int, my_error_t> funct_group9_56()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_57(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_58(); 

            
        tl::expected<int, my_error_t> funct_group9_57()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_58(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_59(); 

            
        tl::expected<int, my_error_t> funct_group9_58()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_59(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_60(); 

            
        tl::expected<int, my_error_t> funct_group9_59()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_60(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_61(); 

            
        tl::expected<int, my_error_t> funct_group9_60()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_61(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_62(); 

            
        tl::expected<int, my_error_t> funct_group9_61()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_62(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_63(); 

            
        tl::expected<int, my_error_t> funct_group9_62()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_63(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_64(); 

            
        tl::expected<int, my_error_t> funct_group9_63()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_64(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_65(); 

            
        tl::expected<int, my_error_t> funct_group9_64()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_65(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_66(); 

            
        tl::expected<int, my_error_t> funct_group9_65()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_66(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_67(); 

            
        tl::expected<int, my_error_t> funct_group9_66()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_67(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_68(); 

            
        tl::expected<int, my_error_t> funct_group9_67()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_68(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_69(); 

            
        tl::expected<int, my_error_t> funct_group9_68()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_69(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_70(); 

            
        tl::expected<int, my_error_t> funct_group9_69()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_70(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_71(); 

            
        tl::expected<int, my_error_t> funct_group9_70()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_71(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_72(); 

            
        tl::expected<int, my_error_t> funct_group9_71()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_72(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_73(); 

            
        tl::expected<int, my_error_t> funct_group9_72()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_73(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_74(); 

            
        tl::expected<int, my_error_t> funct_group9_73()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_74(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_75(); 

            
        tl::expected<int, my_error_t> funct_group9_74()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_75(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_76(); 

            
        tl::expected<int, my_error_t> funct_group9_75()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_76(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_77(); 

            
        tl::expected<int, my_error_t> funct_group9_76()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_77(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_78(); 

            
        tl::expected<int, my_error_t> funct_group9_77()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_78(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_79(); 

            
        tl::expected<int, my_error_t> funct_group9_78()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_79(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_80(); 

            
        tl::expected<int, my_error_t> funct_group9_79()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_80(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_81(); 

            
        tl::expected<int, my_error_t> funct_group9_80()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_81(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_82(); 

            
        tl::expected<int, my_error_t> funct_group9_81()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_82(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_83(); 

            
        tl::expected<int, my_error_t> funct_group9_82()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_83(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_84(); 

            
        tl::expected<int, my_error_t> funct_group9_83()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_84(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_85(); 

            
        tl::expected<int, my_error_t> funct_group9_84()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_85(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_86(); 

            
        tl::expected<int, my_error_t> funct_group9_85()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_86(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_87(); 

            
        tl::expected<int, my_error_t> funct_group9_86()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_87(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_88(); 

            
        tl::expected<int, my_error_t> funct_group9_87()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_88(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_89(); 

            
        tl::expected<int, my_error_t> funct_group9_88()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_89(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_90(); 

            
        tl::expected<int, my_error_t> funct_group9_89()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_90(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_91(); 

            
        tl::expected<int, my_error_t> funct_group9_90()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_91(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_92(); 

            
        tl::expected<int, my_error_t> funct_group9_91()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_92(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_93(); 

            
        tl::expected<int, my_error_t> funct_group9_92()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_93(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_94(); 

            
        tl::expected<int, my_error_t> funct_group9_93()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_94(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group9_95(); 

            
        tl::expected<int, my_error_t> funct_group9_94()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group9_95(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group9_95()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group10_1(); 

            
        tl::expected<int, my_error_t> funct_group10_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group10_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group10_2(); 

            
        tl::expected<int, my_error_t> funct_group10_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group10_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group10_3(); 

            
        tl::expected<int, my_error_t> funct_group10_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group10_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group10_4(); 

            
        tl::expected<int, my_error_t> funct_group10_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group10_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group10_5(); 

            
        tl::expected<int, my_error_t> funct_group10_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group10_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group10_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group11_1(); 

            
        tl::expected<int, my_error_t> funct_group11_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group11_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group11_2(); 

            
        tl::expected<int, my_error_t> funct_group11_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group11_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group11_3(); 

            
        tl::expected<int, my_error_t> funct_group11_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group11_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group11_4(); 

            
        tl::expected<int, my_error_t> funct_group11_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group11_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group11_5(); 

            
        tl::expected<int, my_error_t> funct_group11_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group11_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group11_6(); 

            
        tl::expected<int, my_error_t> funct_group11_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group11_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group11_7(); 

            
        tl::expected<int, my_error_t> funct_group11_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group11_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group11_8(); 

            
        tl::expected<int, my_error_t> funct_group11_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group11_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group11_9(); 

            
        tl::expected<int, my_error_t> funct_group11_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group11_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group11_10(); 

            
        tl::expected<int, my_error_t> funct_group11_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group11_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group11_11(); 

            
        tl::expected<int, my_error_t> funct_group11_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group11_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group11_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_1(); 

            
        tl::expected<int, my_error_t> funct_group12_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_2(); 

            
        tl::expected<int, my_error_t> funct_group12_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_3(); 

            
        tl::expected<int, my_error_t> funct_group12_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_4(); 

            
        tl::expected<int, my_error_t> funct_group12_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_5(); 

            
        tl::expected<int, my_error_t> funct_group12_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_6(); 

            
        tl::expected<int, my_error_t> funct_group12_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_7(); 

            
        tl::expected<int, my_error_t> funct_group12_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_8(); 

            
        tl::expected<int, my_error_t> funct_group12_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_9(); 

            
        tl::expected<int, my_error_t> funct_group12_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_10(); 

            
        tl::expected<int, my_error_t> funct_group12_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_11(); 

            
        tl::expected<int, my_error_t> funct_group12_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_12(); 

            
        tl::expected<int, my_error_t> funct_group12_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_12(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_13(); 

            
        tl::expected<int, my_error_t> funct_group12_12()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_13(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_14(); 

            
        tl::expected<int, my_error_t> funct_group12_13()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_14(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_15(); 

            
        tl::expected<int, my_error_t> funct_group12_14()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_15(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_16(); 

            
        tl::expected<int, my_error_t> funct_group12_15()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_16(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_17(); 

            
        tl::expected<int, my_error_t> funct_group12_16()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_17(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_18(); 

            
        tl::expected<int, my_error_t> funct_group12_17()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_18(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_19(); 

            
        tl::expected<int, my_error_t> funct_group12_18()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_19(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_20(); 

            
        tl::expected<int, my_error_t> funct_group12_19()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_20(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_21(); 

            
        tl::expected<int, my_error_t> funct_group12_20()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_21(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_22(); 

            
        tl::expected<int, my_error_t> funct_group12_21()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_22(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group12_23(); 

            
        tl::expected<int, my_error_t> funct_group12_22()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group12_23(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group12_23()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_1(); 

            
        tl::expected<int, my_error_t> funct_group13_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_2(); 

            
        tl::expected<int, my_error_t> funct_group13_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_3(); 

            
        tl::expected<int, my_error_t> funct_group13_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_4(); 

            
        tl::expected<int, my_error_t> funct_group13_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_5(); 

            
        tl::expected<int, my_error_t> funct_group13_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_6(); 

            
        tl::expected<int, my_error_t> funct_group13_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_7(); 

            
        tl::expected<int, my_error_t> funct_group13_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_8(); 

            
        tl::expected<int, my_error_t> funct_group13_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_9(); 

            
        tl::expected<int, my_error_t> funct_group13_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_10(); 

            
        tl::expected<int, my_error_t> funct_group13_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_11(); 

            
        tl::expected<int, my_error_t> funct_group13_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_12(); 

            
        tl::expected<int, my_error_t> funct_group13_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_12(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_13(); 

            
        tl::expected<int, my_error_t> funct_group13_12()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_13(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_14(); 

            
        tl::expected<int, my_error_t> funct_group13_13()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_14(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_15(); 

            
        tl::expected<int, my_error_t> funct_group13_14()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_15(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_16(); 

            
        tl::expected<int, my_error_t> funct_group13_15()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_16(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_17(); 

            
        tl::expected<int, my_error_t> funct_group13_16()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_17(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_18(); 

            
        tl::expected<int, my_error_t> funct_group13_17()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_18(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_19(); 

            
        tl::expected<int, my_error_t> funct_group13_18()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_19(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_20(); 

            
        tl::expected<int, my_error_t> funct_group13_19()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_20(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_21(); 

            
        tl::expected<int, my_error_t> funct_group13_20()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_21(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_22(); 

            
        tl::expected<int, my_error_t> funct_group13_21()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_22(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_23(); 

            
        tl::expected<int, my_error_t> funct_group13_22()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_23(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_24(); 

            
        tl::expected<int, my_error_t> funct_group13_23()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_24(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_25(); 

            
        tl::expected<int, my_error_t> funct_group13_24()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_25(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_26(); 

            
        tl::expected<int, my_error_t> funct_group13_25()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_26(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_27(); 

            
        tl::expected<int, my_error_t> funct_group13_26()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_27(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_28(); 

            
        tl::expected<int, my_error_t> funct_group13_27()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_28(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_29(); 

            
        tl::expected<int, my_error_t> funct_group13_28()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_29(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_30(); 

            
        tl::expected<int, my_error_t> funct_group13_29()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_30(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_31(); 

            
        tl::expected<int, my_error_t> funct_group13_30()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_31(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_32(); 

            
        tl::expected<int, my_error_t> funct_group13_31()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_32(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_33(); 

            
        tl::expected<int, my_error_t> funct_group13_32()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_33(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_34(); 

            
        tl::expected<int, my_error_t> funct_group13_33()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_34(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_35(); 

            
        tl::expected<int, my_error_t> funct_group13_34()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_35(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_36(); 

            
        tl::expected<int, my_error_t> funct_group13_35()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_36(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_37(); 

            
        tl::expected<int, my_error_t> funct_group13_36()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_37(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_38(); 

            
        tl::expected<int, my_error_t> funct_group13_37()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_38(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_39(); 

            
        tl::expected<int, my_error_t> funct_group13_38()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_39(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_40(); 

            
        tl::expected<int, my_error_t> funct_group13_39()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_40(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_41(); 

            
        tl::expected<int, my_error_t> funct_group13_40()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_41(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_42(); 

            
        tl::expected<int, my_error_t> funct_group13_41()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_42(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_43(); 

            
        tl::expected<int, my_error_t> funct_group13_42()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_43(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_44(); 

            
        tl::expected<int, my_error_t> funct_group13_43()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_44(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_45(); 

            
        tl::expected<int, my_error_t> funct_group13_44()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_45(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_46(); 

            
        tl::expected<int, my_error_t> funct_group13_45()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_46(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group13_47(); 

            
        tl::expected<int, my_error_t> funct_group13_46()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group13_47(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group13_47()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_1(); 

            
        tl::expected<int, my_error_t> funct_group14_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_2(); 

            
        tl::expected<int, my_error_t> funct_group14_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_3(); 

            
        tl::expected<int, my_error_t> funct_group14_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_4(); 

            
        tl::expected<int, my_error_t> funct_group14_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_5(); 

            
        tl::expected<int, my_error_t> funct_group14_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_6(); 

            
        tl::expected<int, my_error_t> funct_group14_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_7(); 

            
        tl::expected<int, my_error_t> funct_group14_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_8(); 

            
        tl::expected<int, my_error_t> funct_group14_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_9(); 

            
        tl::expected<int, my_error_t> funct_group14_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_10(); 

            
        tl::expected<int, my_error_t> funct_group14_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_11(); 

            
        tl::expected<int, my_error_t> funct_group14_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_12(); 

            
        tl::expected<int, my_error_t> funct_group14_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_12(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_13(); 

            
        tl::expected<int, my_error_t> funct_group14_12()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_13(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_14(); 

            
        tl::expected<int, my_error_t> funct_group14_13()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_14(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_15(); 

            
        tl::expected<int, my_error_t> funct_group14_14()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_15(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_16(); 

            
        tl::expected<int, my_error_t> funct_group14_15()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_16(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_17(); 

            
        tl::expected<int, my_error_t> funct_group14_16()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_17(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_18(); 

            
        tl::expected<int, my_error_t> funct_group14_17()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_18(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_19(); 

            
        tl::expected<int, my_error_t> funct_group14_18()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_19(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_20(); 

            
        tl::expected<int, my_error_t> funct_group14_19()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_20(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_21(); 

            
        tl::expected<int, my_error_t> funct_group14_20()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_21(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_22(); 

            
        tl::expected<int, my_error_t> funct_group14_21()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_22(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_23(); 

            
        tl::expected<int, my_error_t> funct_group14_22()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_23(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_24(); 

            
        tl::expected<int, my_error_t> funct_group14_23()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_24(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_25(); 

            
        tl::expected<int, my_error_t> funct_group14_24()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_25(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_26(); 

            
        tl::expected<int, my_error_t> funct_group14_25()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_26(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_27(); 

            
        tl::expected<int, my_error_t> funct_group14_26()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_27(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_28(); 

            
        tl::expected<int, my_error_t> funct_group14_27()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_28(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_29(); 

            
        tl::expected<int, my_error_t> funct_group14_28()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_29(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_30(); 

            
        tl::expected<int, my_error_t> funct_group14_29()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_30(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_31(); 

            
        tl::expected<int, my_error_t> funct_group14_30()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_31(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_32(); 

            
        tl::expected<int, my_error_t> funct_group14_31()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_32(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_33(); 

            
        tl::expected<int, my_error_t> funct_group14_32()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_33(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_34(); 

            
        tl::expected<int, my_error_t> funct_group14_33()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_34(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_35(); 

            
        tl::expected<int, my_error_t> funct_group14_34()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_35(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_36(); 

            
        tl::expected<int, my_error_t> funct_group14_35()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_36(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_37(); 

            
        tl::expected<int, my_error_t> funct_group14_36()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_37(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_38(); 

            
        tl::expected<int, my_error_t> funct_group14_37()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_38(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_39(); 

            
        tl::expected<int, my_error_t> funct_group14_38()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_39(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_40(); 

            
        tl::expected<int, my_error_t> funct_group14_39()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_40(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_41(); 

            
        tl::expected<int, my_error_t> funct_group14_40()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_41(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_42(); 

            
        tl::expected<int, my_error_t> funct_group14_41()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_42(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_43(); 

            
        tl::expected<int, my_error_t> funct_group14_42()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_43(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_44(); 

            
        tl::expected<int, my_error_t> funct_group14_43()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_44(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_45(); 

            
        tl::expected<int, my_error_t> funct_group14_44()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_45(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_46(); 

            
        tl::expected<int, my_error_t> funct_group14_45()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_46(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_47(); 

            
        tl::expected<int, my_error_t> funct_group14_46()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_47(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_48(); 

            
        tl::expected<int, my_error_t> funct_group14_47()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_48(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_49(); 

            
        tl::expected<int, my_error_t> funct_group14_48()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_49(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_50(); 

            
        tl::expected<int, my_error_t> funct_group14_49()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_50(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_51(); 

            
        tl::expected<int, my_error_t> funct_group14_50()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_51(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_52(); 

            
        tl::expected<int, my_error_t> funct_group14_51()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_52(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_53(); 

            
        tl::expected<int, my_error_t> funct_group14_52()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_53(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_54(); 

            
        tl::expected<int, my_error_t> funct_group14_53()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_54(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_55(); 

            
        tl::expected<int, my_error_t> funct_group14_54()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_55(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_56(); 

            
        tl::expected<int, my_error_t> funct_group14_55()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_56(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_57(); 

            
        tl::expected<int, my_error_t> funct_group14_56()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_57(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_58(); 

            
        tl::expected<int, my_error_t> funct_group14_57()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_58(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_59(); 

            
        tl::expected<int, my_error_t> funct_group14_58()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_59(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_60(); 

            
        tl::expected<int, my_error_t> funct_group14_59()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_60(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_61(); 

            
        tl::expected<int, my_error_t> funct_group14_60()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_61(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_62(); 

            
        tl::expected<int, my_error_t> funct_group14_61()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_62(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_63(); 

            
        tl::expected<int, my_error_t> funct_group14_62()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_63(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_64(); 

            
        tl::expected<int, my_error_t> funct_group14_63()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_64(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_65(); 

            
        tl::expected<int, my_error_t> funct_group14_64()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_65(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_66(); 

            
        tl::expected<int, my_error_t> funct_group14_65()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_66(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_67(); 

            
        tl::expected<int, my_error_t> funct_group14_66()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_67(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_68(); 

            
        tl::expected<int, my_error_t> funct_group14_67()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_68(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_69(); 

            
        tl::expected<int, my_error_t> funct_group14_68()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_69(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_70(); 

            
        tl::expected<int, my_error_t> funct_group14_69()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_70(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_71(); 

            
        tl::expected<int, my_error_t> funct_group14_70()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_71(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_72(); 

            
        tl::expected<int, my_error_t> funct_group14_71()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_72(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_73(); 

            
        tl::expected<int, my_error_t> funct_group14_72()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_73(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_74(); 

            
        tl::expected<int, my_error_t> funct_group14_73()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_74(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_75(); 

            
        tl::expected<int, my_error_t> funct_group14_74()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_75(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_76(); 

            
        tl::expected<int, my_error_t> funct_group14_75()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_76(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_77(); 

            
        tl::expected<int, my_error_t> funct_group14_76()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_77(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_78(); 

            
        tl::expected<int, my_error_t> funct_group14_77()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_78(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_79(); 

            
        tl::expected<int, my_error_t> funct_group14_78()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_79(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_80(); 

            
        tl::expected<int, my_error_t> funct_group14_79()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_80(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_81(); 

            
        tl::expected<int, my_error_t> funct_group14_80()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_81(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_82(); 

            
        tl::expected<int, my_error_t> funct_group14_81()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_82(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_83(); 

            
        tl::expected<int, my_error_t> funct_group14_82()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_83(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_84(); 

            
        tl::expected<int, my_error_t> funct_group14_83()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_84(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_85(); 

            
        tl::expected<int, my_error_t> funct_group14_84()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_85(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_86(); 

            
        tl::expected<int, my_error_t> funct_group14_85()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_86(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_87(); 

            
        tl::expected<int, my_error_t> funct_group14_86()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_87(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_88(); 

            
        tl::expected<int, my_error_t> funct_group14_87()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_88(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_89(); 

            
        tl::expected<int, my_error_t> funct_group14_88()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_89(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_90(); 

            
        tl::expected<int, my_error_t> funct_group14_89()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_90(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_91(); 

            
        tl::expected<int, my_error_t> funct_group14_90()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_91(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_92(); 

            
        tl::expected<int, my_error_t> funct_group14_91()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_92(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_93(); 

            
        tl::expected<int, my_error_t> funct_group14_92()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_93(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_94(); 

            
        tl::expected<int, my_error_t> funct_group14_93()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_94(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group14_95(); 

            
        tl::expected<int, my_error_t> funct_group14_94()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group14_95(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group14_95()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group15_1(); 

            
        tl::expected<int, my_error_t> funct_group15_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group15_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group15_2(); 

            
        tl::expected<int, my_error_t> funct_group15_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group15_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group15_3(); 

            
        tl::expected<int, my_error_t> funct_group15_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group15_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group15_4(); 

            
        tl::expected<int, my_error_t> funct_group15_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group15_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group15_5(); 

            
        tl::expected<int, my_error_t> funct_group15_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group15_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group15_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group16_1(); 

            
        tl::expected<int, my_error_t> funct_group16_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group16_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group16_2(); 

            
        tl::expected<int, my_error_t> funct_group16_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group16_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group16_3(); 

            
        tl::expected<int, my_error_t> funct_group16_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group16_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group16_4(); 

            
        tl::expected<int, my_error_t> funct_group16_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group16_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group16_5(); 

            
        tl::expected<int, my_error_t> funct_group16_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group16_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group16_6(); 

            
        tl::expected<int, my_error_t> funct_group16_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group16_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group16_7(); 

            
        tl::expected<int, my_error_t> funct_group16_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group16_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group16_8(); 

            
        tl::expected<int, my_error_t> funct_group16_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group16_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group16_9(); 

            
        tl::expected<int, my_error_t> funct_group16_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group16_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group16_10(); 

            
        tl::expected<int, my_error_t> funct_group16_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group16_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group16_11(); 

            
        tl::expected<int, my_error_t> funct_group16_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group16_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group16_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_1(); 

            
        tl::expected<int, my_error_t> funct_group17_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_2(); 

            
        tl::expected<int, my_error_t> funct_group17_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_3(); 

            
        tl::expected<int, my_error_t> funct_group17_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_4(); 

            
        tl::expected<int, my_error_t> funct_group17_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_5(); 

            
        tl::expected<int, my_error_t> funct_group17_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_6(); 

            
        tl::expected<int, my_error_t> funct_group17_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_7(); 

            
        tl::expected<int, my_error_t> funct_group17_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_8(); 

            
        tl::expected<int, my_error_t> funct_group17_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_9(); 

            
        tl::expected<int, my_error_t> funct_group17_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_10(); 

            
        tl::expected<int, my_error_t> funct_group17_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_11(); 

            
        tl::expected<int, my_error_t> funct_group17_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_12(); 

            
        tl::expected<int, my_error_t> funct_group17_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_12(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_13(); 

            
        tl::expected<int, my_error_t> funct_group17_12()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_13(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_14(); 

            
        tl::expected<int, my_error_t> funct_group17_13()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_14(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_15(); 

            
        tl::expected<int, my_error_t> funct_group17_14()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_15(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_16(); 

            
        tl::expected<int, my_error_t> funct_group17_15()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_16(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_17(); 

            
        tl::expected<int, my_error_t> funct_group17_16()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_17(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_18(); 

            
        tl::expected<int, my_error_t> funct_group17_17()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_18(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_19(); 

            
        tl::expected<int, my_error_t> funct_group17_18()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_19(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_20(); 

            
        tl::expected<int, my_error_t> funct_group17_19()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_20(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_21(); 

            
        tl::expected<int, my_error_t> funct_group17_20()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_21(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_22(); 

            
        tl::expected<int, my_error_t> funct_group17_21()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_22(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group17_23(); 

            
        tl::expected<int, my_error_t> funct_group17_22()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group17_23(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group17_23()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_1(); 

            
        tl::expected<int, my_error_t> funct_group18_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_2(); 

            
        tl::expected<int, my_error_t> funct_group18_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_3(); 

            
        tl::expected<int, my_error_t> funct_group18_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_4(); 

            
        tl::expected<int, my_error_t> funct_group18_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_5(); 

            
        tl::expected<int, my_error_t> funct_group18_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_6(); 

            
        tl::expected<int, my_error_t> funct_group18_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_7(); 

            
        tl::expected<int, my_error_t> funct_group18_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_8(); 

            
        tl::expected<int, my_error_t> funct_group18_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_9(); 

            
        tl::expected<int, my_error_t> funct_group18_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_10(); 

            
        tl::expected<int, my_error_t> funct_group18_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_11(); 

            
        tl::expected<int, my_error_t> funct_group18_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_12(); 

            
        tl::expected<int, my_error_t> funct_group18_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_12(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_13(); 

            
        tl::expected<int, my_error_t> funct_group18_12()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_13(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_14(); 

            
        tl::expected<int, my_error_t> funct_group18_13()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_14(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_15(); 

            
        tl::expected<int, my_error_t> funct_group18_14()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_15(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_16(); 

            
        tl::expected<int, my_error_t> funct_group18_15()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_16(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_17(); 

            
        tl::expected<int, my_error_t> funct_group18_16()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_17(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_18(); 

            
        tl::expected<int, my_error_t> funct_group18_17()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_18(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_19(); 

            
        tl::expected<int, my_error_t> funct_group18_18()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_19(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_20(); 

            
        tl::expected<int, my_error_t> funct_group18_19()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_20(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_21(); 

            
        tl::expected<int, my_error_t> funct_group18_20()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_21(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_22(); 

            
        tl::expected<int, my_error_t> funct_group18_21()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_22(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_23(); 

            
        tl::expected<int, my_error_t> funct_group18_22()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_23(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_24(); 

            
        tl::expected<int, my_error_t> funct_group18_23()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_24(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_25(); 

            
        tl::expected<int, my_error_t> funct_group18_24()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_25(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_26(); 

            
        tl::expected<int, my_error_t> funct_group18_25()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_26(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_27(); 

            
        tl::expected<int, my_error_t> funct_group18_26()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_27(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_28(); 

            
        tl::expected<int, my_error_t> funct_group18_27()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_28(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_29(); 

            
        tl::expected<int, my_error_t> funct_group18_28()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_29(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_30(); 

            
        tl::expected<int, my_error_t> funct_group18_29()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_30(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_31(); 

            
        tl::expected<int, my_error_t> funct_group18_30()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_31(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_32(); 

            
        tl::expected<int, my_error_t> funct_group18_31()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_32(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_33(); 

            
        tl::expected<int, my_error_t> funct_group18_32()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_33(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_34(); 

            
        tl::expected<int, my_error_t> funct_group18_33()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_34(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_35(); 

            
        tl::expected<int, my_error_t> funct_group18_34()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_35(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_36(); 

            
        tl::expected<int, my_error_t> funct_group18_35()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_36(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_37(); 

            
        tl::expected<int, my_error_t> funct_group18_36()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_37(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_38(); 

            
        tl::expected<int, my_error_t> funct_group18_37()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_38(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_39(); 

            
        tl::expected<int, my_error_t> funct_group18_38()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_39(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_40(); 

            
        tl::expected<int, my_error_t> funct_group18_39()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_40(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_41(); 

            
        tl::expected<int, my_error_t> funct_group18_40()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_41(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_42(); 

            
        tl::expected<int, my_error_t> funct_group18_41()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_42(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_43(); 

            
        tl::expected<int, my_error_t> funct_group18_42()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_43(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_44(); 

            
        tl::expected<int, my_error_t> funct_group18_43()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_44(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_45(); 

            
        tl::expected<int, my_error_t> funct_group18_44()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_45(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_46(); 

            
        tl::expected<int, my_error_t> funct_group18_45()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_46(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group18_47(); 

            
        tl::expected<int, my_error_t> funct_group18_46()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group18_47(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group18_47()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_1(); 

            
        tl::expected<int, my_error_t> funct_group19_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_2(); 

            
        tl::expected<int, my_error_t> funct_group19_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_3(); 

            
        tl::expected<int, my_error_t> funct_group19_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_4(); 

            
        tl::expected<int, my_error_t> funct_group19_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_5(); 

            
        tl::expected<int, my_error_t> funct_group19_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_6(); 

            
        tl::expected<int, my_error_t> funct_group19_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_7(); 

            
        tl::expected<int, my_error_t> funct_group19_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_8(); 

            
        tl::expected<int, my_error_t> funct_group19_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_9(); 

            
        tl::expected<int, my_error_t> funct_group19_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_10(); 

            
        tl::expected<int, my_error_t> funct_group19_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_11(); 

            
        tl::expected<int, my_error_t> funct_group19_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_12(); 

            
        tl::expected<int, my_error_t> funct_group19_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_12(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_13(); 

            
        tl::expected<int, my_error_t> funct_group19_12()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_13(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_14(); 

            
        tl::expected<int, my_error_t> funct_group19_13()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_14(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_15(); 

            
        tl::expected<int, my_error_t> funct_group19_14()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_15(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_16(); 

            
        tl::expected<int, my_error_t> funct_group19_15()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_16(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_17(); 

            
        tl::expected<int, my_error_t> funct_group19_16()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_17(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_18(); 

            
        tl::expected<int, my_error_t> funct_group19_17()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_18(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_19(); 

            
        tl::expected<int, my_error_t> funct_group19_18()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_19(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_20(); 

            
        tl::expected<int, my_error_t> funct_group19_19()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_20(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_21(); 

            
        tl::expected<int, my_error_t> funct_group19_20()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_21(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_22(); 

            
        tl::expected<int, my_error_t> funct_group19_21()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_22(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_23(); 

            
        tl::expected<int, my_error_t> funct_group19_22()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_23(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_24(); 

            
        tl::expected<int, my_error_t> funct_group19_23()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_24(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_25(); 

            
        tl::expected<int, my_error_t> funct_group19_24()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_25(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_26(); 

            
        tl::expected<int, my_error_t> funct_group19_25()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_26(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_27(); 

            
        tl::expected<int, my_error_t> funct_group19_26()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_27(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_28(); 

            
        tl::expected<int, my_error_t> funct_group19_27()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_28(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_29(); 

            
        tl::expected<int, my_error_t> funct_group19_28()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_29(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_30(); 

            
        tl::expected<int, my_error_t> funct_group19_29()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_30(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_31(); 

            
        tl::expected<int, my_error_t> funct_group19_30()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_31(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_32(); 

            
        tl::expected<int, my_error_t> funct_group19_31()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_32(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_33(); 

            
        tl::expected<int, my_error_t> funct_group19_32()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_33(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_34(); 

            
        tl::expected<int, my_error_t> funct_group19_33()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_34(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_35(); 

            
        tl::expected<int, my_error_t> funct_group19_34()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_35(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_36(); 

            
        tl::expected<int, my_error_t> funct_group19_35()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_36(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_37(); 

            
        tl::expected<int, my_error_t> funct_group19_36()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_37(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_38(); 

            
        tl::expected<int, my_error_t> funct_group19_37()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_38(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_39(); 

            
        tl::expected<int, my_error_t> funct_group19_38()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_39(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_40(); 

            
        tl::expected<int, my_error_t> funct_group19_39()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_40(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_41(); 

            
        tl::expected<int, my_error_t> funct_group19_40()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_41(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_42(); 

            
        tl::expected<int, my_error_t> funct_group19_41()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_42(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_43(); 

            
        tl::expected<int, my_error_t> funct_group19_42()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_43(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_44(); 

            
        tl::expected<int, my_error_t> funct_group19_43()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_44(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_45(); 

            
        tl::expected<int, my_error_t> funct_group19_44()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_45(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_46(); 

            
        tl::expected<int, my_error_t> funct_group19_45()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_46(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_47(); 

            
        tl::expected<int, my_error_t> funct_group19_46()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_47(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_48(); 

            
        tl::expected<int, my_error_t> funct_group19_47()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_48(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_49(); 

            
        tl::expected<int, my_error_t> funct_group19_48()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_49(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_50(); 

            
        tl::expected<int, my_error_t> funct_group19_49()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_50(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_51(); 

            
        tl::expected<int, my_error_t> funct_group19_50()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_51(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_52(); 

            
        tl::expected<int, my_error_t> funct_group19_51()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_52(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_53(); 

            
        tl::expected<int, my_error_t> funct_group19_52()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_53(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_54(); 

            
        tl::expected<int, my_error_t> funct_group19_53()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_54(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_55(); 

            
        tl::expected<int, my_error_t> funct_group19_54()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_55(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_56(); 

            
        tl::expected<int, my_error_t> funct_group19_55()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_56(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_57(); 

            
        tl::expected<int, my_error_t> funct_group19_56()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_57(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_58(); 

            
        tl::expected<int, my_error_t> funct_group19_57()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_58(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_59(); 

            
        tl::expected<int, my_error_t> funct_group19_58()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_59(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_60(); 

            
        tl::expected<int, my_error_t> funct_group19_59()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_60(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_61(); 

            
        tl::expected<int, my_error_t> funct_group19_60()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_61(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_62(); 

            
        tl::expected<int, my_error_t> funct_group19_61()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_62(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_63(); 

            
        tl::expected<int, my_error_t> funct_group19_62()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_63(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_64(); 

            
        tl::expected<int, my_error_t> funct_group19_63()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_64(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_65(); 

            
        tl::expected<int, my_error_t> funct_group19_64()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_65(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_66(); 

            
        tl::expected<int, my_error_t> funct_group19_65()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_66(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_67(); 

            
        tl::expected<int, my_error_t> funct_group19_66()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_67(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_68(); 

            
        tl::expected<int, my_error_t> funct_group19_67()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_68(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_69(); 

            
        tl::expected<int, my_error_t> funct_group19_68()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_69(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_70(); 

            
        tl::expected<int, my_error_t> funct_group19_69()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_70(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_71(); 

            
        tl::expected<int, my_error_t> funct_group19_70()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_71(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_72(); 

            
        tl::expected<int, my_error_t> funct_group19_71()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_72(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_73(); 

            
        tl::expected<int, my_error_t> funct_group19_72()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_73(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_74(); 

            
        tl::expected<int, my_error_t> funct_group19_73()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_74(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_75(); 

            
        tl::expected<int, my_error_t> funct_group19_74()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_75(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_76(); 

            
        tl::expected<int, my_error_t> funct_group19_75()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_76(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_77(); 

            
        tl::expected<int, my_error_t> funct_group19_76()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_77(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_78(); 

            
        tl::expected<int, my_error_t> funct_group19_77()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_78(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_79(); 

            
        tl::expected<int, my_error_t> funct_group19_78()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_79(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_80(); 

            
        tl::expected<int, my_error_t> funct_group19_79()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_80(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_81(); 

            
        tl::expected<int, my_error_t> funct_group19_80()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_81(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_82(); 

            
        tl::expected<int, my_error_t> funct_group19_81()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_82(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_83(); 

            
        tl::expected<int, my_error_t> funct_group19_82()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_83(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_84(); 

            
        tl::expected<int, my_error_t> funct_group19_83()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_84(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_85(); 

            
        tl::expected<int, my_error_t> funct_group19_84()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_85(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_86(); 

            
        tl::expected<int, my_error_t> funct_group19_85()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_86(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_87(); 

            
        tl::expected<int, my_error_t> funct_group19_86()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_87(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_88(); 

            
        tl::expected<int, my_error_t> funct_group19_87()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_88(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_89(); 

            
        tl::expected<int, my_error_t> funct_group19_88()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_89(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_90(); 

            
        tl::expected<int, my_error_t> funct_group19_89()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_90(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_91(); 

            
        tl::expected<int, my_error_t> funct_group19_90()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_91(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_92(); 

            
        tl::expected<int, my_error_t> funct_group19_91()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_92(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_93(); 

            
        tl::expected<int, my_error_t> funct_group19_92()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_93(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_94(); 

            
        tl::expected<int, my_error_t> funct_group19_93()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_94(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group19_95(); 

            
        tl::expected<int, my_error_t> funct_group19_94()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_0::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group19_95(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group19_95()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group20_1(); 

            
        tl::expected<int, my_error_t> funct_group20_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group20_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group20_2(); 

            
        tl::expected<int, my_error_t> funct_group20_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group20_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group20_3(); 

            
        tl::expected<int, my_error_t> funct_group20_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group20_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group20_4(); 

            
        tl::expected<int, my_error_t> funct_group20_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group20_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group20_5(); 

            
        tl::expected<int, my_error_t> funct_group20_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group20_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group20_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group21_1(); 

            
        tl::expected<int, my_error_t> funct_group21_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group21_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group21_2(); 

            
        tl::expected<int, my_error_t> funct_group21_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group21_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group21_3(); 

            
        tl::expected<int, my_error_t> funct_group21_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group21_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group21_4(); 

            
        tl::expected<int, my_error_t> funct_group21_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group21_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group21_5(); 

            
        tl::expected<int, my_error_t> funct_group21_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group21_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group21_6(); 

            
        tl::expected<int, my_error_t> funct_group21_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group21_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group21_7(); 

            
        tl::expected<int, my_error_t> funct_group21_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group21_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group21_8(); 

            
        tl::expected<int, my_error_t> funct_group21_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group21_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group21_9(); 

            
        tl::expected<int, my_error_t> funct_group21_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group21_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group21_10(); 

            
        tl::expected<int, my_error_t> funct_group21_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group21_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group21_11(); 

            
        tl::expected<int, my_error_t> funct_group21_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group21_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group21_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_1(); 

            
        tl::expected<int, my_error_t> funct_group22_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_2(); 

            
        tl::expected<int, my_error_t> funct_group22_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_3(); 

            
        tl::expected<int, my_error_t> funct_group22_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_4(); 

            
        tl::expected<int, my_error_t> funct_group22_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_5(); 

            
        tl::expected<int, my_error_t> funct_group22_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_6(); 

            
        tl::expected<int, my_error_t> funct_group22_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_7(); 

            
        tl::expected<int, my_error_t> funct_group22_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_8(); 

            
        tl::expected<int, my_error_t> funct_group22_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_9(); 

            
        tl::expected<int, my_error_t> funct_group22_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_10(); 

            
        tl::expected<int, my_error_t> funct_group22_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_11(); 

            
        tl::expected<int, my_error_t> funct_group22_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_12(); 

            
        tl::expected<int, my_error_t> funct_group22_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_12(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_13(); 

            
        tl::expected<int, my_error_t> funct_group22_12()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_13(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_14(); 

            
        tl::expected<int, my_error_t> funct_group22_13()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_14(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_15(); 

            
        tl::expected<int, my_error_t> funct_group22_14()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_15(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_16(); 

            
        tl::expected<int, my_error_t> funct_group22_15()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_16(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_17(); 

            
        tl::expected<int, my_error_t> funct_group22_16()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_17(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_18(); 

            
        tl::expected<int, my_error_t> funct_group22_17()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_18(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_19(); 

            
        tl::expected<int, my_error_t> funct_group22_18()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_19(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_20(); 

            
        tl::expected<int, my_error_t> funct_group22_19()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_20(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_21(); 

            
        tl::expected<int, my_error_t> funct_group22_20()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_21(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_22(); 

            
        tl::expected<int, my_error_t> funct_group22_21()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_22(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group22_23(); 

            
        tl::expected<int, my_error_t> funct_group22_22()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group22_23(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group22_23()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_1(); 

            
        tl::expected<int, my_error_t> funct_group23_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_2(); 

            
        tl::expected<int, my_error_t> funct_group23_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_3(); 

            
        tl::expected<int, my_error_t> funct_group23_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_4(); 

            
        tl::expected<int, my_error_t> funct_group23_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_5(); 

            
        tl::expected<int, my_error_t> funct_group23_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_6(); 

            
        tl::expected<int, my_error_t> funct_group23_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_7(); 

            
        tl::expected<int, my_error_t> funct_group23_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_8(); 

            
        tl::expected<int, my_error_t> funct_group23_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_9(); 

            
        tl::expected<int, my_error_t> funct_group23_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_10(); 

            
        tl::expected<int, my_error_t> funct_group23_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_11(); 

            
        tl::expected<int, my_error_t> funct_group23_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_12(); 

            
        tl::expected<int, my_error_t> funct_group23_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_12(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_13(); 

            
        tl::expected<int, my_error_t> funct_group23_12()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_13(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_14(); 

            
        tl::expected<int, my_error_t> funct_group23_13()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_14(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_15(); 

            
        tl::expected<int, my_error_t> funct_group23_14()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_15(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_16(); 

            
        tl::expected<int, my_error_t> funct_group23_15()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_16(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_17(); 

            
        tl::expected<int, my_error_t> funct_group23_16()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_17(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_18(); 

            
        tl::expected<int, my_error_t> funct_group23_17()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_18(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_19(); 

            
        tl::expected<int, my_error_t> funct_group23_18()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_19(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_20(); 

            
        tl::expected<int, my_error_t> funct_group23_19()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_20(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_21(); 

            
        tl::expected<int, my_error_t> funct_group23_20()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_21(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_22(); 

            
        tl::expected<int, my_error_t> funct_group23_21()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_22(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_23(); 

            
        tl::expected<int, my_error_t> funct_group23_22()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_23(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_24(); 

            
        tl::expected<int, my_error_t> funct_group23_23()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_24(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_25(); 

            
        tl::expected<int, my_error_t> funct_group23_24()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_25(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_26(); 

            
        tl::expected<int, my_error_t> funct_group23_25()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_26(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_27(); 

            
        tl::expected<int, my_error_t> funct_group23_26()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_27(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_28(); 

            
        tl::expected<int, my_error_t> funct_group23_27()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_28(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_29(); 

            
        tl::expected<int, my_error_t> funct_group23_28()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_29(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_30(); 

            
        tl::expected<int, my_error_t> funct_group23_29()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_30(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_31(); 

            
        tl::expected<int, my_error_t> funct_group23_30()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_31(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_32(); 

            
        tl::expected<int, my_error_t> funct_group23_31()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_32(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_33(); 

            
        tl::expected<int, my_error_t> funct_group23_32()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_33(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_34(); 

            
        tl::expected<int, my_error_t> funct_group23_33()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_34(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_35(); 

            
        tl::expected<int, my_error_t> funct_group23_34()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_35(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_36(); 

            
        tl::expected<int, my_error_t> funct_group23_35()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_36(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_37(); 

            
        tl::expected<int, my_error_t> funct_group23_36()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_37(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_38(); 

            
        tl::expected<int, my_error_t> funct_group23_37()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_38(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_39(); 

            
        tl::expected<int, my_error_t> funct_group23_38()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_39(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_40(); 

            
        tl::expected<int, my_error_t> funct_group23_39()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_40(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_41(); 

            
        tl::expected<int, my_error_t> funct_group23_40()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_41(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_42(); 

            
        tl::expected<int, my_error_t> funct_group23_41()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_42(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_43(); 

            
        tl::expected<int, my_error_t> funct_group23_42()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_43(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_44(); 

            
        tl::expected<int, my_error_t> funct_group23_43()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_44(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_45(); 

            
        tl::expected<int, my_error_t> funct_group23_44()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_45(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_46(); 

            
        tl::expected<int, my_error_t> funct_group23_45()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_46(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group23_47(); 

            
        tl::expected<int, my_error_t> funct_group23_46()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group23_47(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group23_47()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_1(); 

            
        tl::expected<int, my_error_t> funct_group24_0()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_1(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_2(); 

            
        tl::expected<int, my_error_t> funct_group24_1()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_2(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_3(); 

            
        tl::expected<int, my_error_t> funct_group24_2()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_3(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_4(); 

            
        tl::expected<int, my_error_t> funct_group24_3()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_4(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_5(); 

            
        tl::expected<int, my_error_t> funct_group24_4()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_5(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_6(); 

            
        tl::expected<int, my_error_t> funct_group24_5()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_6(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_7(); 

            
        tl::expected<int, my_error_t> funct_group24_6()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_7(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_8(); 

            
        tl::expected<int, my_error_t> funct_group24_7()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_8(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_9(); 

            
        tl::expected<int, my_error_t> funct_group24_8()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_9(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_10(); 

            
        tl::expected<int, my_error_t> funct_group24_9()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_10(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_11(); 

            
        tl::expected<int, my_error_t> funct_group24_10()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_11(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_12(); 

            
        tl::expected<int, my_error_t> funct_group24_11()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_12(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_13(); 

            
        tl::expected<int, my_error_t> funct_group24_12()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_13(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_14(); 

            
        tl::expected<int, my_error_t> funct_group24_13()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_14(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_15(); 

            
        tl::expected<int, my_error_t> funct_group24_14()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_15(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_16(); 

            
        tl::expected<int, my_error_t> funct_group24_15()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_16(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_17(); 

            
        tl::expected<int, my_error_t> funct_group24_16()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_17(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_18(); 

            
        tl::expected<int, my_error_t> funct_group24_17()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_18(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_19(); 

            
        tl::expected<int, my_error_t> funct_group24_18()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_19(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_20(); 

            
        tl::expected<int, my_error_t> funct_group24_19()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_20(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_21(); 

            
        tl::expected<int, my_error_t> funct_group24_20()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_21(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_22(); 

            
        tl::expected<int, my_error_t> funct_group24_21()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_22(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_23(); 

            
        tl::expected<int, my_error_t> funct_group24_22()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_23(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_24(); 

            
        tl::expected<int, my_error_t> funct_group24_23()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_24(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_25(); 

            
        tl::expected<int, my_error_t> funct_group24_24()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_25(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_26(); 

            
        tl::expected<int, my_error_t> funct_group24_25()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_26(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_27(); 

            
        tl::expected<int, my_error_t> funct_group24_26()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_27(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_28(); 

            
        tl::expected<int, my_error_t> funct_group24_27()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_28(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_29(); 

            
        tl::expected<int, my_error_t> funct_group24_28()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_29(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_30(); 

            
        tl::expected<int, my_error_t> funct_group24_29()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_30(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_31(); 

            
        tl::expected<int, my_error_t> funct_group24_30()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_31(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_32(); 

            
        tl::expected<int, my_error_t> funct_group24_31()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_32(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_33(); 

            
        tl::expected<int, my_error_t> funct_group24_32()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_33(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_34(); 

            
        tl::expected<int, my_error_t> funct_group24_33()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_34(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_35(); 

            
        tl::expected<int, my_error_t> funct_group24_34()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_35(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_36(); 

            
        tl::expected<int, my_error_t> funct_group24_35()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_36(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_37(); 

            
        tl::expected<int, my_error_t> funct_group24_36()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_37(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_38(); 

            
        tl::expected<int, my_error_t> funct_group24_37()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_38(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_39(); 

            
        tl::expected<int, my_error_t> funct_group24_38()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_39(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_40(); 

            
        tl::expected<int, my_error_t> funct_group24_39()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_40(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_41(); 

            
        tl::expected<int, my_error_t> funct_group24_40()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_41(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_42(); 

            
        tl::expected<int, my_error_t> funct_group24_41()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_42(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_43(); 

            
        tl::expected<int, my_error_t> funct_group24_42()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_43(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_44(); 

            
        tl::expected<int, my_error_t> funct_group24_43()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_44(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_45(); 

            
        tl::expected<int, my_error_t> funct_group24_44()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_45(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_46(); 

            
        tl::expected<int, my_error_t> funct_group24_45()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_46(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_47(); 

            
        tl::expected<int, my_error_t> funct_group24_46()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_47(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_48(); 

            
        tl::expected<int, my_error_t> funct_group24_47()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_48(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_49(); 

            
        tl::expected<int, my_error_t> funct_group24_48()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_49(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_50(); 

            
        tl::expected<int, my_error_t> funct_group24_49()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_50(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_51(); 

            
        tl::expected<int, my_error_t> funct_group24_50()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_51(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_52(); 

            
        tl::expected<int, my_error_t> funct_group24_51()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_52(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_53(); 

            
        tl::expected<int, my_error_t> funct_group24_52()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_53(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_54(); 

            
        tl::expected<int, my_error_t> funct_group24_53()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_54(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_55(); 

            
        tl::expected<int, my_error_t> funct_group24_54()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_55(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_56(); 

            
        tl::expected<int, my_error_t> funct_group24_55()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_56(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_57(); 

            
        tl::expected<int, my_error_t> funct_group24_56()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_57(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_58(); 

            
        tl::expected<int, my_error_t> funct_group24_57()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_58(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_59(); 

            
        tl::expected<int, my_error_t> funct_group24_58()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_59(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_60(); 

            
        tl::expected<int, my_error_t> funct_group24_59()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_60(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_61(); 

            
        tl::expected<int, my_error_t> funct_group24_60()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_61(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_62(); 

            
        tl::expected<int, my_error_t> funct_group24_61()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_62(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_63(); 

            
        tl::expected<int, my_error_t> funct_group24_62()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_63(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_64(); 

            
        tl::expected<int, my_error_t> funct_group24_63()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_64(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_65(); 

            
        tl::expected<int, my_error_t> funct_group24_64()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_65(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_66(); 

            
        tl::expected<int, my_error_t> funct_group24_65()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_66(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_67(); 

            
        tl::expected<int, my_error_t> funct_group24_66()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_67(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_68(); 

            
        tl::expected<int, my_error_t> funct_group24_67()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_68(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_69(); 

            
        tl::expected<int, my_error_t> funct_group24_68()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_69(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_70(); 

            
        tl::expected<int, my_error_t> funct_group24_69()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_70(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_71(); 

            
        tl::expected<int, my_error_t> funct_group24_70()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_71(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_72(); 

            
        tl::expected<int, my_error_t> funct_group24_71()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_72(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_73(); 

            
        tl::expected<int, my_error_t> funct_group24_72()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_73(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_74(); 

            
        tl::expected<int, my_error_t> funct_group24_73()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_74(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_75(); 

            
        tl::expected<int, my_error_t> funct_group24_74()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_75(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_76(); 

            
        tl::expected<int, my_error_t> funct_group24_75()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_76(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_77(); 

            
        tl::expected<int, my_error_t> funct_group24_76()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_77(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_78(); 

            
        tl::expected<int, my_error_t> funct_group24_77()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_78(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_79(); 

            
        tl::expected<int, my_error_t> funct_group24_78()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_79(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_80(); 

            
        tl::expected<int, my_error_t> funct_group24_79()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_80(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_81(); 

            
        tl::expected<int, my_error_t> funct_group24_80()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_81(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_82(); 

            
        tl::expected<int, my_error_t> funct_group24_81()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_82(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_83(); 

            
        tl::expected<int, my_error_t> funct_group24_82()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_83(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_84(); 

            
        tl::expected<int, my_error_t> funct_group24_83()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_84(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_85(); 

            
        tl::expected<int, my_error_t> funct_group24_84()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_85(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_86(); 

            
        tl::expected<int, my_error_t> funct_group24_85()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_86(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_87(); 

            
        tl::expected<int, my_error_t> funct_group24_86()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_87(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_88(); 

            
        tl::expected<int, my_error_t> funct_group24_87()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_88(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_89(); 

            
        tl::expected<int, my_error_t> funct_group24_88()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_89(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_90(); 

            
        tl::expected<int, my_error_t> funct_group24_89()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_90(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_91(); 

            
        tl::expected<int, my_error_t> funct_group24_90()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_91(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_92(); 

            
        tl::expected<int, my_error_t> funct_group24_91()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_92(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_93(); 

            
        tl::expected<int, my_error_t> funct_group24_92()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_93(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_94(); 

            
        tl::expected<int, my_error_t> funct_group24_93()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_94(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

            tl::expected<int, my_error_t> funct_group24_95(); 

            
        tl::expected<int, my_error_t> funct_group24_94()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if(auto result = funct_group24_95(); !result) {
                    return tl::unexpected(result.error());
                } else {
                    side_effect = side_effect + result.value();
                }
        return side_effect;
        }
        

        tl::expected<int, my_error_t> funct_group24_95()
        {
            volatile static std::uint32_t inner_side_effect = 0;
            inner_side_effect = inner_side_effect + 1;
        
        auto instance_0 = class_1::make(side_effect);
        if (!instance_0) {
            return tl::unexpected(instance_0.error());
        }
        {
        auto scoped_result = instance_0.value().trigger();
        if (!scoped_result) {
            return tl::unexpected(scoped_result.error());
        }
        }
                if (side_effect > 0)
                {
                    return tl::unexpected(my_error_t{ .data = { 0xDE, 0xAD } });
                }
                
        return side_effect;
        }
        