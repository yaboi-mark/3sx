#ifndef XRD_COMMON_H
#define XRD_COMMON_H

#define XRD_MAX_VITALITY 200
#define XRD_TIMER_SPEED 0      //how fast the timer is at base
#define XRD_TIMER_SLOWDOWN 60   //how must faster/slower the timer is by the end of the round

typedef enum {
    ROMAN_CANCEL_TYPE_TAUNT,
    ROMAN_CANCEL_TYPE_NOT_TAUNT,
    ROMAN_CANCEL_TYPE_RED
} roman_cancel_type;

#endif
