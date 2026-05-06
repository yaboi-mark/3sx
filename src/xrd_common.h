#ifndef XRD_COMMON_H
#define XRD_COMMON_H

//#define STATE_DEBUG

#define XRD_MAX_VITALITY 200

#define XRD_INSTANT_BLOCK_WINDOW 8
#define XRD_INSTANT_BLOCK_COOLDOWN 20   //cooldown does not include the block window
#define XRD_INSTANT_BLOCK_FRAME_NUMERATOR 2
#define XRD_INSTANT_BLOCK_FRAME_DENOMENATOR 3

 //note: the basegame timer is 53 frames, not 60.
 //also, this mechanic isn't anything related to xrd or sf3's mechanics, i just wanted to test this to see if anyone noticed it.
 //at least, during gameplay, i mean. reading from the github doesn't count.
#define XRD_TIMER_SPEED 48      //how fast the timer is at base
#define XRD_TIMER_SLOWDOWN 14   //how must faster/slower the timer is by the end of the round

#endif
