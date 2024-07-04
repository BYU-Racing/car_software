#ifndef BLACKBOX_H
#define BLACKBOX_H

#include <string>

class BlackBox {
    private:
        FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> comsCAN;


        String updateFileName();
        int getMaxNumber();
        void writeNumber(const int&);
        String assembleName(const int&);
        int tempLength(const int&);


    public:
        BlackBox(FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> comsCANin);
};

#endif