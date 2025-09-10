//
// Created by Kehinde Adeoso on 8/25/25.
//

#include "GameboyContext.h"

int GBBus::WorkRamBankD() const {
    if (!GBC) return 1;
    const BYTE b = m_SVBK & 0x07;

    return b ? b : 1;
}

// Device implementations required.
GBBus::BYTE GBBus::read8(uint16_t addr) {
    switch (addr)
    {

    }
}

void GBBus::write8(uint16_t addr, uint8_t data) {

}
