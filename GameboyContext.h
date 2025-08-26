//
// Created by Kehinde Adeoso on 8/25/25.
//

#ifndef KEHINDES_GAMEBOY_EMULATOR_GAMEBOYCONTEXT_H
#define KEHINDES_GAMEBOY_EMULATOR_GAMEBOYCONTEXT_H

#include <array>
#include <cstdint>

struct Cartridge; // ROM Banking, External RAM, Memory Bank Controller registers
struct PPU; // Picture Processing Unit, owns VRAM, OAM, PPU regs
struct APU; // Audio registers
struct Timers; // DIV/TIMA/TMA/TAC
struct Joypad; // FF00
struct DMA; // Direct Memory Access
struct Interrupts; // Interrupt Flag and Interrupt Enable | IF (FF0F) + IE (FFFF)


struct Bus {
    // Devices
    Cartridge* cartridge;
    PPU* ppu;
    APU* apu;
    Timers* timers;
    Joypad* joypad;
    DMA* dma;
    Interrupts* interrupts;

    // Memory
    bool bootrom_mapped = true;
    std::array<uint8_t, 0x100> bootrom{};
    std::array<uint8_t, 8 * 1024> bus_wram_bank0{};
    std::array<uint8_t, 4 * 1024> bus_wram_bank1{}; // banked on GBC
    std::array<uint8_t, 127> bus_hram{};
    uint8_t io[0x80]{}; // or route each IO addr to owner

    uint8_t read8(uint16_t addr);
    void    write8(uint16_t addr, uint8_t data);



};


#endif //KEHINDES_GAMEBOY_EMULATOR_GAMEBOYCONTEXT_H