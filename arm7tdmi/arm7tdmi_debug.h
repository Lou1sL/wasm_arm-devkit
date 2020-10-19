#pragma once

#include "arm7tdmi.h"

struct DebugStatus {
    std::uint32_t pipeline[3];

    std::uint32_t reg_current_general[GENERAL_REG_SIZE];
    std::uint32_t reg_current_cpsr;
    std::uint32_t reg_current_spsr;

    std::uint32_t reg_banked_general_sysusr[BANK_SIZE];
    std::uint32_t reg_banked_general_fiq[BANK_SIZE];
    std::uint32_t reg_banked_general_irq[BANK_SIZE];
    std::uint32_t reg_banked_general_svc[BANK_SIZE];
    std::uint32_t reg_banked_general_abt[BANK_SIZE];
    std::uint32_t reg_banked_general_und[BANK_SIZE];

    std::uint32_t reg_banked_spsr_fiq;
    std::uint32_t reg_banked_spsr_irq;
    std::uint32_t reg_banked_spsr_svc;
    std::uint32_t reg_banked_spsr_abt;
    std::uint32_t reg_banked_spsr_und;

    bool cond_cpsr[16];
    bool cond_spsr_fiq[16];
    bool cond_spsr_irq[16];
    bool cond_spsr_svc[16];
    bool cond_spsr_abt[16];
    bool cond_spsr_und[16];
};

template <std::size_t N>
class BusBindFullRAM : public BusInterface {
public:
    std::array<std::uint8_t,N>* memory;
    BusBindFullRAM(std::array<std::uint8_t,N>* mem) : memory(mem){}
    std::uint8_t  R8   (std::uint32_t addr, bool isSeq){
        return *reinterpret_cast<std::uint8_t*>(&(reinterpret_cast<std::uint8_t*>(memory))[addr]);
    }
    std::uint16_t R16  (std::uint32_t addr, bool isSeq){
        return *reinterpret_cast<std::uint16_t*>(&(reinterpret_cast<std::uint8_t*>(memory))[addr]);
    }
    std::uint32_t R32  (std::uint32_t addr, bool isSeq){
        return *reinterpret_cast<std::uint32_t*>(&(reinterpret_cast<std::uint8_t*>(memory))[addr]);
    }
    void          W8   (std::uint32_t addr, std::uint8_t  val, bool isSeq){
        *reinterpret_cast<std::uint8_t*>(&(reinterpret_cast<std::uint8_t*>(memory))[addr]) = val;
    }
    void          W16  (std::uint32_t addr, std::uint16_t val, bool isSeq){
        *reinterpret_cast<std::uint16_t*>(&(reinterpret_cast<std::uint8_t*>(memory))[addr]) = val;
    }
    void          W32  (std::uint32_t addr, std::uint32_t val, bool isSeq){
        *reinterpret_cast<std::uint32_t*>(&(reinterpret_cast<std::uint8_t*>(memory))[addr]) = val;
    }
};


template <std::size_t MEM_SIZE>
class ARM7TDMI_DEBUG {
public:
    std::array<std::uint8_t,MEM_SIZE> memory;
    BusBindFullRAM<MEM_SIZE> main_bus;
    ARM7TDMI cpu;

    ARM7TDMI_DEBUG() : main_bus(&memory), cpu(&main_bus) { memory.fill(0xFF); }

    //Attention:
    //Due to pipelined CPU nature, changing memory data may not take effect immediatly.
    //For example:
    //During an interrupt(e.g RST), pipeline will already be filled with the data from EVA, and ready for branch.
    //So if you set EVA data afterwards, it simply won't work.
    template <std::size_t SZ>
    void SetMemory32(std::uint32_t addr, const std::uint32_t(&data)[SZ]) {
        for(std::size_t i=0; i<SZ; i++){
            main_bus.W8(addr+i*4+3, (std::uint8_t)(data[i] >>  0), false);
            main_bus.W8(addr+i*4+2, (std::uint8_t)(data[i] >>  8), false);
            main_bus.W8(addr+i*4+1, (std::uint8_t)(data[i] >> 16), false);
            main_bus.W8(addr+i*4  , (std::uint8_t)(data[i] >> 24), false);
        }
    }
    void SetMemory8(std::uint32_t addr, std::uint8_t data){
        main_bus.W8(addr, data, false);
    }
    std::uint8_t GetMemory8(std::uint32_t addr){
        return main_bus.R8(addr, false);
    }
    void ResetMemory(){
        memory.fill(0xFF);
    }

    void SetStackPointer(std::uint32_t val){
        for(std::size_t i=0; i<BANK_COUNT; i++)
            cpu.registers.banked[i][BANK_R13] = val;
        cpu.registers[13] = val;
    }
    void Step() {
        cpu.Step();
    }

    DebugStatus GetStatus(){
        DebugStatus sta;
        sta.pipeline[0] = cpu.instruction_register;
        sta.pipeline[1] = cpu.pipeline[0];
        sta.pipeline[2] = cpu.pipeline[1];
        for(std::size_t i=0; i<GENERAL_REG_SIZE; i++){
            sta.reg_current_general[i] = cpu.registers[i];
        }
        sta.reg_current_cpsr = cpu.registers.cpsr.value;
        sta.reg_current_spsr = (*cpu.registers.p_spsr).value;
        for(std::size_t i=0; i<BANK_SIZE; i++){
            sta.reg_banked_general_sysusr[i] = cpu.registers.banked[BANK_SYSUSR][i];
            sta.reg_banked_general_fiq[i]    = cpu.registers.banked[BANK_FIQ][i];
            sta.reg_banked_general_irq[i]    = cpu.registers.banked[BANK_IRQ][i];
            sta.reg_banked_general_svc[i]    = cpu.registers.banked[BANK_SVC][i];
            sta.reg_banked_general_abt[i]    = cpu.registers.banked[BANK_ABT][i];
            sta.reg_banked_general_und[i]    = cpu.registers.banked[BANK_UND][i];
        }
        sta.reg_banked_spsr_fiq = cpu.registers.spsr[BANK_FIQ].value;
        sta.reg_banked_spsr_irq = cpu.registers.spsr[BANK_IRQ].value;
        sta.reg_banked_spsr_svc = cpu.registers.spsr[BANK_SVC].value;
        sta.reg_banked_spsr_abt = cpu.registers.spsr[BANK_ABT].value;
        sta.reg_banked_spsr_und = cpu.registers.spsr[BANK_UND].value;

        for(int i=0;i<16;i++){
            sta.cond_cpsr[i] = cpu.condition_table[cpu.registers.cpsr.nzcv][i];
            sta.cond_spsr_fiq[i] = cpu.condition_table[cpu.registers.spsr[BANK_FIQ].nzcv][i];
            sta.cond_spsr_irq[i] = cpu.condition_table[cpu.registers.spsr[BANK_IRQ].nzcv][i];
            sta.cond_spsr_svc[i] = cpu.condition_table[cpu.registers.spsr[BANK_SVC].nzcv][i];
            sta.cond_spsr_abt[i] = cpu.condition_table[cpu.registers.spsr[BANK_ABT].nzcv][i];
            sta.cond_spsr_und[i] = cpu.condition_table[cpu.registers.spsr[BANK_UND].nzcv][i];
        }
        return sta;
    }
};

