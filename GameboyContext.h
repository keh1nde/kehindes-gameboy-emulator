//
// Created by Kehinde Adeoso on 8/25/25.
//

#ifndef KEHINDES_GAMEBOY_EMULATOR_GAMEBOYCONTEXT_H
#define KEHINDES_GAMEBOY_EMULATOR_GAMEBOYCONTEXT_H

#include <array>
#include <cstdint>
#include <stack>

struct Cartridge // ROM Banking, External RAM, Memory Bank Controller registers
{
    using BYTE = uint8_t;
    using WORD = uint16_t;
    enum class MBCKind {None, MBC1, MBC2, MBC3, MBC5, HuC1, HuC3, Unknown};

    // Start of Memory Bank Implementation. Make sure the the following is set before the emulator runs.
    MBCKind kind = MBCKind::Unknown;
    int cm_RAM_SIZE;
    int cm_RAM_BANK_AMT;
    int cm_ROM_SIZE;
    int cm_ROM_BANK_AMT;

    std::vector<BYTE> cm_MBCROM;
    std::vector<BYTE> cm_MBCRAM;
};
struct PPU; // Picture Processing Unit, owns VRAM, OAM, PPU regs
struct APU; // Audio registers
struct Timers; // DIV/TIMA/TMA/TAC
struct Joypad; // FF00
struct DMA; // Direct Memory Access
struct Interrupts; // Interrupt Flag and Interrupt Enable | IF (FF0F) + IE (FFFF)


struct GBBus {
    using BYTE = uint8_t;
    using WORD = uint16_t;

    // Devices
    Cartridge* cartridge;
    PPU* ppu;
    APU* apu;
    Timers* timers;
    Joypad* joypad;
    DMA* dma;
    Interrupts* interrupts;

    BYTE m_WorkRam[8][0x1000];
    BYTE m_HighRam[0x7];
    BYTE m_ObjectAttributeMemory[0xA0];
    BYTE m_SVBK= 1; // WRAM Bank Select. Selects which RAM banks to use for GBC.
    int GBC = 0; // Set to 1 if emulating GBC, 0 otherwise

    inline int WorkRamBankD() const;


    BYTE read8(uint16_t addr);
    void    write8(uint16_t addr, uint8_t data);
};

struct CPU {
    uint8_t A,F,B,C,D,E,H,L; // Must they really be separate?
    uint16_t PC, SP;

    /* Might be useful for later.
    inline void setFlagZ(bool v){ F = v ? (F|0x80) : (F&~0x80); }
    // N=0x40, H=0x20, C=0x10; low nibble must stay 0 on writes
    inline void writeF(uint8_t v){ F = v & 0xF0; }
    */

    int step(class Bus& bus); // fetch/decode/execute, returns cycles
};


#endif //KEHINDES_GAMEBOY_EMULATOR_GAMEBOYCONTEXT_H